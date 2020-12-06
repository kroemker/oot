#ifndef _Z_ARROW_BOMB_H_
#define _Z_ARROW_BOMB_H_

#include "ultra64.h"
#include "global.h"

#include "../ovl_En_Bom/z_en_bom.h"

struct ArrowBomb;

typedef void (*ArrowBombActionFunc)(struct ArrowBomb*, GlobalContext*);

typedef struct ArrowBomb {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ Vec3f unkPos;
    /* 0x0150 */ ArrowBombActionFunc actionFunc;
    ColliderJntSph explosionCollider;
    ColliderJntSphItem explosionColliderItems[1];
    Actor* bomb;
    f32 bombScale;
} ArrowBomb;

extern const ActorInit Arrow_Bomb_InitVars;

#endif
