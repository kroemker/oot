#ifndef _Z_TRANSFORM_IK_H_
#define _Z_TRANSFORM_IK_H_

#include "ultra64.h"
#include "global.h"
#include "../ovl_En_Ik/z_en_ik.h"

struct TransformIk;

typedef void (*TransformIkActionFunc)(struct TransformIk*, PlayState*);

typedef struct TransformIk {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ Vec3s jointTable[IRON_KNUCKLE_LIMB_MAX];
    /* 0x0244 */ Vec3s morphTable[IRON_KNUCKLE_LIMB_MAX];
    /* 0x02F8 */ u8 unk_2F8;
    /* 0x02F9 */ u8 animationTimer;
    /* 0x02FA */ u8 drawArmorFlag;
    /* 0x02FB */ u8 armorStatusFlag;
    /* 0x02FC */ u8 isBreakingProp;
    /* 0x02FD */ u8 damageEffect;
    /* 0x02FE */ s8 unk_2FE;
    /* 0x02FF */ s8 unk_2FF;
    /* 0x0300 */ s16 unk_300;
    /* 0x0302 */ s16 switchFlag;
    /* 0x0304 */ TransformIkActionFunc actionFunc;
    /* 0x0308 */ BodyBreak bodyBreak;
    /* 0x0320 */ ColliderCylinder bodyCollider;
    /* 0x036C */ ColliderQuad axeCollider;
    /* 0x03EC */ ColliderTris shieldCollider;
    /* 0x040C */ ColliderTrisElement shieldColliderItems[2];
    /* 0x04C4 */ s32 blureIdx;
    /* 0x04C8 */ s32 csAction;
    /* 0x04CC */ s32 csDrawMode;
    /* 0x04D0 */ u32 cueId;
    /* 0x04D4 */ s32 isAxeSummoned;
    /* 0x04D8 */ char unk_4D8[0x04];
    u32 playedSfx;
    u32 queuedAttack;
} TransformIk;

extern const ActorInit Transform_Ik_InitVars;

#endif