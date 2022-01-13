#ifndef _Z_SPINNER_H_
#define _Z_SPINNER_H_

#include "ultra64.h"
#include "global.h"

struct Spinner;

typedef void (*SpinnerActionFunc)(struct Spinner*, GlobalContext*);

typedef struct Spinner {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ s16 radialSpeed;
    /* 0x0150 */ SpinnerActionFunc actionFunc;
    /* 0x0154 */ ColliderCylinder collider;
                 s32 timer;
                 f32 scale;
                 f32 initialSpeed;
} Spinner; // size = 0x0150

extern const ActorInit Spinner_InitVars;

#endif
