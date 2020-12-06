#ifndef _Z_ARROW_TELEPORT_H_
#define _Z_ARROW_TELEPORT_H_

#include "ultra64.h"
#include "global.h"

struct ArrowTeleport;

typedef void (*ArrowTeleportActionFunc)(struct ArrowTeleport*, GlobalContext*);

typedef struct ArrowTeleport {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ Vec3f unkPos;
    /* 0x0150 */ ArrowTeleportActionFunc actionFunc;
} ArrowTeleport;

extern const ActorInit Arrow_Teleport_InitVars;

#endif
