#ifndef PILOTWINGS64_UV_AUDIO
#define PILOTWINGS64_UV_AUDIO

#include <ultra64.h>
#include <uv_matrix.h>
#include <uv_util.h>

typedef struct uvaEmitter {
/* 00 */ Mtx4F_t m1;
/* 40 */ Vec3F_t unk40;
/* 4C */ Vec3F_t unk4C;
/* 58 */ Vec3F_t unk58;
/* 64 */ Vec3F_t unk64;
/* 70 */ Vec4F_t unk70;
/* 80 */ f32 unk80;
/* 84 */ f32 unk84;
/* 88 */ s32 priority;
/* 8C */ u8 sound;
/* 8D */ u8 unk8D;
/* 8E */ u8 unk8E;
/* 8F */ u8 unk8F;
/* 90 */ f32 near;
/* 94 */ f32 far;
/* 98 */ s32 unk98;
/* 9C */ f32 playPitch;
/* A0 */ s32 playState;
/* A4 */ s32 playVolume;
/* A8 */ s32 state;
/* AC */ u8 playVoice;
/* AD */ u8 playPan;
/* AE */ u8 playMix;
/* AF */ u8 playTimeout;
} uvaEmitter_t;

void uvEmitterInitTable(void);
void uvEmitterInit(uvaEmitter_t*);
u8 uvEmitterLookup(void);
void uvEmitterFromModel(u8 obj_id, u8 mdl_id);
void uvEmitterSetMatrix(u8 obj_id, Mtx4F_t msrc);
void uvEmitterGetMatrix(u8 obj_id, Mtx4F_t mdst);

void _uvaUpdateVoice(u8 obj_id);
void _uvaStopVoice(u8 voice_id);
void _uvaStatus(u8 obj_id);

void uvaSeqPlay(void);
void uvaSeqSetTempo(f32 tempo);
void uvaSeqSetVol(f32 vol);
void uvaSeqStop(void);

#endif // PILOTWINGS64_UV_AUDIO

