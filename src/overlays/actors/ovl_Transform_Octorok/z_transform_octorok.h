#ifndef Z_TRANSFORM_OCTOROK_H
#define Z_TRANSFORM_OCTOROK_H

#include "ultra64.h"
#include "global.h"

struct TransformOctorok;

typedef void (*TransformOctorokActionFunc)(struct TransformOctorok*, PlayState*);

typedef struct TransformOctorok {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ TransformOctorokActionFunc actionFunc;
    /* 0x0194 */ s16 timer;
    /* 0x0196 */ s16 numShots;
    /* 0x0198 */ Vec3s jointTable[38];
    /* 0x027C */ Vec3s morphTable[38];
    /* 0x0360 */ f32 jumpHeight;
    /* 0x0364 */ Vec3f headScale;
    /* 0x0370 */ ColliderCylinder collider;
    s32 framesBPressed;
    s32 framesAPressed;
} TransformOctorok; // size = 0x03BC

#endif
