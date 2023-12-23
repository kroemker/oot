
#include "z_transform_keese.h"
#include "assets/objects/object_firefly/object_firefly.h"
#include "overlays/actors/ovl_Obj_Syokudai/z_obj_syokudai.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_IGNORE_QUAKE)

void TransformKeese_Init(Actor* thisx, PlayState* play);
void TransformKeese_Destroy(Actor* thisx, PlayState* play);
void TransformKeese_Update(Actor* thisx, PlayState* play2);
void TransformKeese_Draw(Actor* thisx, PlayState* play);

void TransformKeese_Action_Fly(TransformKeese* this, PlayState* play);
void TransformKeese_Action_Land(TransformKeese* this, PlayState* play);
void TransformKeese_Action_DiveAttack(TransformKeese* this, PlayState* play);

#define A_PRESS_Y_ACCEL 0.9f
#define MAX_Y_SPEED 2.9f
#define GRAVITY -0.5f
#define DIVE_ATTACK_SPEED_MULTIPLIER 1.84f
#define SPEED_CAP 4.0f

typedef enum {
    /* 0 */ KEESE_AURA_NONE, 
    /* 1 */ KEESE_AURA_FIRE,
    /* 2 */ KEESE_AURA_ICE
} KeeseAuraType;

ActorInit Transform_Keese_InitVars = {
    /**/ ACTOR_TRANSFORM_KEESE,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_FIREFLY,
    /**/ sizeof(TransformKeese),
    /**/ TransformKeese_Init,
    /**/ TransformKeese_Destroy,
    /**/ TransformKeese_Update,
    /**/ TransformKeese_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { DMG_ARROW_NORMAL, 0x01, 0x08 },
            { 0xFFCFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_HARD,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 1000, 0 }, 15 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_PLAYER,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 10, 10, 30 };


static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 5, ICHAIN_CONTINUE),
    ICHAIN_F32(minVelocityY, -4, ICHAIN_STOP)
};

void TransformKeese_Extinguish(TransformKeese* this) {
    this->actor.params += 2;
    this->collider.elements[0].info.toucher.effect = 0; // None
    this->auraType = KEESE_AURA_NONE;
    this->onFire = false;
}

void TransformKeese_Ignite(TransformKeese* this) {
    if (this->actor.params == KEESE_ICE_FLY) {
        this->actor.params = KEESE_FIRE_FLY;
    } else {
        this->actor.params -= 2;
    }
    this->collider.elements[0].info.toucher.effect = 1; // Fire
    this->auraType = KEESE_AURA_FIRE;
    this->onFire = true;
}

void TransformKeese_SetupAction(TransformKeese* this, PlayState* play, TransformKeeseActionFunc actionFunc) {
    this->actionFunc = actionFunc;

    Interface_SetDoAction(play, DO_ACTION_CLIMB);
    if (actionFunc == TransformKeese_Action_Fly) {
        this->targetPitch = 0x954;
        this->actor.gravity = GRAVITY;
        this->skelAnime.playSpeed = 1.0f;
        Interface_LoadActionLabelB(play, DO_ACTION_ATTACK);
    }
    else if (actionFunc == TransformKeese_Action_Land) {
        this->targetPitch = 0x954;
        this->actor.speed = 0.0f;
        this->actor.gravity = 0.0f;
        this->actor.velocity.y = 0.0f;
        Animation_Change(&this->skelAnime, &gKeeseFlyAnim, 0.5f, 0.0f, 0.0f, ANIMMODE_LOOP_INTERP, -3.0f);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (actionFunc == TransformKeese_Action_DiveAttack) {
        this->targetPitch = 0x2154;
        Interface_LoadActionLabelB(play, DO_ACTION_ATTACK);
    }
}

void TransformKeese_Action_Fly(TransformKeese* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, play);

    Math_StepToF(&this->actor.speed, speedTarget, 0.9f);
    if (speedTarget != 0.0f) {
        this->actor.world.rot.y = this->actor.shape.rot.y = yawTarget;
    }
    else {
        Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, 1200);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    if (CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_A)) {
        this->actor.velocity.y = MIN(this->actor.velocity.y + A_PRESS_Y_ACCEL, MAX_Y_SPEED);
    }

    this->skelAnime.playSpeed = (speedTarget / SPEED_CAP) * 0.75f + 0.25f; 
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_FFLY_FLY);
    }

    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        TransformKeese_SetupAction(this, play, TransformKeese_Action_Land);
    }
    else if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_B)) {
        TransformKeese_SetupAction(this, play, TransformKeese_Action_DiveAttack);
    }
}

void TransformKeese_Action_Land(TransformKeese* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, play);

    Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, 1200);
    this->actor.shape.rot.y = this->actor.world.rot.y;

    if (CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_A)) {
        this->actor.velocity.y = MIN(this->actor.velocity.y + A_PRESS_Y_ACCEL, MAX_Y_SPEED);
    }

    if (Animation_OnFrame(&this->skelAnime, 6.0f)) {
        this->skelAnime.playSpeed = 0.0f;
    }
    SkelAnime_Update(&this->skelAnime);

    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        TransformKeese_SetupAction(this, play, TransformKeese_Action_Fly);
    }
}

void TransformKeese_Action_DiveAttack(TransformKeese* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, play);

    Math_StepToF(&this->actor.speed, speedTarget * DIVE_ATTACK_SPEED_MULTIPLIER, 0.9f);
    if (speedTarget != 0.0f) {
        this->actor.world.rot.y = this->actor.shape.rot.y = yawTarget;
    }
    else {
        Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, 1200);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
        this->skelAnime.playSpeed = 0.0f;
        this->skelAnime.curFrame = 4.0f;
    }
    SkelAnime_Update(&this->skelAnime);

    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        TransformKeese_SetupAction(this, play, TransformKeese_Action_Land);
    }
    else if (!CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_B)) {
        TransformKeese_SetupAction(this, play, TransformKeese_Action_Fly);
    }
}

void TransformKeese_Init(Actor* thisx, PlayState* play) {
    TransformKeese* this = (TransformKeese*)thisx;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_Init(play, &this->skelAnime, &gKeeseSkeleton, &gKeeseFlyAnim, this->jointTable, this->morphTable, 28);
    Collider_InitJntSph(play, &this->collider);
    Collider_SetJntSph(play, &this->collider, &this->actor, &sJntSphInit, this->colliderItems);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &sColChkInfoInit);

    this->collider.elements[0].dim.worldSphere.radius = sJntSphInit.elements[0].dim.modelSphere.radius;

    this->actor.speedCap = SPEED_CAP;
    this->actor.gravity = GRAVITY;

    TransformKeese_SetupAction(this, play, TransformKeese_Action_Fly);
}

void TransformKeese_Destroy(Actor* thisx, PlayState* play) {
    TransformKeese* this = (TransformKeese*)thisx;

    Collider_DestroyJntSph(play, &this->collider);
}

void TransformKeese_Update(Actor* thisx, PlayState* play) {
    TransformKeese* this = (TransformKeese*)thisx;
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

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;

        Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 12);

        play->damagePlayer(play, -this->actor.colChkInfo.damage);
        Actor_PlaySfx(&this->actor, NA_SE_EN_FFLY_DEAD);

        if (gSaveContext.save.info.playerData.health == 0) {
            Enemy_StartFinishingBlow(play, &this->actor);
            Actor_Kill(&this->actor);
        }
    }

    Math_ScaledStepToS(&this->actor.shape.rot.x, this->targetPitch, 0x100);

    Actor_HandleZTarget(&this->actor, play);
    Actor_MoveXZGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 15.0f,
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2);
    this->collider.elements[0].dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.elements[0].dim.worldSphere.center.y = this->actor.world.pos.y + 10.0f;
    this->collider.elements[0].dim.worldSphere.center.z = this->actor.world.pos.z;

    Actor_SetFocus(&this->actor, 10.0f);

    this->actionFunc(this, play);

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);

    if ((this->actionFunc == TransformKeese_Action_DiveAttack)) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
    }
    if (gSaveContext.save.info.playerData.health > 0 && (this->actor.colorFilterTimer == 0)) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }
}

s32 TransformKeese_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx,
                               Gfx** gfx) {
    TransformKeese* this = (TransformKeese*)thisx;

    if (limbIndex == 1) {
        pos->y += 2300.0f;
    }
    return false;
}

void TransformKeese_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    static Color_RGBA8 fireAuraPrimColor = { 255, 255, 100, 255 };
    static Color_RGBA8 fireAuraEnvColor = { 255, 50, 0, 0 };
    static Color_RGBA8 iceAuraPrimColor = { 100, 200, 255, 255 };
    static Color_RGBA8 iceAuraEnvColor = { 0, 0, 255, 0 };
    static Vec3f effVelocity = { 0.0f, 0.5f, 0.0f };
    static Vec3f effAccel = { 0.0f, 0.5f, 0.0f };
    static Vec3f limbSrc = { 0.0f, 0.0f, 0.0f };
    Vec3f effPos;
    Vec3f* limbDest;
    Color_RGBA8* effPrimColor;
    Color_RGBA8* effEnvColor;
    MtxF mtx;
    s16 effScaleStep;
    s16 effLife;
    TransformKeese* this = (TransformKeese*)thisx;

    if (!this->onFire && (limbIndex == 27)) {
        gSPDisplayList((*gfx)++, gKeeseEyesDL);
    } else {
        if ((this->auraType == KEESE_AURA_FIRE) || (this->auraType == KEESE_AURA_ICE)) {
            if ((limbIndex == 15) || (limbIndex == 21)) {
                if (limbIndex == 15) {
                    effPos.x = (Math_SinS(9100 * this->timer) * this->timer) + this->actor.world.pos.x;
                    effPos.z = (Math_CosS(9100 * this->timer) * this->timer) + this->actor.world.pos.z;
                } else {
                    effPos.x = this->actor.world.pos.x - (Math_SinS(9100 * this->timer) * this->timer);
                    effPos.z = this->actor.world.pos.z - (Math_CosS(9100 * this->timer) * this->timer);
                }

                effPos.y = this->actor.world.pos.y + ((15 - this->timer) * 1.5f);
                effScaleStep = -5;
                effLife = 10;

                if (this->auraType == KEESE_AURA_FIRE) {
                    effPrimColor = &fireAuraPrimColor;
                    effEnvColor = &fireAuraEnvColor;
                } else {
                    effPrimColor = &iceAuraPrimColor;
                    effEnvColor = &iceAuraEnvColor;
                }

                func_8002843C(play, &effPos, &effVelocity, &effAccel, effPrimColor, effEnvColor, 250, effScaleStep, effLife);
            }
        }
    }
    if ((limbIndex == 15) || (limbIndex == 21) || (limbIndex == 10)) {
        if (limbIndex == 15) {
            limbDest = &this->bodyPartsPos[0];
        } else if (limbIndex == 21) {
            limbDest = &this->bodyPartsPos[1];
        } else {
            limbDest = &this->bodyPartsPos[2];
        }

        Matrix_MultVec3f(&limbSrc, limbDest);
        limbDest->y -= 5.0f;
    }
}

void TransformKeese_Draw(Actor* thisx, PlayState* play) {
    TransformKeese* this = (TransformKeese*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    if (this->onFire) {
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);
    } else {
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    }

    POLY_OPA_DISP = SkelAnime_Draw(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   TransformKeese_OverrideLimbDraw, TransformKeese_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}