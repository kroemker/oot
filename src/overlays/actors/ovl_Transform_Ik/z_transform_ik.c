/*
 * File: z_transform_ik.c
 * Overlay: Transform_Ik
 * Description: Iron Knuckle Transformation
 */

#include "z_transform_ik.h"

#include "assets/objects/object_ik/object_ik.h"

#define FLAGS 0x00000010

#define THIS ((TransformIk*)thisx)

#define ARMOR_BROKEN (1 << 0)
#define RUNNING_SPEED 3.5f

void TransformIk_Init(Actor* thisx, PlayState* play);
void TransformIk_Destroy(Actor* thisx, PlayState* play);
void TransformIk_Update(Actor* thisx, PlayState* play);
void TransformIk_Draw(Actor* thisx, PlayState* play);

void TransformIk_Action_Idle(TransformIk* this, PlayState* play);
void TransformIk_Action_Walk(TransformIk* this, PlayState* play);
void TransformIk_Action_Run(TransformIk* this, PlayState* play);
void TransformIk_Action_SwingAxe(TransformIk* this, PlayState* play);
void TransformIk_Action_ReturnToIdleAfterAnimFinished(EnIk* this, PlayState* play);

const ActorInit Transform_Ik_InitVars = {
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

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON | BUMP_HOOKABLE,
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
            TOUCH_NONE,
            BUMP_ON | BUMP_NO_AT_INFO,
            OCELEM_NONE,
        },
        { { { -10.0f, 14.0f, 2.0f }, { -10.0f, -6.0f, 2.0f }, { 9.0f, 14.0f, 2.0f } } },
    },
    {
        {
            ELEMTYPE_UNK2,
            { 0x00000000, 0x00, 0x00 },
            { 0xFFC3FFFF, 0x00, 0x00 },
            TOUCH_NONE,
            BUMP_ON | BUMP_NO_AT_INFO,
            OCELEM_NONE,
        },
        { { { -10.0f, -6.0f, 2.0f }, { 9.0f, -6.0f, 2.0f }, { 9.0f, 14.0f, 2.0f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_TRIS,
    },
    2,
    sTrisElementsInit,
};

static ColliderQuadInit sQuadInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK0,
        { 0x20000000, 0x00, 0x40 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

void TransformIk_CheckAxeSwing(TransformIk* this, PlayState* play) {
    if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_B)) {
        TransformIk_SetupAction(this, play, TransformIk_Action_SwingAxe);
    }
}

void TransformIk_MoveAndUpdateBgInfo(TransformIk* this, PlayState* play) {
    Actor_MoveXZGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 75.0f, 30.0f, 30.0f,
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 |
                                UPDBGCHECKINFO_FLAG_4);

    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 45.0f;

    Collider_UpdateCylinder(&this->actor, &this->bodyCollider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->bodyCollider.base);
}

void TransformIk_SetupAction(TransformIk* this, PlayState* play, TransformIkActionFunc actionFunc) {
    this->actionFunc = actionFunc;

    if (this->actionFunc == TransformIk_Action_Idle) {
        this->actor.speed = GET_PLAYER(play)->actor.speed;
        f32 endFrame = Animation_GetLastFrame(&object_ik_Anim_00DD50);
        Animation_Change(&this->skelAnime, &object_ik_Anim_00DD50, 0.0f, 0.0f, endFrame, ANIMMODE_LOOP, 4.0f);
    }
    else if (this->actionFunc == TransformIk_Action_Walk) {
        Animation_Change(&this->skelAnime, &gIronKnuckleWalkAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gIronKnuckleWalkAnim), ANIMMODE_LOOP, -4.0f);
    }
    else if (this->actionFunc == TransformIk_Action_Run) {
        Animation_Change(&this->skelAnime, &gIronKnuckleRunAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gIronKnuckleRunAnim), ANIMMODE_LOOP, -4.0f);
        Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_DASH);
    }
    else if (this->actionFunc == TransformIk_Action_SwingAxe) {
        Animation_Change(&this->skelAnime, &gIronKnuckleHorizontalAttackAnim, 0.5f, 0.0f, 10.0f, ANIMMODE_ONCE_INTERP, -4.0f);
        this->playedSfx = 0;
        this->queuedAttack = 0;
    }
    else if (this->actionFunc == TransformIk_Action_ReturnToIdleAfterAnimFinished) {
        Animation_Change(&this->skelAnime, &gIronKnuckleRecoverFromHorizontalAttackAnim, 1.5f, 0.0f, Animation_GetLastFrame(&gIronKnuckleRecoverFromHorizontalAttackAnim), ANIMMODE_ONCE_INTERP, -4.0f);
    }
}

void TransformIk_Action_ReturnToIdleAfterAnimFinished(EnIk* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
    }
}

void TransformIk_Action_SwingAxe(TransformIk* this, PlayState* play) {
    if (this->skelAnime.curFrame > 8.0f && CHECK_BTN_ALL(play->state.input[0].press.button, BTN_B) && this->queuedAttack == 0) {
        this->queuedAttack = 1;
        this->skelAnime.endFrame = Animation_GetLastFrame(&gIronKnuckleHorizontalAttackAnim);
    }
     
    if ((this->skelAnime.curFrame > 1.0f) && (this->skelAnime.curFrame < 9.0f)) {
        if (this->playedSfx < 1) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_SWING_AXE);
            this->playedSfx = 1;
        }
    }

    if ((this->skelAnime.curFrame > 13.0f) && (this->skelAnime.curFrame < 18.0f)) {
        if (this->playedSfx < 2) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_SWING_AXE);
            this->playedSfx = 2;
        }
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->skelAnime.curFrame > 10.0f) {
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

    TransformIk_MoveAndUpdateBgInfo(this, play);

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, play);

    this->actor.world.rot.y = this->actor.shape.rot.y = yawTarget;
    Math_StepToF(&this->actor.speed, speedTarget, 0.9f);

    if (this->actor.speed == 0.0f) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
    }
    else if (this->actor.speed < RUNNING_SPEED) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Walk);
    }

    TransformIk_CheckAxeSwing(this, play);

    SkelAnime_Update(&this->skelAnime);

    if (((s16)this->skelAnime.curFrame == 2) || ((s16)this->skelAnime.curFrame == 9)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_WALK);
    }
}

void TransformIk_Action_Walk(TransformIk* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    TransformIk_MoveAndUpdateBgInfo(this, play);

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, play);

    this->actor.world.rot.y = this->actor.shape.rot.y = yawTarget;
    Math_StepToF(&this->actor.speed, speedTarget, 0.9f);
 
    if (this->actor.speed == 0.0f) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Idle);
    }
    else if (this->actor.speed >= RUNNING_SPEED) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Run);
    }
    
    TransformIk_CheckAxeSwing(this, play);

    SkelAnime_Update(&this->skelAnime);

    if (((s16)this->skelAnime.curFrame == 0) || ((s16)this->skelAnime.curFrame == 16)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_IRONNACK_WALK);
    }
}

void TransformIk_Action_Idle(TransformIk* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    TransformIk_MoveAndUpdateBgInfo(this, play);

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, play);

    if (speedTarget != 0.0f) {
        TransformIk_SetupAction(this, play, TransformIk_Action_Walk);
    }
    else {
        Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, 1200);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }
    
    TransformIk_CheckAxeSwing(this, play);

    SkelAnime_Update(&this->skelAnime);
}

void TransformIk_Init(Actor* thisx, PlayState* play) {
    TransformIk* this = THIS;
    EffectBlureInit1 blureInit;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gIronKnuckleSkel, &gIronKnuckleNabooruSummonAxeAnim,
                        this->jointTable, this->morphTable, IRON_KNUCKLE_LIMB_MAX);

    Collider_InitCylinder(play, &this->bodyCollider);
    Collider_SetCylinder(play, &this->bodyCollider, thisx, &sCylinderInit);
    Collider_InitTris(play, &this->shieldCollider);
    Collider_SetTris(play, &this->shieldCollider, thisx, &sTrisInit, this->shieldColliderItems);
    Collider_InitQuad(play, &this->axeCollider);
    Collider_SetQuad(play, &this->axeCollider, thisx, &sQuadInit);

    //thisx->colChkInfo.damageTable = &sDamageTable;
    thisx->colChkInfo.mass = MASS_HEAVY;
    this->isBreakingProp = false;
    thisx->colChkInfo.health = 30;
    thisx->gravity = -1.0f;
    thisx->speedCap = 10.0f;

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
}

void TransformIk_Destroy(Actor* thisx, PlayState* play) {
    TransformIk* this = THIS;
}

void TransformIk_Update(Actor* thisx, PlayState* play) {
    TransformIk* this = THIS;
    Player* player = GET_PLAYER(play);

    player->actor.world.pos.x = this->actor.world.pos.x;
    player->actor.world.pos.y = this->actor.world.pos.y;
    player->actor.world.pos.z = this->actor.world.pos.z;
    player->actor.world.rot.x = this->actor.world.rot.x;
    player->actor.world.rot.y = this->actor.world.rot.y;
    player->actor.world.rot.z = this->actor.world.rot.z;
    player->actor.shape.rot.x = this->actor.shape.rot.x;
    player->actor.shape.rot.y = this->actor.shape.rot.y;
    player->actor.shape.rot.z = this->actor.shape.rot.z;

    if (this->actionFunc != NULL) {
        this->actionFunc(this, play);
    }
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
        if (this->drawArmorFlag & ARMOR_BROKEN) {
            *dList = NULL;
        }
    } else if ((limbIndex == IRON_KNUCKLE_LIMB_TORSO) || (limbIndex == IRON_KNUCKLE_LIMB_WAIST)) {
        if (!(this->drawArmorFlag & ARMOR_BROKEN)) {
            *dList = NULL;
        }
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

    /*if (this->armorStatusFlag & ARMOR_BROKEN) {
        BodyBreak_SetInfo(&this->bodyBreak, limbIndex, IRON_KNUCKLE_LIMB_CHEST_ARMOR_FRONT,
                          IRON_KNUCKLE_LIMB_CHEST_ARMOR_BACK, IRON_KNUCKLE_LIMB_TORSO, dList,
                          BODYBREAK_OBJECT_SLOT_DEFAULT);
    }*/
    if (limbIndex == IRON_KNUCKLE_LIMB_HELMET_ARMOR) {
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        if (this->actor.params != IK_TYPE_NABOORU) {
            gSPDisplayList(POLY_XLU_DISP++, gIronKnuckleHelmetMarkingDL);
        } else {
            gSPDisplayList(POLY_XLU_DISP++, object_ik_DL_016D88);
        }
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
        if (this->unk_2FE > 0) {
            EffectBlure_AddVertex(Effect_GetByIndex(this->blureIdx), &spF4, &spE8);
        } else if (this->unk_2FE == 0) {
            EffectBlure_AddSpace(Effect_GetByIndex(this->blureIdx));
            this->unk_2FE = -1;
        }
        if (this->unk_2F8 == 9) {
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
            if (!(this->drawArmorFlag & ARMOR_BROKEN)) {
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gIronKnuckleArmorRivetAndSymbolDL);
            }
            break;

        case IRON_KNUCKLE_LIMB_CHEST_ARMOR_BACK:
            if (!(this->drawArmorFlag & ARMOR_BROKEN)) {
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, object_ik_DL_016CD8);
            }
            break;
    }

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

void TransformIk_DrawDebugInfo(PlayState* play, TransformIk* this) {
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
    GfxPrint_SetPos(&printer, 4, 16);
    GfxPrint_Printf(&printer, "yaw: %d", this->actor.shape.rot.y);

    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    Graph_BranchDlist(polyOpa, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx, __FILE__, __LINE__);
}

void TransformIk_Draw(Actor* thisx, PlayState* play) {
    TransformIk* this = (TransformIk*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    TransformIk_DrawDebugInfo(play, this);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    Gfx_SetupDL_25Xlu(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, TransformIk_SetPrimEnvColors(play->state.gfxCtx, 245, 225, 155, 30, 30, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, TransformIk_SetPrimEnvColors(play->state.gfxCtx, 255, 40, 0, 40, 0, 0));
    gSPSegment(POLY_OPA_DISP++, 0x0A, TransformIk_SetPrimEnvColors(play->state.gfxCtx, 255, 255, 255, 20, 40, 30));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          TransformIk_OverrideLimbDrawEnemy, TransformIk_PostLimbDrawEnemy, this);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}