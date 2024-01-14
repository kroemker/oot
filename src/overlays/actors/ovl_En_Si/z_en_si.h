#ifndef Z_EN_SI_H
#define Z_EN_SI_H

#include "ultra64.h"
#include "global.h"

typedef enum {
    /* 0x00 */ SI_TOKEN,
    /* 0x01 */ SI_SOUL_IK,
    /* 0x02 */ SI_SOUL_OCTOROK,
    /* 0x03 */ SI_SOUL_KEESE,
} EnSiType;

struct EnSi;

typedef void (*EnSiActionFunc)(struct EnSi*, PlayState*);

typedef struct EnSi {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ EnSiActionFunc actionFunc;
    /* 0x0150 */ ColliderCylinder collider;
    /* 0x019C */ u8 unk_19C;
    u8 type;
} EnSi; // size = 0x01A0

#endif
