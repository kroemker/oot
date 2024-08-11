/*
 * File: z_transform_gohma.c
 * Overlay: ovl_Transform_Gohma
 * Description: Gohma transformation
 */

#include "z_transform_gohma.h"
#include "assets/objects/object_goma/object_goma.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

typedef enum {
    VISUALSTATE_RED,         // main/eye: red
    VISUALSTATE_DEFAULT,     // main: greenish cyan, blinks with dark gray every 16 frames; eye: white
    VISUALSTATE_DEFEATED,    // main/eye: dark gray
    VISUALSTATE_STUNNED = 4, // main: greenish cyan, alternates with blue; eye: greenish cyan
    VISUALSTATE_HIT          // main: greenish cyan, alternates with red; eye: greenish cyan
} GohmaVisualState;

void TransformGohma_Init(Actor* thisx, PlayState* play);
void TransformGohma_Destroy(Actor* thisx, PlayState* play);
void TransformGohma_Update(Actor* thisx, PlayState* play);
void TransformGohma_Draw(Actor* thisx, PlayState* play);

void TransformGohma_Action_Idle(TransformGohma* this, PlayState* play);
void TransformGohma_Action_Walk(TransformGohma* this, PlayState* play);
void TransformGohma_Action_GetHit(TransformGohma* this, PlayState* play);
void TransformGohma_Action_HangCeiling(TransformGohma* this, PlayState* play);
void TransformGohma_Action_Fall(TransformGohma* this, PlayState* play);
void TransformGohma_Action_StartClimb(TransformGohma* this, PlayState* play);
void TransformGohma_Action_Climb(TransformGohma* this, PlayState* play);
void TransformGohma_Action_Land(TransformGohma* this, PlayState* play);
void TransformGohma_Action_Attack(TransformGohma* this, PlayState* play);
void TransformGohma_Action_PrepareAttack(TransformGohma* this, PlayState* play);

#define GRAVITY -2.0f
#define SPEED_CAP 10.0f
#define CLIMB_SPEED 7.0f

ActorProfile Transform_Gohma_Profile = {
    /**/ ACTOR_TRANSFORM_GOHMA,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_GOMA,
    /**/ sizeof(TransformGohma),
    /**/ TransformGohma_Init,
    /**/ TransformGohma_Destroy,
    /**/ TransformGohma_Update,
    /**/ TransformGohma_Draw,
};

static ColliderJntSphElementInit sColliderJntSphElementInit[13] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_EYE, { { 0, 0, 1200 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_TAIL4, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_TAIL3, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_TAIL2, { { 0, 0, 0 }, 12 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_TAIL1, { { 0, 0, 0 }, 25 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_R_FEET, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_R_SHIN, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_R_THIGH_SHELL, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_L_ANTENNA_CLAW, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_R_ANTENNA_CLAW, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_L_FEET, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_L_SHIN, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0xFFCFFFFF, 0x00, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_ON,
        },
        { BOSSGOMA_LIMB_L_THIGH_SHELL, { { 0, 0, 0 }, 15 }, 100 },
    },
};

static ColliderJntSphInit sColliderJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_PLAYER,
        COLSHAPE_JNTSPH,
    },
    13,
    sColliderJntSphElementInit,
};

void TransformGohma_PlayEffectsAndSfx(TransformGohma* this, PlayState* play, s16 arg2, s16 amountMinus1) {
    if (arg2 == 0 || arg2 == 1 || arg2 == 3) {
        Actor_SpawnFloorDustRing(play, &this->actor, &this->rightHandBackLimbWorldPos, 25.0f, amountMinus1, 8.0f, 500,
                                 10, true);
    }

    if (arg2 == 0 || arg2 == 2 || arg2 == 3) {
        Actor_SpawnFloorDustRing(play, &this->actor, &this->leftHandBackLimbWorldPos, 25.0f, amountMinus1, 8.0f, 500,
                                 10, true);
    }

    if (arg2 == 0) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_DOWN);
    } else {
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_WALK);
    }
}

void TransformGohma_SetupAction(TransformGohma* this, PlayState* play, TransformGohmaActionFunc actionFunc) {
    this->actionFunc = actionFunc;

    this->visualState = VISUALSTATE_DEFAULT;
    this->actor.gravity = GRAVITY;
    if (this->actionFunc == TransformGohma_Action_Idle) {
        this->actor.shape.rot.x = 0;
        Animation_Change(&this->skelAnime, &gGohmaIdleCrouchedAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGohmaIdleCrouchedAnim), ANIMMODE_LOOP, 4.0f);
        Interface_SetDoAction(play, DO_ACTION_ATTACK);
    }
    else if (this->actionFunc == TransformGohma_Action_Walk) {
        Animation_Change(&this->skelAnime, &gGohmaWalkCrouchedAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGohmaWalkCrouchedAnim), ANIMMODE_LOOP, -5.0f);
        Interface_SetDoAction(play, DO_ACTION_ATTACK);
    }
    else if (this->actionFunc == TransformGohma_Action_GetHit) {
        Animation_Change(&this->skelAnime, &gGohmaDamageAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGohmaDamageAnim), ANIMMODE_ONCE_INTERP, 4.0f);
        this->actor.speed = 0.0f;
    }
    else if (this->actionFunc == TransformGohma_Action_HangCeiling) {
        Animation_Change(&this->skelAnime, &gGohmaHangAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGohmaHangAnim), ANIMMODE_LOOP, 4.0f);
    }
    else if (this->actionFunc == TransformGohma_Action_Fall) {
        Animation_Change(&this->skelAnime, &gGohmaLandAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGohmaLandAnim), ANIMMODE_LOOP, -5.0f);
        this->actor.speed = 0.0f;
        this->actor.velocity.y = 0.0f;
        Interface_SetDoAction(play, DO_ACTION_NONE);
    }
    else if (this->actionFunc == TransformGohma_Action_StartClimb) {
        Animation_Change(&this->skelAnime, &gGohmaClimbAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGohmaClimbAnim), ANIMMODE_LOOP, -10.0f);
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
        Interface_SetDoAction(play, DO_ACTION_NONE);
    }
    else if (this->actionFunc == TransformGohma_Action_Climb) {
        Animation_Change(&this->skelAnime, &gGohmaClimbAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGohmaClimbAnim), ANIMMODE_LOOP, -10.0f);
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
        Interface_SetDoAction(play, DO_ACTION_DOWN);
    }
    else if (this->actionFunc == TransformGohma_Action_Land) {
        Animation_Change(&this->skelAnime, &gGohmaLandAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGohmaLandAnim), ANIMMODE_ONCE_INTERP, 4.0f);
        this->actor.speed = 0.0f;
    }
    else if (this->actionFunc == TransformGohma_Action_Attack) {
        Animation_Change(&this->skelAnime, &gGohmaAttackAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGohmaAttackAnim), ANIMMODE_ONCE_INTERP, 4.0f);
        this->actor.speed = 0.0f;
        this->visualState = VISUALSTATE_RED;
        
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_CRY1);
    }
    else if (this->actionFunc == TransformGohma_Action_PrepareAttack) {
        Animation_Change(&this->skelAnime, &gGohmaPrepareAttackAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gGohmaPrepareAttackAnim), ANIMMODE_ONCE_INTERP, 4.0f);
        this->actor.speed = 0.0f;
        this->visualState = VISUALSTATE_RED;
        Interface_SetDoAction(play, DO_ACTION_NONE);
    }
}

void TransformGohma_CheckAttack(TransformGohma* this, PlayState* play) {
    if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_A)) {
        TransformGohma_SetupAction(this, play, TransformGohma_Action_PrepareAttack);
    }
}

void TransformGohma_CheckWallClimb(TransformGohma* this, PlayState* play, s16 yawTarget) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
        s16 invertedWallYaw;
        s32 yawDiff;
        invertedWallYaw = this->actor.wallYaw + (s16)0x8000;
        yawDiff = ((s32)invertedWallYaw) - ((s32)yawTarget);
        if (ABS(yawDiff) < 0x4000) {
            TransformGohma_SetupAction(this, play, TransformGohma_Action_StartClimb);
        }
    }
}

void TransformGohma_Action_Idle(TransformGohma* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 1, play);

    if (speedTarget != 0.0f) {
        TransformGohma_SetupAction(this, play, TransformGohma_Action_Walk);
    }
    else {
        Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, 1200);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    TransformGohma_CheckAttack(this, play);

    SkelAnime_Update(&this->skelAnime);
}

void TransformGohma_Action_Walk(TransformGohma* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    s32 angleDiff;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 1, play);

    Math_StepToAngleS(&this->actor.shape.rot.y, yawTarget, 2000);
    angleDiff = (s32)yawTarget - (s32)this->actor.shape.rot.y;
    if (ABS(angleDiff) < 2000) {
        this->actor.shape.rot.y = yawTarget;
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    Math_StepToF(&this->actor.speed, speedTarget, 0.9f);

    if (this->actor.speed == 0.0f) {
        TransformGohma_SetupAction(this, play, TransformGohma_Action_Idle);
    }

    TransformGohma_CheckAttack(this, play);
    TransformGohma_CheckWallClimb(this, play, yawTarget);

    SkelAnime_Update(&this->skelAnime);

    if (Animation_OnFrame(&this->skelAnime, 15.0f)) {
        TransformGohma_PlayEffectsAndSfx(this, play, 1, 3);
    } else if (Animation_OnFrame(&this->skelAnime, 30.0f)) {
        TransformGohma_PlayEffectsAndSfx(this, play, 2, 3);
    }
}

void TransformGohma_Action_GetHit(TransformGohma* this, PlayState* play) {
}

void TransformGohma_Action_HangCeiling(TransformGohma* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
}

void TransformGohma_Action_Fall(TransformGohma* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    Math_ApproachS(&this->actor.shape.rot.x, 0, 2, 3000);

    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        TransformGohma_SetupAction(this, play, TransformGohma_Action_Idle); // TODO land action?
        this->actor.velocity.y = 0.0f;
        TransformGohma_PlayEffectsAndSfx(this, play, 0, 8);
        Actor_RequestQuakeAndRumble(&this->actor, play, 5, 15);
    }
}

void TransformGohma_Action_StartClimb(TransformGohma* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    Math_ApproachF(&this->actor.speed, 3.0f, 0.5f, 2.0f);
    Math_ApproachF(&this->actor.velocity.y, 5.0f, 0.5f, 2.0f);
    Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 2, 2000);
    Math_ApproachS(&this->actor.world.rot.y, this->actor.wallYaw + 0x8000, 2, 1500);
    this->actor.shape.rot.y = this->actor.world.rot.y;

    if (Animation_OnFrame(&this->skelAnime, 8.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_CLIM);
    }

    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_WALL)) {
        if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
            osSyncPrintf("TransformGohma: StartClimb -> Idle\n");
            TransformGohma_SetupAction(this, play, TransformGohma_Action_Idle);
        }
        else {
            osSyncPrintf("TransformGohma: StartClimb -> Fall\n");
            TransformGohma_SetupAction(this, play, TransformGohma_Action_Fall);
        }
    }

    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        osSyncPrintf("TransformGohma: StartClimb -> Climb\n");
        TransformGohma_SetupAction(this, play, TransformGohma_Action_Climb);
    }
}

void TransformGohma_Action_Climb(TransformGohma* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    s32 angleDiff;

    Math_ApproachF(&this->actor.speed, 3.0f, 0.5f, 2.0f);
    Math_ApproachF(&this->actor.velocity.y, CLIMB_SPEED, 0.5f, 2.0f);
    Math_ApproachS(&this->actor.shape.rot.x, -0x4000, 2, 2000);
    Math_ApproachS(&this->actor.world.rot.y, this->actor.wallYaw + 0x8000, 2, 1500);
    this->actor.shape.rot.y = this->actor.world.rot.y;

    SkelAnime_Update(&this->skelAnime);

    if (Animation_OnFrame(&this->skelAnime, 8.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_CLIM);
    }

    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        osSyncPrintf("TransformGohma: Climb -> Idle\n");
        TransformGohma_SetupAction(this, play, TransformGohma_Action_Idle);
    }
    
    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_WALL) || (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_A))) {
        osSyncPrintf("TransformGohma: Climb -> Fall\n");
        TransformGohma_SetupAction(this, play, TransformGohma_Action_Fall);
    }

    if (this->actor.bgCheckFlags & BGCHECKFLAG_CEILING) {
        osSyncPrintf("TransformGohma: Climb -> HangCeiling\n");
        TransformGohma_SetupAction(this, play, TransformGohma_Action_HangCeiling);
    }
}

void TransformGohma_Action_Land(TransformGohma* this, PlayState* play) {
}

void TransformGohma_Action_Attack(TransformGohma* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        TransformGohma_SetupAction(this, play, TransformGohma_Action_Idle);
    }

    if (Animation_OnFrame(&this->skelAnime, 10.0f)) {
        TransformGohma_PlayEffectsAndSfx(this, play, 3, 5);
        Actor_RequestQuakeAndRumble(&this->actor, play, 5, 15);
    }
}

void TransformGohma_Action_PrepareAttack(TransformGohma* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        TransformGohma_SetupAction(this, play, TransformGohma_Action_Attack);
    }
}

void TransformGohma_Init(Actor* thisx, PlayState* play) {
    TransformGohma* this = (TransformGohma*)thisx;
    ActorShape_Init(&this->actor.shape, 4000.0f, ActorShadow_DrawCircle, 150.0f);
    Actor_SetScale(&this->actor, 0.01f);
    SkelAnime_Init(play, &this->skelAnime, &gGohmaSkel, &gGohmaIdleCrouchedAnim, this->jointTable, this->morphTable, BOSSGOMA_LIMB_MAX);

    this->actor.speedCap = SPEED_CAP;
    this->actor.gravity = GRAVITY;
    this->eyeIrisScaleX = 1.0f;
    this->eyeIrisScaleY = 1.0f;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    this->invincibilityFrames = 0;

    Collider_InitJntSph(play, &this->collider);
    Collider_SetJntSph(play, &this->collider, &this->actor, &sColliderJntSphInit, this->colliderItems);

    TransformGohma_SetupAction(this, play, TransformGohma_Action_Idle);
    
    this->actor.speed = GET_PLAYER(play)->actor.speed;
    this->actor.room = -1;
}

void TransformGohma_Destroy(Actor* thisx, PlayState* play) {
    TransformGohma* this = (TransformGohma*)thisx;

    Collider_DestroyJntSph(play, &this->collider);
}

void TransformGohma_UpdateMainEnvColor(TransformGohma* this) {
    static f32 colors1[][3] = {
        { 255.0f, 17.0f, 0.0f },  { 0.0f, 255.0f, 170.0f }, { 50.0f, 50.0f, 50.0f },
        { 0.0f, 255.0f, 170.0f }, { 0.0f, 255.0f, 170.0f }, { 0.0f, 255.0f, 170.0f },
    };
    static f32 colors2[][3] = {
        { 255.0f, 17.0f, 0.0f },  { 0.0f, 255.0f, 170.0f }, { 50.0f, 50.0f, 50.0f },
        { 0.0f, 255.0f, 170.0f }, { 0.0f, 0.0f, 255.0f },   { 255.0f, 17.0f, 0.0f },
    };

    if (this->visualState == VISUALSTATE_RED) {
        Math_ApproachF(&this->mainEnvColor[0], 50.0f, 0.5f, 20.0f);
        Math_ApproachF(&this->mainEnvColor[1], 50.0f, 0.5f, 20.0f);
        Math_ApproachF(&this->mainEnvColor[2], 50.0f, 0.5f, 20.0f);
    } else if (this->visualState == VISUALSTATE_DEFAULT) {
            this->mainEnvColor[0] = colors2[this->visualState][0];
            this->mainEnvColor[1] = colors2[this->visualState][1];
            this->mainEnvColor[2] = colors2[this->visualState][2];
    } else if (this->visualState == VISUALSTATE_DEFEATED) {
            this->mainEnvColor[0] = colors1[this->visualState][0];
            this->mainEnvColor[1] = colors1[this->visualState][1];
            this->mainEnvColor[2] = colors1[this->visualState][2];
    } else {
        Math_ApproachF(&this->mainEnvColor[0], colors1[this->visualState][0], 0.5f, 20.0f);
        Math_ApproachF(&this->mainEnvColor[1], colors1[this->visualState][1], 0.5f, 20.0f);
        Math_ApproachF(&this->mainEnvColor[2], colors1[this->visualState][2], 0.5f, 20.0f);
    }
}

void TransformGohma_UpdateEyeEnvColor(TransformGohma* this) {
    static f32 targetEyeEnvColors[][3] = {
        { 255.0f, 17.0f, 0.0f },  { 255.0f, 255.0f, 255.0f }, { 50.0f, 50.0f, 50.0f },
        { 0.0f, 255.0f, 170.0f }, { 0.0f, 255.0f, 170.0f },   { 0.0f, 255.0f, 170.0f },
    };

    Math_ApproachF(&this->eyeEnvColor[0], targetEyeEnvColors[this->visualState][0], 0.5f, 20.0f);
    Math_ApproachF(&this->eyeEnvColor[1], targetEyeEnvColors[this->visualState][1], 0.5f, 20.0f);
    Math_ApproachF(&this->eyeEnvColor[2], targetEyeEnvColors[this->visualState][2], 0.5f, 20.0f);
}

void TransformGohma_UpdateTailLimbsScale(TransformGohma* this) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(this->tailLimbsScaleTimers); i++) {
        if (this->tailLimbsScaleTimers[i] != 0) {
            this->tailLimbsScaleTimers[i]--;
            Math_ApproachF(&this->tailLimbsScale[i], 1.5f, 0.2f, 0.1f);
        } else {
            Math_ApproachF(&this->tailLimbsScale[i], 1.0f, 0.2f, 0.1f);
        }
    }
}

void TransformGohma_Update(Actor* thisx, PlayState* play) {
    TransformGohma* this = (TransformGohma*)thisx;

    Player* player = GET_PLAYER(play);

    player->actor.world.pos.x = this->actor.world.pos.x;
    player->actor.world.pos.y = this->actor.world.pos.y;
    player->actor.world.pos.z = this->actor.world.pos.z;

    Math_Vec3f_Copy(&player->actor.world.pos, &this->actor.world.pos);
    Math_Vec3f_Copy(&player->actor.home.pos, &this->actor.world.pos);
    Math_Vec3f_Copy(&player->actor.prevPos, &this->actor.world.pos);
    player->actor.world.rot.x = this->actor.world.rot.x;
    player->actor.world.rot.y = this->actor.world.rot.y;
    player->actor.world.rot.z = this->actor.world.rot.z;
    player->actor.shape.rot.x = this->actor.shape.rot.x;
    player->actor.shape.rot.y = this->actor.shape.rot.y;
    player->actor.shape.rot.z = this->actor.shape.rot.z;

    if (this->invincibilityFrames > 0) {
        this->invincibilityFrames--;
    }

    Actor_HandleZTarget(&this->actor, play);
    Actor_MoveXZGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 90.0f, 80.0f, UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2);

    TransformGohma_UpdateMainEnvColor(this);
    TransformGohma_UpdateEyeEnvColor(this);
    TransformGohma_UpdateTailLimbsScale(this);

    this->actionFunc(this, play);

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
}



s32 TransformGohma_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    TransformGohma* this = (TransformGohma*)thisx;
    s32 doNotDrawLimb = false;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, (s16)this->mainEnvColor[0], (s16)this->mainEnvColor[1], (s16)this->mainEnvColor[2],
                   255);

    switch (limbIndex) {
        case BOSSGOMA_LIMB_EYE:
            if (this->invincibilityFrames != 0) {
                gDPSetEnvColor(POLY_OPA_DISP++, (s16)(Rand_ZeroOne() * 255.0f), (s16)(Rand_ZeroOne() * 255.0f),
                               (s16)(Rand_ZeroOne() * 255.0f), 63);
            } else {
                gDPSetEnvColor(POLY_OPA_DISP++, (s16)this->eyeEnvColor[0], (s16)this->eyeEnvColor[1],
                               (s16)this->eyeEnvColor[2], 63);
            }
            break;

        case BOSSGOMA_LIMB_EYE_LID_BOTTOM_ROOT2:
            rot->x += this->eyeLidBottomRotX;
            break;

        case BOSSGOMA_LIMB_EYE_LID_TOP_ROOT2:
            rot->x += this->eyeLidTopRotX;
            break;

        case BOSSGOMA_LIMB_IRIS_ROOT2:
            rot->x += this->eyeIrisRotX;
            rot->y += this->eyeIrisRotY;
            break;

        case BOSSGOMA_LIMB_IRIS:
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);

            Matrix_TranslateRotateZYX(pos, rot);

            if (*dList != NULL) {
                Matrix_Push();
                Matrix_Scale(this->eyeIrisScaleX, this->eyeIrisScaleY, 1.0f, MTXMODE_APPLY);
                gSPMatrix(POLY_OPA_DISP++, MATRIX_NEW(play->state.gfxCtx, __FILE__, __LINE__),
                            G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, *dList);
                Matrix_Pop();
            }

            doNotDrawLimb = true;
            break;

        case BOSSGOMA_LIMB_TAIL4:
        case BOSSGOMA_LIMB_TAIL3:
        case BOSSGOMA_LIMB_TAIL2:
        case BOSSGOMA_LIMB_TAIL1:
            Matrix_TranslateRotateZYX(pos, rot);

            if (*dList != NULL) {
                Matrix_Push();
                Matrix_Scale(this->tailLimbsScale[limbIndex - BOSSGOMA_LIMB_TAIL4],
                             this->tailLimbsScale[limbIndex - BOSSGOMA_LIMB_TAIL4],
                             this->tailLimbsScale[limbIndex - BOSSGOMA_LIMB_TAIL4], MTXMODE_APPLY);
                gSPMatrix(POLY_OPA_DISP++, MATRIX_NEW(play->state.gfxCtx, __FILE__, __LINE__),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, *dList);
                Matrix_Pop();
            }

            doNotDrawLimb = true;
            break;
    }

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    return doNotDrawLimb;
}

void TransformGohma_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
    static Vec3f tailZero = { 0.0f, 0.0f, 0.0f };
    static Vec3f clawBackLocalPos = { 0.0f, 0.0f, 0.0f };
    static Vec3f focusEyeLocalPos = { 0.0f, 300.0f, 2650.0f }; // in the center of the surface of the lens
    static Vec3f zero = { 0.0f, 0.0f, 0.0f };
    Vec3f childPos;
    Vec3s childRot;
    TransformGohma* this = (TransformGohma*)thisx;
    MtxF mtx;

    if (limbIndex == BOSSGOMA_LIMB_TAIL4) { // tail end/last part
        Matrix_MultVec3f(&tailZero, &this->lastTailLimbWorldPos);
    } else if (limbIndex == BOSSGOMA_LIMB_TAIL1) { // tail start/first part
        Matrix_MultVec3f(&tailZero, &this->firstTailLimbWorldPos);
    } else if (limbIndex == BOSSGOMA_LIMB_EYE) {
        Matrix_MultVec3f(&focusEyeLocalPos, &this->actor.focus.pos);
    } else if (limbIndex == BOSSGOMA_LIMB_R_FEET_BACK) {
        Matrix_MultVec3f(&clawBackLocalPos, &this->rightHandBackLimbWorldPos);
    } else if (limbIndex == BOSSGOMA_LIMB_L_FEET_BACK) {
        Matrix_MultVec3f(&clawBackLocalPos, &this->leftHandBackLimbWorldPos);
    }

    Collider_UpdateSpheres(limbIndex, &this->collider);
}

Gfx* TransformGohma_EmptyDlist(GraphicsContext* gfxCtx) {
    Gfx* dListHead;
    Gfx* dList;

    dList = dListHead = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 1);

    gSPEndDisplayList(dListHead++);

    return dList;
}

void TransformGohma_Draw(Actor* thisx, PlayState* play) {
    TransformGohma* this = (TransformGohma*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    Matrix_Translate(0.0f, -4000.0f, 0.0f, MTXMODE_APPLY);

    gSPSegment(POLY_OPA_DISP++, 0x08, TransformGohma_EmptyDlist(play->state.gfxCtx));

    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, TransformGohma_OverrideLimbDraw,
                      TransformGohma_PostLimbDraw, this);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

