/*
 * File: z_transform_ik.c
 * Overlay: Transform_Ik
 * Description: Iron Knuckle Transformation
 */

#include "z_transform_ik.h"

#include "assets/objects/object_ik/object_ik.h"

#define FLAGS ACTOR_FLAG_4

#define THIS ((TransformIk*)thisx)

#define RUNNING_SPEED 3.5f

void TransformIk_Init(Actor* thisx, PlayState* play);
void TransformIk_Destroy(Actor* thisx, PlayState* play);
void TransformIk_Update(Actor* thisx, PlayState* play);
void TransformIk_Draw(Actor* thisx, PlayState* play);

void TransformIk_Action_Cutscene(TransformIk* this, PlayState* play);
void TransformIk_Action_Idle(TransformIk* this, PlayState* play);
void TransformIk_Action_Walk(TransformIk* this, PlayState* play);
void TransformIk_Action_Run(TransformIk* this, PlayState* play);
void TransformIk_Action_SwingAxe(TransformIk* this, PlayState* play);
void TransformIk_Action_ReturnToIdleAfterAnimFinished(TransformIk* this, PlayState* play);
void TransformIk_Action_Block(TransformIk* this, PlayState* play);
void TransformIk_Action_GetHit(TransformIk* this, PlayState* play);
void TransformIk_Action_VerticalAttack(TransformIk* this, PlayState* play);
void TransformIk_Action_PullOutAxe(TransformIk* this, PlayState* play);
void TransformIk_Action_Fall(TransformIk* this, PlayState* play);

const ActorProfile Transform_Ik_Profile = {
    ACTOR_TRANSFORM_IK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_IK,
    sizeof(TransformIk),
    (ActorFunc)TransformIk_Init,
    (ActorFunc)TransformIk_Destroy,
    (ActorFunc)TransformIk_Update,
    (ActorFunc)TransformIk_Draw,
};

static ColliderCylinderInit sBodyCollider = {
    {
        COLTYPE_NONE,
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
    { 25, 80, 0, { 0, 0, 0 } },
};

static ColliderTrisElementInit sTrisElementsInit[2] = {
    {
        {
            ELEMTYPE_UNK2,
            { 0x00000000, 0x00, 0x00 },
            { 0xFFC3FFFF, 0x00, 0x00 },
            ATELEM_NONE,
            ACELEM_ON,
            OCELEM_NONE,
        },
        { { { -10.0f, 14.0f, 2.0f }, { -10.0f, -6.0f, 2.0f }, { 9.0f, 14.0f, 2.0f } } },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0x00000000, 0x00, 0x00 },
            { 0xFFC3FFFF, 0x00, 0x00 },
            ATELEM_NONE,
            ACELEM_ON,
            OCELEM_NONE,
        },
        { { { -10.0f, -6.0f, 2.0f }, { 9.0f, -6.0f, 2.0f }, { 9.0f, 14.0f, 2.0f } } },
    },
};

static ColliderTrisInit sShieldTrisCollider = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_ENEMY,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_TRIS,
    },
    2,
    sTrisElementsInit,
};

static ColliderQuadInit sAxeCollider = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0xFFCFFFFF, 0x0F, 0x40 },
        { 0x00000000, 0x00, 0x00 },
        ATELEM_ON | ATELEM_SFX_NORMAL,
        ACELEM_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

void TransformIk_SetupAction(TransformIk* this, PlayState* play, TransformIkActionFunc actionFunc) {
    this->actionFunc = actionFunc;

    this->attackState = 0;
    this->shieldState = 0;
    this->playedSfx = 0;
    this->queuedAttack = 0;
    this->axeCollider.elem.atDmgInfo.dmgFlags = DMG_UNBLOCKABLE;
    this->axeCollider.elem.atDmgInfo.damage = 0x40;
    if (this->actionFunc == TransformIk_Action_Cutscene) {
        Animation_Change(&this->skelAnime, &object_ik_Anim_00DD50, 0.0f, 0.0f, Animation_GetLastFrame(&object_ik_Anim_00DD50), ANIMMODE_LOOP, 4.0f);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (this->actionFunc == TransformIk_Action_Idle) {
        Animation_Change(&this->skelAnime, &object_ik_Anim_00DD50, 0.0f, 0.0f, Animation_GetLastFrame(&object_ik_Anim_00DD50), ANIMMODE_LOOP, 4.0f);
        Interface_SetDoAction(play, DO_ACTION_ATTACK);
        Interface_LoadActionLabelB(play, DO_ACTION_ATTACK);
    }
    else if (this->actionFunc == TransformIk_Action_Walk) {
        Animation_Change(&this->skelAnime, &gIronKnuckleWalkAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gIronKnuckleWalkAnim), ANIMMODE_LOOP, -4.0f);
        Interface_SetDoAction(play, DO_ACTION_ATTACK);
        Interface_LoadActionLabelB(play, DO_ACTION_ATTACK);
    }
    else if (this->actionFunc == TransformIk_Action_Run) {
        Animation_Change(&this->skelAnime, &gIronKnuckleRunAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gIronKnuckleRunAnim), ANIMMODE_LOOP, -4.0f);
        Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_DASH);
        Interface_SetDoAction(play, DO_ACTION_ATTACK);
        Interface_LoadActionLabelB(play, DO_ACTION_ATTACK);
    }
    else if (this->actionFunc == TransformIk_Action_SwingAxe) {
        this->actor.speed = 0.0f;
        Animation_Change(&this->skelAnime, &gIronKnuckleHorizontalAttackAnim, 0.5f, 0.0f, 10.0f, ANIMMODE_ONCE_INTERP, -4.0f);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (this->actionFunc == TransformIk_Action_VerticalAttack) {
        this->actor.speed = 0.0f;
        Animation_Change(&this->skelAnime, &gIronKnuckleVerticalAttackAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gIronKnuckleVerticalAttackAnim), ANIMMODE_ONCE_INTERP, -4.0f);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (this->actionFunc == TransformIk_Action_PullOutAxe) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_PULLOUT);
        Animation_Change(&this->skelAnime, &gIronKnuckleAxeStuckAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gIronKnuckleAxeStuckAnim), ANIMMODE_LOOP, -4.0f);
        this->animationTimer = Animation_GetLastFrame(&gIronKnuckleAxeStuckAnim);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (this->actionFunc == TransformIk_Action_ReturnToIdleAfterAnimFinished) {
        Animation_Change(&this->skelAnime, this->recoverAnimation, 1.5f, 0.0f, Animation_GetLastFrame(this->recoverAnimation), ANIMMODE_ONCE_INTERP, -4.0f);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (this->actionFunc == TransformIk_Action_Block) {
        this->shieldState = 1;
        this->actor.speed = 0.0f;
        Animation_Change(&this->skelAnime, &gIronKnuckleBlockAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gIronKnuckleBlockAnim), ANIMMODE_ONCE_INTERP, -4.0f);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (this->actionFunc == TransformIk_Action_GetHit) {
        s16 yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->bodyCollider.base.ac->world.pos);
        s16 yawDiff = yaw - this->actor.shape.rot.y;

        if (ABS(yawDiff) <= 0x4000) {
            Animation_Change(&this->skelAnime, &gIronKnuckleFrontHitAnim, 1.0f, 0.0f,
                            Animation_GetLastFrame(&gIronKnuckleFrontHitAnim), ANIMMODE_ONCE, -4.0f);
            this->actor.speed = -6.0f;
        } else {
            Animation_Change(&this->skelAnime, &gIronKnuckleBackHitAnim, 1.0f, 0.0f,
                            Animation_GetLastFrame(&gIronKnuckleBackHitAnim), ANIMMODE_ONCE, -4.0f);
            this->actor.speed = 6.0f;
        }
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (this->actionFunc == TransformIk_Action_Fall) {
        this->shieldState = 1;
        Animation_Change(&this->skelAnime, &gIronKnuckleBlockAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gIronKnuckleBlockAnim), ANIMMODE_ONCE_INTERP, -4.0f);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
}

void TransformIk_SetUnderwaterProperties(TransformIk* this, PlayState* play, f32* speedTarget, f32 originalPlaySpeed) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_WATER) {
        if (speedTarget != NULL) {
            *speedTarget *= 0.75f;
        }
        this->skelAnime.playSpeed = originalPlaySpeed * 0.75f;
    }
    else {
        this->skelAnime.playSpeed = originalPlaySpeed;
    }
}

void TransformIk_CheckAxeSwing(TransformIk* this, PlayState* play) {
    if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_B)) {
        TransformIk_SetupAction(this, play, TransformIk_Action_SwingAxe);
    }
    else if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_A)) {
        TransformIk_SetupAction(this, play, TransformIk_Action_VerticalAttack);
    }
}

void TransformIk_CheckBlock(TransformIk* this, PlayState* play) {
    if (CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_R)) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Block);
    }
}

void TransformIk_Action_ReturnToIdleAfterAnimFinished(TransformIk* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
    }
}

void TransformIk_Action_VerticalAttack(TransformIk* this, PlayState* play) {
    Vec3f sparksPos;

    TransformIk_SetUnderwaterProperties(this, play, NULL, 1.0f);

    if (this->skelAnime.curFrame == 15.0f) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_SWING_AXE);
    } else if (this->skelAnime.curFrame == 21.0f) {
        sparksPos.x = this->actor.world.pos.x + Math_SinS(this->actor.shape.rot.y + 0x6A4) * 70.0f;
        sparksPos.z = this->actor.world.pos.z + Math_CosS(this->actor.shape.rot.y + 0x6A4) * 70.0f;
        sparksPos.y = this->actor.world.pos.y;

        Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_HIT_GND);
        Camera_RequestQuake(&play->mainCamera, 2, 25, 5);
        Rumble_Request(this->actor.xzDistToPlayer, 255, 20, 150);
        CollisionCheck_SpawnShieldParticles(play, &sparksPos);
    }

    if ((this->skelAnime.curFrame > 17.0f) && (this->skelAnime.curFrame < 23.0f)) {
        this->attackState = 1;
        this->axeCollider.elem.atDmgInfo.dmgFlags = DMG_UNKNOWN_2;
        this->axeCollider.elem.atDmgInfo.damage = 0x60;
    } else {
        this->attackState = 0;
        this->axeCollider.elem.atDmgInfo.dmgFlags = DMG_UNBLOCKABLE;
        this->axeCollider.elem.atDmgInfo.damage = 0x40;
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        TransformIk_SetupAction(this, play, TransformIk_Action_PullOutAxe);
    }
}

void TransformIk_Action_PullOutAxe(TransformIk* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime) || (--this->animationTimer == 0)) {
        this->recoverAnimation = &gIronKnuckleRecoverFromVerticalAttackAnim;
        TransformIk_SetupAction(this, play, TransformIk_Action_ReturnToIdleAfterAnimFinished);
    }
}

void TransformIk_Action_SwingAxe(TransformIk* this, PlayState* play) {
    if (this->skelAnime.curFrame > 7.0f && CHECK_BTN_ALL(play->state.input[0].press.button, BTN_B) && this->queuedAttack == 0) {
        this->queuedAttack = 1;
        this->skelAnime.endFrame = Animation_GetLastFrame(&gIronKnuckleHorizontalAttackAnim);
    }

    TransformIk_SetUnderwaterProperties(this, play, NULL, 0.5f);
     
    if ((this->skelAnime.curFrame > 1.0f) && (this->skelAnime.curFrame < 9.0f)) {
        if (this->playedSfx < 1) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_SWING_AXE);
            this->playedSfx = 1;
        }
        this->attackState = 1;
    }
    else if ((this->skelAnime.curFrame > 13.0f) && (this->skelAnime.curFrame < 18.0f)) {
        if (this->playedSfx < 2) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_SWING_AXE);
            this->playedSfx = 2;
        }
        this->attackState = 1;
    }
    else {
        this->attackState = 0;
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->skelAnime.curFrame > 10.0f) {
            this->recoverAnimation = &gIronKnuckleRecoverFromHorizontalAttackAnim;
            TransformIk_SetupAction(this, play, TransformIk_Action_ReturnToIdleAfterAnimFinished);
        }
        else {
            TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
        }
    }
}

void TransformIk_Action_Run(TransformIk* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 1, play);

    TransformIk_SetUnderwaterProperties(this, play, &speedTarget, 1.0f);

    this->actor.world.rot.y = this->actor.shape.rot.y = yawTarget;
    Math_StepToF(&this->actor.speed, speedTarget, 0.9f);


    if (this->actor.speed == 0.0f) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
    }
    else if (this->actor.speed < RUNNING_SPEED) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Walk);
    }

    TransformIk_CheckAxeSwing(this, play);
    TransformIk_CheckBlock(this, play);

    SkelAnime_Update(&this->skelAnime);

    if (((s16)this->skelAnime.curFrame == 2) || ((s16)this->skelAnime.curFrame == 9)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_WALK);
    }
}

void TransformIk_Action_Walk(TransformIk* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 1, play);

    TransformIk_SetUnderwaterProperties(this, play, &speedTarget, 1.0f);

    this->actor.world.rot.y = this->actor.shape.rot.y = yawTarget;
    Math_StepToF(&this->actor.speed, speedTarget, 0.9f);
 
    if (this->actor.speed == 0.0f) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
    }
    else if (this->actor.speed >= RUNNING_SPEED) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Run);
    }
    
    TransformIk_CheckAxeSwing(this, play);
    TransformIk_CheckBlock(this, play);

    SkelAnime_Update(&this->skelAnime);

    if (((s16)this->skelAnime.curFrame == 0) || ((s16)this->skelAnime.curFrame == 16)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_WALK);
    }
}

void TransformIk_Action_Cutscene(TransformIk* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    SkelAnime_Update(&this->skelAnime);

    Math_StepToF(&this->actor.speed, 0.0f, 0.9f);

    if (player->csAction == PLAYER_CSACTION_NONE) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
    }
}

void TransformIk_Action_Idle(TransformIk* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 1, play);

    if (speedTarget != 0.0f) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Walk);
    }
    else {
        Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, 1200);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
    
    TransformIk_CheckAxeSwing(this, play);
    TransformIk_CheckBlock(this, play);

    SkelAnime_Update(&this->skelAnime);
}

void TransformIk_Action_Block(TransformIk* this, PlayState* play) {
    if (!CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_R)) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
    }

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->shieldCollider.base);

    SkelAnime_Update(&this->skelAnime);
}

void TransformIk_Action_GetHit(TransformIk* this, PlayState* play) {
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 1.0f, 1.0f, 0.0f);

    if (SkelAnime_Update(&this->skelAnime)) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
    }
}

void TransformIk_Action_Fall(TransformIk* this, PlayState* play) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        if (!(this->actor.bgCheckFlags & BGCHECKFLAG_WATER)) {
            Actor_PlaySfx(&this->actor, NA_SE_EV_BLOCK_BOUND);
            Actor_RequestQuakeAndRumble(&this->actor, play, 5, 5);
        }
        TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
    }
    else if ((this->actor.bgCheckFlags & BGCHECKFLAG_WATER) && !this->previousFrameInWater) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_JUMP);
        EffectSsGSplash_Spawn(play, &this->actor.world.pos, NULL, NULL, 0, 1500);
    }
    
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 1.0f, 1.0f, 0.0f);

    CollisionCheck_SetAC(play, &play->colChkCtx, &this->shieldCollider.base);

    SkelAnime_Update(&this->skelAnime);
}


void TransformIk_Init(Actor* thisx, PlayState* play) {
    TransformIk* this = THIS;
    EffectBlureInit1 blureInit;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gIronKnuckleSkel, &gIronKnuckleNabooruSummonAxeAnim,
                        this->jointTable, this->morphTable, IRON_KNUCKLE_LIMB_MAX);

    Collider_InitCylinder(play, &this->bodyCollider);
    Collider_SetCylinder(play, &this->bodyCollider, thisx, &sBodyCollider);
    Collider_InitTris(play, &this->shieldCollider);
    Collider_SetTris(play, &this->shieldCollider, thisx, &sShieldTrisCollider, this->shieldColliderItems);
    Collider_InitQuad(play, &this->axeCollider);
    Collider_SetQuad(play, &this->axeCollider, thisx, &sAxeCollider);

    thisx->colChkInfo.mass = MASS_HEAVY;
    thisx->colChkInfo.health = 30;
    thisx->gravity = -1.0f;
    thisx->speedCap = 10.0f;
    Actor_SetScale(thisx, 0.011f);

    blureInit.p1StartColor[0] = blureInit.p1StartColor[1] = blureInit.p2StartColor[0] = blureInit.p2StartColor[1] =
        blureInit.p2StartColor[2] = blureInit.p1EndColor[0] = blureInit.p1EndColor[1] = blureInit.p2EndColor[0] =
            blureInit.p2EndColor[1] = blureInit.p2EndColor[2] = 255;

    blureInit.p2StartColor[3] = 64;
    blureInit.p1StartColor[3] = 200;
    blureInit.p1StartColor[2] = blureInit.p1EndColor[2] = 150;
    blureInit.p1EndColor[3] = blureInit.p2EndColor[3] = 0;

    blureInit.elemDuration = 8;
    blureInit.unkFlag = 0;
    blureInit.calcMode = 2;

    Effect_Add(play, &this->blureIdx, EFFECT_BLURE1, 0, 0, &blureInit);

    TransformIk_SetupAction(this, play, TransformIk_Action_Idle);

    this->actor.speed = GET_PLAYER(play)->actor.speed;
    this->actor.room = -1;
    this->invincibilityTimer = 0;
}

void TransformIk_Destroy(Actor* thisx, PlayState* play) {
    TransformIk* this = THIS;

    Collider_DestroyTris(play, &this->shieldCollider);
    Collider_DestroyCylinder(play, &this->bodyCollider);
    Collider_DestroyQuad(play, &this->axeCollider);
}

void TransformIk_Update(Actor* thisx, PlayState* play) {
    TransformIk* this = THIS;
    Player* player = GET_PLAYER(play);

    Actor_SetPlayerLocation(&this->actor, play, 45.0f);

    if (this->shieldCollider.base.acFlags & AC_BOUNCED) {
        s16 frames = Animation_GetLastFrame(&gIronKnuckleBlockAnim) - 2.0f;

        if (this->skelAnime.curFrame < frames) {
            this->skelAnime.curFrame = frames;
        }

        this->shieldCollider.base.acFlags &= ~AC_BOUNCED;
        this->bodyCollider.base.acFlags &= ~AC_HIT;
    } else if (this->axeCollider.base.atFlags & AT_HIT) {
        this->axeCollider.base.atFlags &= ~AT_HIT;
    } else if (this->bodyCollider.base.acFlags & AC_HIT &&
        !(this->bodyCollider.base.ac != NULL && this->bodyCollider.base.ac->id == ACTOR_BG_JYA_HAHENIRON)) {
        this->bodyCollider.base.acFlags &= ~AC_HIT;

        Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 12);

        play->damagePlayer(play, -this->actor.colChkInfo.damage);
        this->invincibilityTimer = 30;

        if (gSaveContext.save.info.playerData.health == 0) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_DEAD);
            Actor_PlaySfx(&this->actor, NA_SE_EN_NUTS_CUTBODY);
            Enemy_StartFinishingBlow(play, &this->actor);
            Actor_Kill(&this->actor);
        }

        Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_DAMAGE);
        Actor_PlaySfx(&this->actor, NA_SE_EN_NUTS_CUTBODY);

        TransformIk_SetupAction(this, play, TransformIk_Action_GetHit);
    }

    Actor_HandleZTarget(&this->actor, play);
    Actor_MoveXZGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 75.0f, 30.0f, 30.0f,
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 |
                                UPDBGCHECKINFO_FLAG_4);

    Actor_TriggerDynapolyIfPossible(&this->actor, play);
    Actor_CheckVoidOut(&this->actor, play);
    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (this->actionFunc != TransformIk_Action_Fall)) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Fall);
    }

    if (this->actor.bgCheckFlags & BGCHECKFLAG_WATER) {
        thisx->gravity = -0.4f;
    }
    else {
        thisx->gravity = -1.0f;
    }

    if (player->csAction != PLAYER_CSACTION_NONE && this->actionFunc != TransformIk_Action_Cutscene) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Cutscene);
    }

    this->actionFunc(this, play);

    Collider_UpdateCylinder(&this->actor, &this->bodyCollider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->bodyCollider.base);

    if (this->invincibilityTimer != 0) {
        this->invincibilityTimer--;
    }

    if ((gSaveContext.save.info.playerData.health > 0) && (this->actor.colorFilterTimer == 0) && (this->invincibilityTimer == 0)) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->bodyCollider.base);
    }

    if (this->attackState > 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->axeCollider.base);
    }

    if (this->shieldState > 0) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->shieldCollider.base);
    }

    this->previousFrameInWater = !!(this->actor.bgCheckFlags & BGCHECKFLAG_WATER);
}

Gfx* TransformIk_SetPrimEnvColors(GraphicsContext* gfxCtx, u8 primR, u8 primG, u8 primB, u8 envR, u8 envG, u8 envB) {
    Gfx* displayList;
    Gfx* displayListHead;

    displayList = Graph_Alloc(gfxCtx, 4 * sizeof(Gfx));
    displayListHead = displayList;

    gDPPipeSync(displayListHead++);
    gDPSetPrimColor(displayListHead++, 0, 0, primR, primG, primB, 255);
    gDPSetEnvColor(displayListHead++, envR, envG, envB, 255);
    gSPEndDisplayList(displayListHead++);

    return displayList;
}

s32 TransformIk_OverrideLimbDrawEnemy(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    TransformIk* this = (TransformIk*)thisx;

    if (limbIndex == IRON_KNUCKLE_LIMB_HELMET_ARMOR) {
        *dList = gIronKnuckleHelmetDL;
    } else if (limbIndex == IRON_KNUCKLE_LIMB_HEAD) {
        *dList = gIronKnuckleGerudoHeadDL;
    } else if ((limbIndex == IRON_KNUCKLE_LIMB_CHEST_ARMOR_FRONT) ||
               (limbIndex == IRON_KNUCKLE_LIMB_CHEST_ARMOR_BACK)) {
    } else if ((limbIndex == IRON_KNUCKLE_LIMB_TORSO) || (limbIndex == IRON_KNUCKLE_LIMB_WAIST)) {
        *dList = NULL;
    }

    return false;
}

static Vec3f D_80A7847C[] = {
    { 800.0f, -200.0f, -5200.0f },
    { 0.0f, 0.0f, 0.0f },
    { -200.0f, -2200.0f, -200.0f },
    { -6000.0f, 2000.0f, -3000.0f },
};

static Vec3f D_80A784AC[] = {
    { -3000.0, -700.0, -5000.0 },
    { -3000.0, -700.0, 2000.0 },
    { 4000.0, -700.0, 2000.0 },
};

static Vec3f D_80A784D0[] = {
    { 4000.0, -700.0, 2000.0 },
    { 4000.0, -700.0, -5000.0 },
    { -3000.0, -700.0, -5000.0 },
};

void TransformIk_PostLimbDrawEnemy(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
    Vec3f spF4;
    Vec3f spE8;
    TransformIk* this = (TransformIk*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    if (limbIndex == IRON_KNUCKLE_LIMB_HELMET_ARMOR) {
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gIronKnuckleHelmetMarkingDL);
    } else if (limbIndex == IRON_KNUCKLE_LIMB_AXE) {
        s32 i;
        Vec3f vertices_0[3];
        Vec3f vertices_1[3];

        Matrix_MultVec3f(&D_80A7847C[0], &this->axeCollider.dim.quad[1]);
        Matrix_MultVec3f(&D_80A7847C[1], &this->axeCollider.dim.quad[0]);
        Matrix_MultVec3f(&D_80A7847C[2], &this->axeCollider.dim.quad[3]);
        Matrix_MultVec3f(&D_80A7847C[3], &this->axeCollider.dim.quad[2]);
        Collider_SetQuadVertices(&this->axeCollider, &this->axeCollider.dim.quad[0], &this->axeCollider.dim.quad[1],
                                 &this->axeCollider.dim.quad[2], &this->axeCollider.dim.quad[3]);
        Matrix_MultVec3f(&D_80A7847C[0], &spF4);
        Matrix_MultVec3f(&D_80A7847C[1], &spE8);
        if (this->attackState > 0) {
            EffectBlure_AddVertex(Effect_GetByIndex(this->blureIdx), &spF4, &spE8);
        } else if (this->attackState == 0) {
            EffectBlure_AddSpace(Effect_GetByIndex(this->blureIdx));
        }
        if (this->shieldState > 0) {
            for (i = 0; i < ARRAY_COUNT(vertices_1); i++) {
                Matrix_MultVec3f(&D_80A784AC[i], &vertices_0[i]);
                Matrix_MultVec3f(&D_80A784D0[i], &vertices_1[i]);
            }

            Collider_SetTrisVertices(&this->shieldCollider, 0, &vertices_0[0], &vertices_0[1], &vertices_0[2]);
            Collider_SetTrisVertices(&this->shieldCollider, 1, &vertices_1[0], &vertices_1[1], &vertices_1[2]);
        }
    }

    switch (limbIndex) {
        case IRON_KNUCKLE_LIMB_UPPER_LEFT_PAULDRON:
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_ik_DL_016F88);
            break;

        case IRON_KNUCKLE_LIMB_UPPER_RIGHT_PAULDRON:
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_ik_DL_016EE8);
            break;

        case IRON_KNUCKLE_LIMB_CHEST_ARMOR_FRONT:
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                        G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gIronKnuckleArmorRivetAndSymbolDL);
            break;

        case IRON_KNUCKLE_LIMB_CHEST_ARMOR_BACK:
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                        G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_ik_DL_016CD8);
            break;
    }

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

static Color_RGB8 sTunicColors[3] = {
    { 30, 105, 27 }, // PLAYER_TUNIC_KOKIRI
    { 100, 20, 0 },  // PLAYER_TUNIC_GORON
    { 0, 60, 100 },  // PLAYER_TUNIC_ZORA
};

void TransformIk_Draw(Actor* thisx, PlayState* play) {
    TransformIk* this = (TransformIk*)thisx;
    u8 tunic = TUNIC_EQUIP_TO_PLAYER(CUR_EQUIP_VALUE(EQUIP_TYPE_TUNIC));

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    Gfx_SetupDL_25Xlu(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, TransformIk_SetPrimEnvColors(play->state.gfxCtx, 245, 225, 155, 30, 30, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, TransformIk_SetPrimEnvColors(play->state.gfxCtx, sTunicColors[tunic].r, sTunicColors[tunic].g, sTunicColors[tunic].b, sTunicColors[tunic].r/4, sTunicColors[tunic].g/4, sTunicColors[tunic].b/4));
    gSPSegment(POLY_OPA_DISP++, 0x0A, TransformIk_SetPrimEnvColors(play->state.gfxCtx, 255, 255, 255, 20, 40, 30));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          TransformIk_OverrideLimbDrawEnemy, TransformIk_PostLimbDrawEnemy, this);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}