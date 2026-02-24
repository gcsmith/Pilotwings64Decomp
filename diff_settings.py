#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'baserom.us.z64'
    config['myimg'] = 'build/pilotwings64.us.z64'
    config['mapfile'] = 'build/pilotwings64.us.map'
    config['source_directories'] = ['./src','./include']
    config['objdump_flags'] = ['-M','reg-names=32']
    config['makeflags'] = ["KEEP_MDEBUG=1"]
