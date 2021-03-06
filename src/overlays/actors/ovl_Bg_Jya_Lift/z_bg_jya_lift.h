#ifndef _Z_BG_JYA_LIFT_H_
#define _Z_BG_JYA_LIFT_H_

#include <ultra64.h>
#include <global.h>

struct BgJyaLift;
typedef void (*BgJyaLiftActionFunc)(struct BgJyaLift*);

typedef struct BgJyaLift {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x164 */ BgJyaLiftActionFunc actionFunc;
    /* 0x168 */ s16 moveDelay;
    /* 0x16A */ u8 unk_16A;
    /* 0x16B */ u8 unk_16B;
} BgJyaLift; // size = 0x016C

extern const ActorInit Bg_Jya_Lift_InitVars;

#endif
