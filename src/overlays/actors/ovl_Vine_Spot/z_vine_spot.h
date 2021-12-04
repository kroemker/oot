#ifndef _Z_VINE_SPOT_H_
#define _Z_VINE_SPOT_H_

#include "ultra64.h"
#include "global.h"

struct VineSpot;

typedef struct VineSpot {
    DynaPolyActor dyna;
    s16 lifetime;
    f32 size;
    u8 status;
} VineSpot;

extern const ActorInit Vine_Spot_InitVars;

#endif