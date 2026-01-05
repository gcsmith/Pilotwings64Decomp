# ------------------------------------------------------------------------------
# Configuration
# ------------------------------------------------------------------------------

VERSION  ?= us
BASENAME := pilotwings64
DISPNAME := Pilotwings 64
BASEROM  := baserom.$(VERSION).z64

NO_COL  := \033[0m
RED     := \033[0;31m
RED2    := \033[1;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
BLUE    := \033[0;34m
PINK    := \033[0;35m
CYAN    := \033[0;36m

# ------------------------------------------------------------------------------
# Toolchain
# ------------------------------------------------------------------------------

find-command = $(shell which $(1) 2>/dev/null)

ifneq      ($(call find-command,mips-linux-gnu-ld),)
  CROSS := mips-linux-gnu-
else ifneq ($(call find-command,mips64-linux-gnu-ld),)
  CROSS := mips64-linux-gnu-
else ifneq ($(call find-command,mips64-elf-ld),)
  CROSS := mips64-elf-
else
  $(error Unable to detect a suitable MIPS toolchain installed.)
endif

TOOLS_DIR = tools

AS       := $(CROSS)as
LD       := $(CROSS)ld
OBJCOPY  := $(CROSS)objcopy
PYTHON   := python3
GCC_HOST := gcc
GREP     := grep -rl

USE_QEMU_IRIX ?= 0
$(eval $(call validate-option,USE_QEMU_IRIX,0 1))

ifeq ($(USE_QEMU_IRIX),1)
  # Verify that qemu-irix exists
  QEMU_IRIX := $(call find-command,qemu-irix)
  ifeq (,$(QEMU_IRIX))
    $(error Using the IDO compiler requires qemu-irix. Please install qemu-irix)
  endif
endif

ifeq ($(USE_QEMU_IRIX),1)
  CC := $(QEMU_IRIX) -silent -L $(TOOLS_DIR)/ido5.3_cc $(TOOLS_DIR)/ido5.3_cc/usr/bin/cc
else
  CC := $(TOOLS_DIR)/ido-static-recomp/build/5.3/out/cc
endif

ASM_PROCESSOR_DIR := $(TOOLS_DIR)/asm-processor
ASM_PROCESSOR     := $(PYTHON) $(ASM_PROCESSOR_DIR)/asm_processor.py

SPLAT       := $(PYTHON) -m splat split
SPLAT_YAML  := config/$(VERSION)/$(BASENAME).$(VERSION).yaml
SPLAT_FLAGS :=

TORCH    	:= $(TOOLS_DIR)/Torch/cmake-build-release/torch

# ------------------------------------------------------------------------------
# Inputs
# ------------------------------------------------------------------------------

ASM_DIR = asm
BIN_DIR = bin
SRC_DIR = src

ASM_DIRS := $(shell find $(ASM_DIR) -type d -not -path "asm/nonmatchings/*")
BIN_DIRS := $(shell find $(BIN_DIR) -type d)
SRC_DIRS := $(shell find $(SRC_DIR) -type d)

S_FILES := $(foreach dir,$(ASM_DIRS) $(SRC_DIRS),$(wildcard $(dir)/*.s))
B_FILES := $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

LIBULTRA_DIRS := $(shell find tools/ultralib/src -type d -not -path "lib/ultralib/src/voice")

# ------------------------------------------------------------------------------
# Outputs
# ------------------------------------------------------------------------------

BUILD_DIR = build

ROM_BIN   := $(BUILD_DIR)/$(BASENAME).$(VERSION).bin
ROM_ELF   := $(BUILD_DIR)/$(BASENAME).$(VERSION).elf
ROM_Z64   := $(BUILD_DIR)/$(BASENAME).$(VERSION).z64
LD_MAP    := $(BUILD_DIR)/$(BASENAME).$(VERSION).map
LD_SCRIPT := $(BUILD_DIR)/$(BASENAME).$(VERSION).ld

S_O_FILES := $(foreach file,$(S_FILES:.s=.o),$(BUILD_DIR)/$(file))
B_O_FILES := $(foreach file,$(B_FILES:.bin=.o),$(BUILD_DIR)/$(file))
C_O_FILES := $(foreach file,$(C_FILES:.c=.o),$(BUILD_DIR)/$(file))

O_FILES := $(C_O_FILES) $(S_O_FILES) $(B_O_FILES)

CRC := @$(TOOLS_DIR)/n64crc build/$(BASENAME).$(VERSION).z64 #Recalculating the CRC

OPT_FLAGS      = -O2
LOOP_UNROLL    =

MIPSISET       = -mips2 -32

INCLUDE_CFLAGS = -I. -Iinclude -Isrc -Itools/ultralib/include

ASFLAGS        = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include
OBJCOPYFLAGS   = -O binary

# Files requiring pre/post-processing
GLOBAL_ASM_C_FILES := $(shell $(GREP) GLOBAL_ASM $(SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_O_FILES := $(foreach file,$(GLOBAL_ASM_C_FILES:.c=.o),$(BUILD_DIR)/$(file))

DEFINES := -D_LANGUAGE_C -D_FINALROM -DF3D_OLD -DWIN32 -DSSSV -DNDEBUG -DTARGET_N64 -DCOMPILING_LIBULTRA
DEFINES += -DVERSION_US

VERIFY = verify

CFLAGS := -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -fullwarn  -nostdinc -g0
CFLAGS += $(DEFINES)
# ignore compiler warnings about anonymous structs
CFLAGS += -woff 624,649,838,712,516,513,596,564,594,709,807
CFLAGS += $(INCLUDE_CFLAGS)

CHECK_WARNINGS := -Wall -Wextra -Wno-format-security -Wno-unknown-pragmas -Wunused-function -Wno-unused-parameter -Wno-unused-variable -Wno-missing-braces -Wno-int-conversion
CC_CHECK := $(GCC_HOST) -fsyntax-only -fno-builtin -fsigned-char -std=gnu90 -m32 $(CHECK_WARNINGS) $(INCLUDE_CFLAGS) $(DEFINES)

GCC_FLAGS := $(INCLUDE_CFLAGS) $(DEFINES)
GCC_FLAGS += -G 0 -mno-shared -march=vr4300 -mfix4300 -mabi=32 -mhard-float
GCC_FLAGS += -mdivide-breaks -fno-stack-protector -fno-common -fno-zero-initialized-in-bss -fno-PIC -mno-abicalls -fno-strict-aliasing -fno-inline-functions -ffreestanding -fwrapv
GCC_FLAGS += -Wall -Wextra -Wno-missing-braces

LD_FLAGS := -T $(LD_SCRIPT)
LD_FLAGS += -T config/$(VERSION)/sym/hardware_regs.ld
LD_FLAGS += -T config/$(VERSION)/sym/pif_syms.ld
LD_FLAGS += -T config/$(VERSION)/sym/libultra_undefined_syms.txt
LD_FLAGS += -T build/splat_out/$(VERSION)/undefined_funcs_auto.txt
LD_FLAGS += -T build/splat_out/$(VERSION)/undefined_syms_auto.txt
LD_FLAGS += -Map $(LD_MAP) --no-check-sections

ifeq ($(VERSION),us)
LD_FLAGS_EXTRA  =
LD_FLAGS_EXTRA += $(foreach sym,$(UNDEFINED_SYMS),-u $(sym))
else
LD_FLAGS_EXTRA  =
endif

### Optimisation Overrides
$(BUILD_DIR)/src/libultra/os/%.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src/libultra/os/audio/%.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/libultra/os/libc/%.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/libultra/gu/%.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src/libultra/gu/lookathil.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/libultra/os/osVirtualtoPhysical.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src/libultra/io/%.o: OPT_FLAGS := -O1

# ------------------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------------------

default: all

all: $(VERIFY)

dirs:
	$(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS) $(LIBULTRA_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

check: .baserom.$(VERSION).ok

verify: $(ROM_Z64)
	@md5sum $(ROM_Z64)
	@md5sum -c config/$(VERSION)/$(BASENAME).$(VERSION).md5

no_verify: $(ROM_Z64)
	@echo "Skipping SHA1SUM check!"

toolchain:
	@$(MAKE) -s -C $(TOOLS_DIR)

assets:
	rm -r -f torch.hash.yml
	@echo "Extracting assets from ROM..."
	@$(TORCH) code $(ROM_Z64) -v
	@$(TORCH) header $(ROM_Z64)
	@$(TORCH) modding export $(ROM_Z64)

init: tools
	@$(MAKE) clean
	@make extract
	@make -j

extract: tools
	rm -rf asm
	rm -rf build
	$(SPLAT) $(SPLAT_YAML) $(SPLAT_FLAGS)

dependencies: tools
	@make -C tools
	#@$(PYTHON) -m pip install -r tools/splat/requirements.txt #Install the splat dependencies
	#@$(PYTHON) -m pip install GitPython colour

expected:
	mkdir -p expected/build
	rm -rf expected/build/
	cp -r build/ expected/build/

clean:
	rm -rf asm
	rm -rf build

distclean: clean
	rm -rf asm
	rm -rf assets
	rm -rf bin
	rm -f *auto.txt
	rm -f *ctx.c*

format:
	$(PYTHON) tools/format.py -j

### Recipes
.baserom.$(VERSION).ok: baserom.$(VERSION).z64
	@echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check
	@touch $@

$(ROM_ELF): dirs $(LD_SCRIPT) $(BUILD_DIR)/$(LIBULTRA) $(O_FILES) $(LANG_RNC_O_FILES) $(IMAGE_O_FILES)
	@$(LD) $(LD_FLAGS) $(LD_FLAGS_EXTRA) -o $@
	@printf "[$(PINK) GNU Linker $(NO_COL)]  $<\n"

ifndef PERMUTER
$(GLOBAL_ASM_O_FILES): $(BUILD_DIR)/%.o: %.c
	@$(CC_CHECK) $<
	@printf "[$(YELLOW) GCC Syntax check $(NO_COL)] $<\n"
	@$(ASM_PROCESSOR) $(OPT_FLAGS) $< > $(BUILD_DIR)/$<
	@$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(LOOP_UNROLL) $(MIPSISET) -o $@ $(BUILD_DIR)/$<
	@$(ASM_PROCESSOR) $(OPT_FLAGS) $< --post-process $@ \
		--assembler "$(AS) $(ASFLAGS)" --asm-prelude $(ASM_PROCESSOR_DIR)/prelude.inc
	@printf "[$(GREEN) IRIS Development Option 5.3 $(NO_COL)]  $<\n" 
endif

# non asm-processor recipe
$(BUILD_DIR)/%.o: %.c
#	@$(CC_CHECK) $<
	@$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(LOOP_UNROLL) $(MIPSISET) -o $@ $<
	@printf "[$(GREEN) IRIS Development Option 5.3 $(NO_COL)]  $<\n"

$(BUILD_DIR)/$(LIBULTRA): $(LIBULTRA)
	@mkdir -p $$(dirname $@)
#	@cp $< $@
#	@$(PYTHON) $(TOOLS_DIR)/set_o32abi_bit.py $@

$(BUILD_DIR)/%.o: %.s
	@$(AS) $(ASFLAGS) -o $@ $<
	@printf "[$(GREEN) MIPS GNU Assembler   $(NO_COL)]  $<\n"

$(BUILD_DIR)/%.o: %.bin
	@$(LD) -r -b binary -o $@ $<
	@printf "[$(PINK) MIPS GNU Linker $(NO_COL)]  $<\n"

$(ROM_BIN): $(ROM_ELF)
	@$(OBJCOPY) $(OBJCOPYFLAGS) $< $@
	@printf "[$(CYAN) GNU Objcopy $(NO_COL)]  $<\n"

$(ROM_Z64): $(ROM_BIN)
	@printf "[$(CYAN) .bin -> .z64 $(NO_COL)] $<\n"
	@cp $(ROM_BIN) $(ROM_Z64)
	@printf "[$(GREEN) Calculating CRC $(NO_COL)]  $<\n"
	@$(CRC)

# fake targets for better error handling
$(SPLAT):
	$(info Repo cloned without submodules, attempting to fetch them now...)
	@which git >/dev/null || echo "ERROR: git binary not found on PATH"
	@which git >/dev/null
	git submodule update --init --recursive

baserom.$(VERSION).z64:
	$(error Place the $(DISPNAME) ROM, named '$@', in the root of this repo and try again.)

### Settings
.SECONDARY:
.PHONY: all clean default assets expected
SHELL = /bin/bash -e -o pipefail
