#include "z_transform_octorok.h"
#include "assets/objects/object_okuta/object_okuta.h"

#define FLAGS ACTOR_FLAG_4

void TransformOctorok_Init(Actor* thisx, PlayState* play);
void TransformOctorok_Destroy(Actor* thisx, PlayState* play);
void TransformOctorok_Update(Actor* thisx, PlayState* play2);
void TransformOctorok_Draw(Actor* thisx, PlayState* play);

void TransformOctorok_Action_Float(TransformOctorok* this, PlayState* play);
void TransformOctorok_Action_Jump(TransformOctorok* this, PlayState* play);
void TransformOctorok_Action_Dive(TransformOctorok* this, PlayState* play);
void TransformOctorok_Action_Shoot(TransformOctorok* this, PlayState* play);
void TransformOctorok_Action_WaitForJumpRelease(TransformOctorok* this, PlayState* play);
void TransformOctorok_Action_JumpOutOfWater(TransformOctorok* this, PlayState* play);
void TransformOctorok_Action_GetHit(TransformOctorok* this, PlayState* play);

ActorInit Transform_Octorok_InitVars = {
    /**/ ACTOR_TRANSFORM_OCTOROK,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_OKUTA,
    /**/ sizeof(TransformOctorok),
    /**/ TransformOctorok_Init,
    /**/ TransformOctorok_Destroy,
    /**/ TransformOctorok_Update,
    /**/ TransformOctorok_Draw,
};

static ColliderCylinderInit sOctorockColliderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 40, -30, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 15, 60, 100 };

void TransformOctorok_SpawnBubbles(TransformOctorok* this, PlayState* play) {
    s32 i;

    for (i = 0; i < 10; i++) {
        EffectSsBubble_Spawn(play, &this->actor.world.pos, -10.0f, 10.0f, 30.0f, 0.25f);
    }
}

void TransformOctorok_SpawnDust(Vec3f* pos, Vec3f* velocity, s16 scaleStep, PlayState* play) {
    static Vec3f accel = { 0.0f, 0.0f, 0.0f };
    static Color_RGBA8 primColor = { 255, 255, 255, 255 };
    static Color_RGBA8 envColor = { 150, 150, 150, 255 };

    func_8002829C(play, pos, velocity, &accel, &primColor, &envColor, 0x190, scaleStep);
}

void TransformOctorok_SpawnSplash(TransformOctorok* this, PlayState* play) {
    EffectSsGSplash_Spawn(play, &this->actor.world.pos, NULL, NULL, 0, 1300);
}

void TransformOctorok_SpawnRipple(TransformOctorok* this, PlayState* play) {
    Vec3f pos;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y + this->actor.yDistToWater;
    pos.z = this->actor.world.pos.z;
    if ((play->gameplayFrames % 7) == 0) {
        EffectSsGRipple_Spawn(play, &pos, 250, 650, 0);
    }
}

void TransformOctorok_SetupAction(TransformOctorok* this, PlayState* play, TransformOctorokActionFunc actionFunc) {
    this->actionFunc = actionFunc;

    if (actionFunc == TransformOctorok_Action_Float) {
        osSyncPrintf("okuta: float\n");
        Animation_PlayLoop(&this->skelAnime, &gOctorokFloatAnim);
        Interface_SetDoAction(play, DO_ACTION_DIVE);
        Interface_LoadActionLabelB(play, DO_ACTION_ATTACK);
    }
    else if (actionFunc == TransformOctorok_Action_Shoot) {
        osSyncPrintf("okuta: shoot\n");
        this->actor.speed = 0.0f;
        Animation_PlayOnceSetSpeed(&this->skelAnime, &gOctorokShootAnim, 1.5f);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (actionFunc == TransformOctorok_Action_Jump) {
        osSyncPrintf("okuta: jump\n");
        Animation_PlayOnce(&this->skelAnime, &gOctorokShootAnim);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_ATTACK);
    }
    else if (actionFunc == TransformOctorok_Action_Dive) {
        osSyncPrintf("okuta: dive\n");
        this->actor.speed = 0.0f;
        this->actor.velocity.y = -2.0f;
        this->framesAPressed = 0;
        Animation_PlayOnce(&this->skelAnime, &gOctorokHideAnim);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (actionFunc == TransformOctorok_Action_WaitForJumpRelease) {
        osSyncPrintf("okuta: wait for jump release\n");
        this->actor.speed = 0.0f;
        this->actor.velocity.y = 0.0f;
        Interface_SetDoAction(play, DO_ACTION_ATTACK);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (actionFunc == TransformOctorok_Action_JumpOutOfWater) {
        osSyncPrintf("okuta: jump out of water\n");
        this->actor.speed = 0.0f;
        this->actor.velocity.y = CLAMP(this->framesAPressed * 1.5f, 5.0f, 24.0f);
        Animation_PlayOnceSetSpeed(&this->skelAnime, &gOctorokFloatAnim, 2.0f);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
    else if (actionFunc == TransformOctorok_Action_GetHit) {
        osSyncPrintf("okuta: get hit\n");
        Animation_MorphToPlayOnce(&this->skelAnime, &gOctorokHitAnim, -5.0f);
        Interface_SetDoAction(play, DO_ACTION_NONE);
        Interface_LoadActionLabelB(play, DO_ACTION_NONE);
    }
}

void TransformOctorok_Init(Actor* thisx, PlayState* play) {
    TransformOctorok* this = (TransformOctorok*)thisx;

    SkelAnime_Init(play, &this->skelAnime, &gOctorokSkel, &gOctorokFloatAnim, this->jointTable, this->morphTable, 38);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sOctorockColliderInit);
    CollisionCheck_SetInfo(&thisx->colChkInfo, NULL, &sColChkInfoInit);

    this->actor.speedCap = 18.0f;
    this->headScale.x = this->headScale.y = this->headScale.z = 1.0f;
    this->actor.speed = GET_PLAYER(play)->actor.speed;

    TransformOctorok_SetupAction(this, play, TransformOctorok_Action_Float);
}

void TransformOctorok_Destroy(Actor* thisx, PlayState* play) {
    TransformOctorok* this = (TransformOctorok*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void TransformOctorok_Update(Actor* thisx, PlayState* play) {
    TransformOctorok* this = (TransformOctorok*)thisx;
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

        if (gSaveContext.save.info.playerData.health == 0) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_DEAD1);
            Enemy_StartFinishingBlow(play, &this->actor);
            Actor_Kill(&this->actor);
        }

        TransformOctorok_SetupAction(this, play, TransformOctorok_Action_GetHit);
    }

    this->collider.dim.height =
        (((sOctorockColliderInit.dim.height * this->headScale.y) - this->collider.dim.yShift) *
            this->actor.scale.y * 100.0f);

    Actor_HandleZTarget(&this->actor, play);
    Actor_MoveXZGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 15.0f, 30.0f,
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 | UPDBGCHECKINFO_FLAG_4);

    Actor_SetFocus(&this->actor, 15.0f);

    this->actionFunc(this, play);

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);

    if (gSaveContext.save.info.playerData.health > 0 && (this->actor.colorFilterTimer == 0)) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }

    if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && !(this->actor.bgCheckFlags & BGCHECKFLAG_WATER) && this->actor.yDistToWater < -5.0f) {
        Enemy_StartFinishingBlow(play, &this->actor);
        Actor_Kill(&this->actor);
    }
}

void TransformOctorok_ComputeFloatingVelocity(TransformOctorok* this, PlayState* play) {
    if (this->actor.yDistToWater <= 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    else {
        this->actor.velocity.y = 3.0f;
    }
    this->actor.gravity = 0.0f;
}

void TransformOctorok_SpawnProjectile(TransformOctorok* this, PlayState* play) {
    Vec3f pos;
    Vec3f velocity;
    Actor* spawnedActor;
    f32 sinY = Math_SinS(this->actor.shape.rot.y);
    f32 cosY = Math_CosS(this->actor.shape.rot.y);

    pos.x = this->actor.world.pos.x + (25.0f * sinY);
    pos.y = this->actor.world.pos.y - 6.0f;
    pos.z = this->actor.world.pos.z + (25.0f * cosY);
    if ((spawnedActor = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, pos.x, pos.y, pos.z, this->actor.shape.rot.x,
                    this->actor.shape.rot.y, this->actor.shape.rot.z, 0)) != NULL) {
        pos.x = this->actor.world.pos.x + (40.0f * sinY);
        pos.z = this->actor.world.pos.z + (40.0f * cosY);
        pos.y = this->actor.world.pos.y;
        velocity.x = 1.5f * sinY;
        velocity.y = 0.0f;
        velocity.z = 1.5f * cosY;
        TransformOctorok_SpawnDust(&pos, &velocity, 20, play);
        spawnedActor->speed = CLAMP(3.0f * this->framesBPressed, 10.0f, 40.0f);
    }
    Actor_PlaySfx(&this->actor, NA_SE_EN_NUTS_THROW);
    this->framesBPressed = 0;
}

void TransformOctorok_CheckShoot(TransformOctorok* this, PlayState* play) {
    if (CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_B)) {
        this->framesBPressed++;
    }
    else if (this->framesBPressed != 0) {
        TransformOctorok_SetupAction(this, play, TransformOctorok_Action_Shoot);
    }
}

void TransformOctorok_CheckDive(TransformOctorok* this, PlayState* play) {
    if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_A)) {
        TransformOctorok_SetupAction(this, play, TransformOctorok_Action_Dive);
    }
}

void TransformOctorok_Action_Jump(TransformOctorok* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 0, play);

    Math_StepToF(&this->actor.speed, speedTarget / 2.0f, 0.7f);
    if (speedTarget != 0.0f) {
        this->actor.world.rot.y = this->actor.shape.rot.y = yawTarget;
    }
    else {
        Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, 1200);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    if (this->actor.bgCheckFlags & BGCHECKFLAG_WATER) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_LAND);
        TransformOctorok_SpawnSplash(this, play);
        TransformOctorok_SetupAction(this, play, TransformOctorok_Action_Float);
    }

    this->skelAnime.curFrame = 11.0f;

    SkelAnime_Update(&this->skelAnime);

    this->actor.gravity = -1.0f;

    TransformOctorok_CheckShoot(this, play);
}

void TransformOctorok_Action_Dive(TransformOctorok* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_BUBLE);
        TransformOctorok_SpawnBubbles(this, play);
        TransformOctorok_SetupAction(this, play, TransformOctorok_Action_WaitForJumpRelease);
    } else if (this->skelAnime.curFrame >= 4.0f) {
        Actor_SetScale(&this->actor, (6.0f - this->skelAnime.curFrame) * 0.5f * 0.01f);
    }
    if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_SINK);
    }
    if (Animation_OnFrame(&this->skelAnime, 4.0f)) {
        TransformOctorok_SpawnSplash(this, play);
    }
    if (CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_A)) {
        this->framesAPressed++;
    }
}

void TransformOctorok_Action_WaitForJumpRelease(TransformOctorok* this, PlayState* play) {
    if (!CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_A)) {
        TransformOctorok_SetupAction(this, play, TransformOctorok_Action_JumpOutOfWater);
    }
    else {
        this->framesAPressed++;
    }
}

void TransformOctorok_Action_JumpOutOfWater(TransformOctorok* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime) || (!(this->actor.bgCheckFlags & BGCHECKFLAG_WATER) && (this->actor.yDistToWater < -5.0f))) {
        TransformOctorok_SpawnSplash(this, play);
        Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_JUMP);
        TransformOctorok_SetupAction(this, play, TransformOctorok_Action_Jump);
        Actor_SetScale(&this->actor, 0.01f);
    }
    else {
        if (this->actor.scale.x < 0.01f) {
            Actor_SetScale(&this->actor, this->skelAnime.curFrame * 0.2 * 0.01f);
        }
        else {
            Actor_SetScale(&this->actor, 0.01f);
        }
    }
}

void TransformOctorok_Action_Shoot(TransformOctorok* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->actor.bgCheckFlags & BGCHECKFLAG_WATER) {
            TransformOctorok_SetupAction(this, play, TransformOctorok_Action_Float);
        } else {
            TransformOctorok_SetupAction(this, play, TransformOctorok_Action_Jump);
        }
    } else {
        if (Animation_OnFrame(&this->skelAnime, 6.0f)) {
            TransformOctorok_SpawnProjectile(this, play);
        }
    }
}

void TransformOctorok_Action_Float(TransformOctorok* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 0, play);

    Math_StepToF(&this->actor.speed, speedTarget * 1.4f, 0.9f);
    if (speedTarget != 0.0f) {
        this->actor.world.rot.y = this->actor.shape.rot.y = yawTarget;
    }
    else {
        Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, 1200);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    TransformOctorok_CheckShoot(this, play);
    TransformOctorok_CheckDive(this, play);
    TransformOctorok_ComputeFloatingVelocity(this, play);

    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_WATER) && (this->actor.yDistToWater < -5.0f)) {
        TransformOctorok_SetupAction(this, play, TransformOctorok_Action_Jump);
    }

    TransformOctorok_SpawnRipple(this, play);

    SkelAnime_Update(&this->skelAnime);

    if (Animation_OnFrame(&this->skelAnime, 0.5f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_OCTAROCK_FLOAT);
    }
}

void TransformOctorok_Action_GetHit(TransformOctorok* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        TransformOctorok_SetupAction(this, play, TransformOctorok_Action_Float);
    }
}

s32 TransformOctorok_GetSnoutScale(TransformOctorok* this, f32 curFrame, Vec3f* scale) {
    if (this->actionFunc == TransformOctorok_Action_Float) {
        scale->x = scale->z = 1.0f;
        scale->y = (sinf((M_PI / 16) * curFrame) * 0.4f) + 1.0f;
    } else if (this->actionFunc == TransformOctorok_Action_Shoot) {
        if (curFrame < 5.0f) {
            scale->x = 1.0f;
            scale->y = scale->z = (curFrame * 0.25f) + 1.0f;
        } else if (curFrame < 7.0f) {
            scale->x = (curFrame - 4.0f) * 0.5f + 1.0f;
            scale->y = scale->z = 2.0f - (curFrame - 4.0f) * 0.5f;
        } else {
            scale->x = 2.0f - ((curFrame - 6.0f) * 0.0769f);
            scale->y = scale->z = 1.0f;
        }
    } else {
        return false;
    }

    return true;
}

s32 TransformOctorok_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx) {
    TransformOctorok* this = (TransformOctorok*)thisx;
    f32 curFrame = this->skelAnime.curFrame;
    Vec3f scale;
    s32 doScale = false;

    if (limbIndex == 5) {
        if ((this->headScale.x != 1.0f) || (this->headScale.y != 1.0f) || (this->headScale.z != 1.0f)) {
            scale = this->headScale;
            doScale = true;
        }
    } else if (limbIndex == 8) {
        scale = this->headScale;
        doScale = TransformOctorok_GetSnoutScale(this, curFrame, &scale);
    }
    if (doScale) {
        Matrix_Scale(scale.x, scale.y, scale.z, MTXMODE_APPLY);
    }
    return false;
}

void TransformOctorok_DrawDebugInfo(PlayState* play, TransformOctorok* this) {
    Gfx* gfx;
    Gfx* polyOpa;
    GfxPrint printer;
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    OPEN_DISPS(gfxCtx, __FILE__, __LINE__);

    polyOpa = POLY_OPA_DISP;
    gfx = Graph_GfxPlusOne(polyOpa);
    gSPDisplayList(OVERLAY_DISP++, gfx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);

    GfxPrint_SetColor(&printer, 250, 250, 50, 255);
    GfxPrint_SetPos(&printer, 4, 14);
    GfxPrint_Printf(&printer, "speed: %f", this->actor.speed);

    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    Graph_BranchDlist(polyOpa, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx, __FILE__, __LINE__);
}

Gfx* TransformOctorok_SetPrimEnvColors(GraphicsContext* gfxCtx, u8 primR, u8 primG, u8 primB, u8 envR, u8 envG, u8 envB) {
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
static Color_RGB8 sTunicColors[3] = {
    { 30, 105, 27 }, // PLAYER_TUNIC_KOKIRI
    { 100, 20, 0 },  // PLAYER_TUNIC_GORON
    { 0, 60, 100 },  // PLAYER_TUNIC_ZORA
};

void TransformOctorok_Draw(Actor* thisx, PlayState* play) {
    TransformOctorok* this = (TransformOctorok*)thisx;
    u8 tunic = TUNIC_EQUIP_TO_PLAYER(CUR_EQUIP_VALUE(EQUIP_TYPE_TUNIC));

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
    
    TransformOctorok_DrawDebugInfo(play, this);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, TransformOctorok_SetPrimEnvColors(play->state.gfxCtx, sTunicColors[tunic].r, sTunicColors[tunic].g, sTunicColors[tunic].b, sTunicColors[tunic].r/4, sTunicColors[tunic].g/4, sTunicColors[tunic].b/4));

    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, TransformOctorok_OverrideLimbDraw, NULL, this);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}
