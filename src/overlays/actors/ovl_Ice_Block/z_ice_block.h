#ifndef _Z_ICE_BLOCK_H_
#define _Z_ICE_BLOCK_H_

#include "ultra64.h"
#include "global.h"

struct IceBlock;

typedef struct IceBlock {
    DynaPolyActor dyna;
    s16 lifetime;
    f32 size;
    u8 status;
} IceBlock;

extern const ActorInit Ice_Block_InitVars;

#endif
