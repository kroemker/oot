/*
 * File: z_transform_baby_gohma.c
 * Overlay: ovl_Transform_Baby_Gohma
 * Description: Play as baby gohma
 */

#include "z_transform_baby_gohma.h"
#include "assets/objects/object_gol/object_gol.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

void TransformBabyGohma_Init(Actor* thisx, PlayState* play);
void TransformBabyGohma_Destroy(Actor* thisx, PlayState* play);
void TransformBabyGohma_Update(Actor* thisx, PlayState* play);
void TransformBabyGohma_Draw(Actor* thisx, PlayState* play);

void TransformBabyGohma_Action_Cutscene(TransformBabyGohma* this, PlayState* play);
void TransformBabyGohma_Action_Idle(TransformBabyGohma* this, PlayState* play);
void TransformBabyGohma_Action_Run(TransformBabyGohma* this, PlayState* play);
void TransformBabyGohma_Action_PrepareJump(TransformBabyGohma* this, PlayState* play);
void TransformBabyGohma_Action_Jump(TransformBabyGohma* this, PlayState* play);
void TransformBabyGohma_Action_HeadAttack(TransformBabyGohma* this, PlayState* play);
void TransformBabyGohma_Action_Land(TransformBabyGohma* this, PlayState* play);
void TransformBabyGohma_Action_GetHit(TransformBabyGohma* this, PlayState* play);

#define GRAVITY -1.0f
#define SPEED_CAP 7.0f

ActorProfile Transform_Baby_Gohma_Profile = {
    /**/ ACTOR_TRANSFORM_BABY_GOHMA,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_GOL,
    /**/ sizeof(TransformBabyGohma),
    /**/ TransformBabyGohma_Init,
    /**/ TransformBabyGohma_Destroy,
    /**/ TransformBabyGohma_Update,
    /**/ TransformBabyGohma_Draw,
};

static ColliderCylinderInit sAttackCollider = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x20, 0x00, 0x08 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        ATELEM_ON | ATELEM_SFX_NORMAL,
        ACELEM_NONE,
        OCELEM_ON,
    },
    { 15, 30, 10, { 0, 0, 0 } },
};

static ColliderCylinderInit sBodyCollider = {
    {
        COLTYPE_HIT3,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        ATELEM_NONE,
        ACELEM_ON,
        OCELEM_ON,
    },
    { 15, 30, 10, { 0, 0, 0 } },
};


void TransformBabyGohma_SetupAction(TransformBabyGohma* this, PlayState* play, TransformBabyGohmaActionFunc actionFunc) {
    this->actionFunc = actionFunc;

    this->eyeColorIndex = 1;
    if (this->actionFunc == TransformBabyGohma_Action_Cutscene) {
        Animation_Change(&this->skelAnime, &gObjectGolStandAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gObjectGolStandAnim), ANIMMODE_LOOP, 8.0f);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    if (this->actionFunc == TransformBabyGohma_Action_Idle) {
        Animation_Change(&this->skelAnime, &gObjectGolStandAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gObjectGolStandAnim), ANIMMODE_LOOP, 4.0f);
        Interface_SetDoAction(play, DO_ACTION_JUMP);
        Interface_LoadActionLabelB(play, DO_ACTION_ATTACK);
        this->idleTimer = 80;
    }
    else if (this->actionFunc == TransformBabyGohma_Action_Run) {
        Animation_Change(&this->skelAnime, &gObjectGolRunningAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gObjectGolRunningAnim), ANIMMODE_LOOP, 4.0f);
        Interface_SetDoAction(play, DO_ACTION_JUMP);
        Interface_LoadActionLabelB(play, DO_ACTION_ATTACK);
    }
    else if (this->actionFunc == TransformBabyGohma_Action_PrepareJump) {
        this->actor.speed = 0.0f;
        this->eyeColorIndex = 0;
        Animation_Change(&this->skelAnime, &gObjectGolPrepareJumpAnim, 4.0f, 0.0f, Animation_GetLastFrame(&gObjectGolPrepareJumpAnim), ANIMMODE_ONCE, 0.0f);
    }
    else if (this->actionFunc == TransformBabyGohma_Action_Jump) {
        this->actor.speed = CLAMP(this->framesAPressed * 1.2f + 10.0f, 10.0f, 20.0f);
        this->actor.velocity.y = CLAMP(this->framesAPressed * 0.6f + 8.0f, 8.0f, 12.0f);
        this->framesAPressed = 0;
        Animation_Change(&this->skelAnime, &gObjectGolJumpHeadbuttAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gObjectGolJumpHeadbuttAnim), ANIMMODE_ONCE_INTERP, -2.0f);
        
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_BJR_CRY);
        this->eyeColorIndex = 0;
    }
    else if (this->actionFunc == TransformBabyGohma_Action_HeadAttack) {
        this->actor.speed = 0.0f;
        this->eyeColorIndex = 0;
        Animation_Change(&this->skelAnime, &gObjectGolPrepareJumpAnim, 3.0f, 0.0f, Animation_GetLastFrame(&gObjectGolPrepareJumpAnim), ANIMMODE_ONCE_INTERP, -2.0f);
    }
    else if (this->actionFunc == TransformBabyGohma_Action_Land) {
        this->actor.speed = 0.0f;
        Animation_Change(&this->skelAnime, &gObjectGolLandFromJumpAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gObjectGolLandFromJumpAnim), ANIMMODE_ONCE_INTERP, -2.0f);
    }
    else if (this->actionFunc == TransformBabyGohma_Action_GetHit) {
        this->actor.speed = 0.0f;
        Animation_Change(&this->skelAnime, &gObjectGolDamagedAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gObjectGolDamagedAnim), ANIMMODE_ONCE_INTERP, -2.0f);
    }
}

void TransformBabyGohma_CheckJump(TransformBabyGohma* this, PlayState* play) {
    if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_A)) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_PrepareJump);
    }
}

void TransformBabyGohma_CheckHeadAttack(TransformBabyGohma* this, PlayState* play) {
    if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_B)) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_HeadAttack);
    }
}

void TransformBabyGohma_UpdateWaterMovement(TransformBabyGohma* this, PlayState* play) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_WATER) {
        this->actor.world.pos.y += this->actor.depthInWater;
    }
}

void TransformBabyGohma_SpawnWaterRipple(TransformBabyGohma* this, PlayState* play, s8 leg) {
    Vec3f pos;

    if (this->actor.bgCheckFlags & BGCHECKFLAG_WATER) {
        Math_Vec3f_Copy(&pos, &this->actor.world.pos);
        pos.x += (leg * 2 - 1) * Math_SinS(this->actor.world.rot.y + 0x4000) * 17.0f;
        pos.z += (leg * 2 - 1) * Math_CosS(this->actor.world.rot.y + 0x4000) * 17.0f;
        EffectSsGRipple_Spawn(play, &pos, 100, 200, 0);
    }
}

void TransformBabyGohma_Action_Cutscene(TransformBabyGohma* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);

    Math_StepToF(&this->actor.speed, 0.0f, 0.9f);

    if (player->csAction == PLAYER_CSACTION_NONE) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Idle);
    }
}

void TransformBabyGohma_Action_Idle(TransformBabyGohma* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 1, play);

    if (speedTarget != 0.0f) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Run);
    }
    else {
        Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, 1200);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    if (DECR(this->idleTimer) == 0) {
        this->eyeColorIndex = this->eyeColorIndex % 2 + 1;
        this->idleTimer = 80;
    }

    
    if (Animation_OnFrame(&this->skelAnime, 8.0f)) {
        TransformBabyGohma_SpawnWaterRipple(this, play, 0);
        TransformBabyGohma_SpawnWaterRipple(this, play, 1);
    }

    TransformBabyGohma_CheckJump(this, play);
    TransformBabyGohma_CheckHeadAttack(this, play);

    SkelAnime_Update(&this->skelAnime);
}

void TransformBabyGohma_Action_Run(TransformBabyGohma* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 1, play);

    this->actor.world.rot.y = this->actor.shape.rot.y = yawTarget;
    Math_StepToF(&this->actor.speed, speedTarget, 0.9f);

    if (this->actor.speed == 0.0f) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Idle);
    }

    TransformBabyGohma_CheckJump(this, play);
    TransformBabyGohma_CheckHeadAttack(this, play);

    SkelAnime_Update(&this->skelAnime);

    if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
        TransformBabyGohma_SpawnWaterRipple(this, play, 1);
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_JR_WALK);
    }
    else if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        TransformBabyGohma_SpawnWaterRipple(this, play, 0);
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_BJR_WALK);
    }
}

void TransformBabyGohma_Action_PrepareJump(TransformBabyGohma* this, PlayState* play) {
    s32 finished = SkelAnime_Update(&this->skelAnime);
    if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_B)) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Idle);
    } else if (CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_A)) {
        this->framesAPressed++;
    } else if (finished) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Jump);
    }
}

void TransformBabyGohma_Action_Jump(TransformBabyGohma* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    
    if ((this->actor.speed != 0.0f) && (this->actor.bgCheckFlags & BGCHECKFLAG_WALL)) {
        s16 yawDiff = this->actor.wallYaw - this->actor.world.rot.y;
        if (ABS(yawDiff) > 0x4000) {
            this->actor.world.rot.y = this->actor.shape.rot.y = ((this->actor.wallYaw - this->actor.world.rot.y) + this->actor.wallYaw) - 0x8000;
        }
        Actor_PlaySfx(&this->actor, NA_SE_EV_BOMB_BOUND);
        this->actor.speed *= 0.8f;
        this->actor.bgCheckFlags &= ~BGCHECKFLAG_WALL;
    }

    if (this->actor.velocity.y <= 0.0f && ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) || (this->actor.bgCheckFlags & BGCHECKFLAG_WATER))) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Land);
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_BJR_LAND2);
        //Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_JR_LAND2);
    }
}

void TransformBabyGohma_Action_HeadAttack(TransformBabyGohma* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Idle);
    }
}

void TransformBabyGohma_Action_Land(TransformBabyGohma* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Idle);
    }
}

void TransformBabyGohma_Action_GetHit(TransformBabyGohma* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Idle);
    }
}

void TransformBabyGohma_Init(Actor* thisx, PlayState* play) {
    TransformBabyGohma* this = (TransformBabyGohma*)thisx;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 40.0f);
    Actor_SetScale(&this->actor, 0.01f);
    SkelAnime_Init(play, &this->skelAnime, &gObjectGolSkel, &gObjectGolStandAnim, this->jointTable, this->morphTable, 24);

    Collider_InitCylinder(play, &this->attackCol);
    Collider_SetCylinder(play, &this->attackCol, &this->actor, &sAttackCollider);
    Collider_InitCylinder(play, &this->bodyCol);
    Collider_SetCylinder(play, &this->bodyCol, &this->actor, &sBodyCollider);

    this->actor.speedCap = SPEED_CAP;
    this->actor.gravity = GRAVITY;

    TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Idle);
    
    this->actor.speed = GET_PLAYER(play)->actor.speed;
    this->actor.room = -1;
}

void TransformBabyGohma_Destroy(Actor* thisx, PlayState* play) {
    TransformBabyGohma* this = (TransformBabyGohma*)thisx;
    
    Collider_DestroyCylinder(play, &this->attackCol);
    Collider_DestroyCylinder(play, &this->bodyCol);
}

void TransformBabyGohma_UpdateHit(TransformBabyGohma* this, PlayState* play) {
    if (this->hurtTimer != 0) {
        this->hurtTimer--;
        return;
    }

    if (this->bodyCol.base.acFlags & AC_HIT) {
        this->bodyCol.base.acFlags &= ~AC_HIT;

        Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 12);

        play->damagePlayer(play, -this->actor.colChkInfo.damage);

        if (gSaveContext.save.info.playerData.health == 0) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_BJR_DEAD);
            //Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_JR_DEAD);
            Enemy_StartFinishingBlow(play, &this->actor);
            Actor_Kill(&this->actor);
        }
        
        Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_BJR_DAM1);
        //Actor_PlaySfx(&this->actor, NA_SE_EN_GOMA_JR_DAM1);

        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_GetHit);
        this->hurtTimer = 10;
        this->invincibilityFrames = 20;
    }
}

void TransformBabyGohma_UpdateEyeEnvColor(TransformBabyGohma* this) {
    f32 step;
    static f32 sTargetEyeEnvColors[][3] = {
        { 255.0f, 0.0f, 170.0f },
        { 17.0f, 255.0f, 255.0f },
        { 0.0f, 170.0f, 0.0f },
    };

    step = this->actionFunc == TransformBabyGohma_Action_HeadAttack ? 60.0f : 20.0f;

    Math_ApproachF(&this->eyeEnvColor[0], sTargetEyeEnvColors[0][this->eyeColorIndex], 0.5f, step);
    Math_ApproachF(&this->eyeEnvColor[1], sTargetEyeEnvColors[1][this->eyeColorIndex], 0.5f, step);
    Math_ApproachF(&this->eyeEnvColor[2], sTargetEyeEnvColors[2][this->eyeColorIndex], 0.5f, step);
}

void TransformBabyGohma_SetFloorRot(TransformBabyGohma* this) {
    f32 nx;
    f32 ny;
    f32 nz;

    if (this->actor.floorPoly != NULL) {
        nx = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.x);
        ny = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.y);
        nz = COLPOLY_GET_NORMAL(this->actor.floorPoly->normal.z);
        Math_ApproachS(&this->slopePitch, RAD_TO_BINANG(-Math_FAtan2F(-nz * ny, 1.0f)), 1, 1000);
        Math_ApproachS(&this->slopeRoll, RAD_TO_BINANG(Math_FAtan2F(-nx * ny, 1.0f)), 1, 1000);
    }
}

void TransformBabyGohma_Update(Actor* thisx, PlayState* play) {
    TransformBabyGohma* this = (TransformBabyGohma*)thisx;
    Player* player = GET_PLAYER(play);

    Actor_SetPlayerLocation(&this->actor, play, 20.0f);
    Actor_SetFocus(&this->actor, 20.0f);

    Math_SmoothStepToF(&this->actor.scale.x, 0.01f, 0.5f, 0.00075f, 0.000001f);
    Math_SmoothStepToF(&this->actor.scale.y, 0.01f, 0.5f, 0.00075f, 0.000001f);
    Math_SmoothStepToF(&this->actor.scale.z, 0.01f, 0.5f, 0.00075f, 0.000001f);

    TransformBabyGohma_UpdateHit(this, play);
    Actor_HandleZTarget(&this->actor, play);
    Actor_MoveXZGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 40.0f, 30.0f, 100.0f, UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2);
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        TransformBabyGohma_SetFloorRot(this);
    }
    else {
        this->slopePitch = 0;
        this->slopeRoll = 0;
    }
    TransformBabyGohma_UpdateWaterMovement(this, play);
    TransformBabyGohma_UpdateEyeEnvColor(this);
    Actor_TriggerDynapolyIfPossible(&this->actor, play);
    Actor_CheckVoidOut(&this->actor, play);

    if (player->csAction != PLAYER_CSACTION_NONE && this->actionFunc != TransformBabyGohma_Action_Cutscene) {
        TransformBabyGohma_SetupAction(this, play, TransformBabyGohma_Action_Cutscene);
    }

    this->actionFunc(this, play);

    Collider_UpdateCylinder(&this->actor, &this->attackCol);
    Collider_UpdateCylinder(&this->actor, &this->bodyCol);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->bodyCol.base);

    if (DECR(this->invincibilityFrames) == 0) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->bodyCol.base);
    }
    if ((this->actionFunc == TransformBabyGohma_Action_Jump) || (this->actionFunc == TransformBabyGohma_Action_HeadAttack)) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->attackCol.base);
    }
}

s32 TransformBabyGohma_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    TransformBabyGohma* this = (TransformBabyGohma*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
    gDPSetEnvColor(POLY_OPA_DISP++, (s16)this->eyeEnvColor[0], (s16)this->eyeEnvColor[1], (s16)this->eyeEnvColor[2],
                   255);

    if (limbIndex == GOMA_LIMB_EYE_IRIS_ROOT1) {
        rot->x += this->eyePitch;
        rot->y += this->eyeYaw;
    } else if (limbIndex == GOMA_LIMB_BODY && this->hurtTimer != 0) {
        gDPSetEnvColor(POLY_OPA_DISP++, (s16)(Rand_ZeroOne() * 255.0f), (s16)(Rand_ZeroOne() * 255.0f),
                       (s16)(Rand_ZeroOne() * 255.0f), 255);
    }

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
    return 0;
}

void TransformBabyGohma_Draw(Actor* thisx, PlayState* play) {
    TransformBabyGohma* this = (TransformBabyGohma*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    Matrix_Translate(this->actor.world.pos.x,
                    this->actor.world.pos.y + ((this->actor.shape.yOffset * this->actor.scale.y) + play->mainCamera.quakeOffset.y),
                    this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateX(BINANG_TO_RAD_ALT(this->slopePitch), MTXMODE_APPLY);
    Matrix_RotateZ(BINANG_TO_RAD_ALT(this->slopeRoll), MTXMODE_APPLY);
    Matrix_RotateY(BINANG_TO_RAD_ALT(this->actor.shape.rot.y), MTXMODE_APPLY);
    Matrix_RotateX(BINANG_TO_RAD_ALT(this->actor.shape.rot.x), MTXMODE_APPLY);
    Matrix_RotateZ(BINANG_TO_RAD_ALT(this->actor.shape.rot.z), MTXMODE_APPLY);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, TransformBabyGohma_OverrideLimbDraw, NULL, this);
    
    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

