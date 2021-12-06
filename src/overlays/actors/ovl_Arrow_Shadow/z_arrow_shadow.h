#ifndef _Z_ARROW_SHADOW_H_
#define _Z_ARROW_SHADOW_H_

#include "ultra64.h"
#include "global.h"

struct ArrowShadow;

typedef void (*ArrowShadowActionFunc)(struct ArrowShadow*, GlobalContext*);

typedef struct ArrowShadow {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ Vec3f unkPos;
    /* 0x0150 */ ArrowShadowActionFunc actionFunc;
    s16 radius;
    f32 unk_160;
    u8 alpha;
} ArrowShadow;

extern const ActorInit Arrow_Shadow_InitVars;

#endif
