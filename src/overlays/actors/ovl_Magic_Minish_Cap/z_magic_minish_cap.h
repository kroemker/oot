#ifndef _Z_MAGIC_DARK_H_
#define _Z_MAGIC_DARK_H_

#include "ultra64.h"
#include "global.h"

struct MagicMinishCap;

typedef struct MagicMinishCap {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ s16 timer;
    /* 0x014E */ u8 primAlpha;
    /* 0x0150 */ Vec3f orbOffset;
    /* 0x015C */ f32 scale;
    /* 0x0160 */ char unk_160[0x4];
} MagicMinishCap; // size = 0x0164

extern const ActorInit Magic_Minish_Cap_InitVars;

#endif
