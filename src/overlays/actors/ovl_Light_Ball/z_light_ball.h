#ifndef _Z_LIGHT_BALL_H_
#define _Z_LIGHT_BALL_H_

#include "ultra64.h"
#include "global.h"

struct LightBall;

typedef void (*LightBallActionFunc)(struct LightBall*, GlobalContext*);

typedef struct LightBall {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ LightBallActionFunc actionFunc;
                 u32 timer;
} LightBall;

extern const ActorInit Light_Ball_InitVars;

#endif
