/*
 * File: z_spinner.c
 * Overlay: ovl_Spinner
 * Description: Spinner
 */

#include "z_spinner.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS 0x00000030

#define THIS ((Spinner*)thisx)

void Spinner_Init(Actor* thisx, GlobalContext* globalCtx);
void Spinner_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Spinner_Update(Actor* thisx, GlobalContext* globalCtx);
void Spinner_Draw(Actor* thisx, GlobalContext* globalCtx);

void Spinner_Action_FreeCruising(Spinner* this, GlobalContext* globalCtx);
void Spinner_Action_PullOut(Spinner* this, GlobalContext* globalCtx);
void Spinner_Action_Disappear(Spinner* this, GlobalContext* globalCtx);
void Spinner_Action_SpinJump(Spinner* this, GlobalContext* globalCtx);
void Spinner_Action_SpinAlongSurface(Spinner* this, GlobalContext* globalCtx);

const ActorInit Spinner_InitVars = {
    ACTOR_SPINNER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(Spinner),
    (ActorFunc)Spinner_Init,
    (ActorFunc)Spinner_Destroy,
    (ActorFunc)Spinner_Update,
    (ActorFunc)Spinner_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    //radius, height, yshift, pos
    { 30, 30, 0, { 0, 0, 0 } },
};


void Spinner_Init(Actor* thisx, GlobalContext* globalCtx) {
    Spinner* this = THIS;

    Actor_SetScale(&this->actor, 0.0f);
    this->actor.gravity = -1.2f;
    this->initialSpeed = 4.0f + GET_PLAYER(globalCtx)->actor.speedXZ;

    ActorShape_Init(&thisx->shape, 700.0f, ActorShadow_DrawCircle, 16.0f);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, thisx, &sCylinderInit);

    this->actor.room = -1;
    this->timer = 0;
    this->scale = 0;
    this->actionFunc = Spinner_Action_PullOut;
}

void Spinner_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    Spinner* this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void Spinner_Update(Actor* thisx, GlobalContext* globalCtx) {
    Spinner* this = THIS;

    if ((this->actionFunc != Spinner_Action_PullOut) && CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_B)) {
        this->actionFunc = Spinner_Action_Disappear;
    }

    this->actionFunc(this, globalCtx);

    Actor_SetFocus(&this->actor, 50.0f);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 40.0f, 30.0f, 40.0f, 5);
    Collider_UpdateCylinder(thisx, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    this->actor.shape.rot.y += this->radialSpeed;
}

void Spinner_Action_Disappear(Spinner* this, GlobalContext* globalCtx) {
    s32 done = Math_StepToF(&this->scale, 0.0f, 0.007f);
    Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);

    Actor_SetScale(&this->actor, this->scale);
    Actor_MoveForward(&this->actor);

    if (done) {
        GET_PLAYER(globalCtx)->spinner = NULL;
        Actor_Kill(&this->actor);
        return;
    }
}

void Spinner_Action_PullOut(Spinner* this, GlobalContext* globalCtx) {
    s32 done = Math_StepToF(&this->scale, 0.035f, 0.007f);
    Math_StepToF(&this->actor.speedXZ, this->initialSpeed, 1.0f);

    Actor_SetScale(&this->actor, this->scale);
    Actor_MoveForward(&this->actor);

    if (done) {
        this->actionFunc = Spinner_Action_FreeCruising;
        return;
    }
}

void Spinner_Action_FreeCruising(Spinner* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    Math_StepToF(&this->actor.speedXZ, 0.85f, 0.05);
    if (this->actor.speedXZ <= 0.9f) {
        this->actionFunc = Spinner_Action_Disappear;
        return;
    }

    if ((this->actor.bgCheckFlags & 1) &&
        ((CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CLEFT) && (C_BTN_ITEM(0) == ITEM_SPINNER)) ||
        (CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CDOWN) && (C_BTN_ITEM(1) == ITEM_SPINNER)) ||
        (CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CRIGHT) && (C_BTN_ITEM(2) == ITEM_SPINNER)))) {
        this->timer = 0;
        this->actionFunc = Spinner_Action_SpinJump;
        return;
    }

    if (this->actor.bgCheckFlags & 8) {
        if (1) { // (SurfaceType_IsSpinnerSurface(&globalCtx->colCtx, this->actor.wallPoly, this->actor.wallBgId)) {
            this->actionFunc = Spinner_Action_SpinAlongSurface;
        }
        else {
            if (ABS((s16)(this->actor.wallYaw - this->actor.world.rot.y)) > 0x4000) {
                this->actor.world.rot.y = ((this->actor.wallYaw - this->actor.world.rot.y) + this->actor.wallYaw) - 0x8000;
            }
            this->actor.speedXZ *= 0.7f;
            this->actor.bgCheckFlags &= ~8;
        }
    }

    if (player->stateFlags1 & 0x8000000) {
        this->actionFunc = Spinner_Action_Disappear;
        return;
    }

    this->radialSpeed = this->actor.speedXZ * 400.0f;
    Actor_MoveForward(&this->actor);
}

void Spinner_Action_SpinJump(Spinner* this, GlobalContext* globalCtx) {
    if (this->timer < 10) {
        Math_StepToS(&this->radialSpeed, 4000, 800);
        this->actor.velocity.y = 5.0f;
    }
    else {
        if (Math_StepToS(&this->radialSpeed, (s16)(this->actor.speedXZ * 400.0f), 800)) {
            this->actionFunc = Spinner_Action_FreeCruising;
        }
    }
    this->timer++;
    Actor_MoveForward(&this->actor);
}

void Spinner_Action_SpinAlongSurface(Spinner* this, GlobalContext* globalCtx) {
    if ((this->actor.bgCheckFlags & 8) == 0) {
        this->actionFunc = Spinner_Action_FreeCruising;
        return;
    }

    if ((CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CLEFT) && (C_BTN_ITEM(0) == ITEM_SPINNER)) ||
        (CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CDOWN) && (C_BTN_ITEM(1) == ITEM_SPINNER)) ||
        (CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_CRIGHT) && (C_BTN_ITEM(2) == ITEM_SPINNER))) {
        this->timer = 0;
        this->actor.world.rot.y = this->actor.wallYaw;
        this->actionFunc = Spinner_Action_SpinJump;
        return;
    }

    if (((s16)(this->actor.wallYaw - this->actor.world.rot.y)) < 0) {
        this->actor.world.rot.y = this->actor.wallYaw + 0x4700;
    }
    else {
        this->actor.world.rot.y = this->actor.wallYaw - 0x4700;
    }

    Math_StepToF(&this->actor.speedXZ, 8.0f, 0.8f);
    Actor_MoveForward(&this->actor);
}

void Spinner_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_spinner.c", 46);

     gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_spinner.c", 104),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gSpinnerDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_spinner.c", 951);
}