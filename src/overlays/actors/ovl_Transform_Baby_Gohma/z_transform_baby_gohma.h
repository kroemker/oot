#ifndef _Z_TRANSFORM_BABY_GOHMA_H_
#define _Z_TRANSFORM_BABY_GOHMA_H_

#include <ultra64.h>
#include <global.h>

#include "../ovl_En_Goma/z_en_goma.h"

struct TransformBabyGohma;

typedef void (*TransformBabyGohmaActionFunc)(struct TransformBabyGohma*, PlayState*);

typedef struct TransformBabyGohma {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[24];
    Vec3s morphTable[24];
    TransformBabyGohmaActionFunc actionFunc;
    ColliderCylinder attackCol;
    ColliderCylinder bodyCol;
    s16 slopePitch;
    s16 slopeRoll;
    s16 eyePitch;
    s16 eyeYaw;
    s16 hurtTimer;
    f32 eyeEnvColor[3];
    s32 framesAPressed;
    u8 eyeColorIndex;
    s32 idleTimer;
    s32 invincibilityFrames;
} TransformBabyGohma;

#endif
