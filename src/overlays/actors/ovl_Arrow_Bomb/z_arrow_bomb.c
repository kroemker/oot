/*
 * File: z_arrow_bomb.c
 * Overlay: ovl_Arrow_Bomb
 * Description: Bomb Arrow. Spawned as a child of a normal arrow.
 */

#include "z_arrow_bomb.h"
#include "overlays/actors/ovl_En_Arrow/z_en_arrow.h"

#define FLAGS 0x02000010

#define THIS ((ArrowBomb*)thisx)

void ArrowBomb_Init(Actor* thisx, GlobalContext* globalCtx);
void ArrowBomb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArrowBomb_Update(Actor* thisx, GlobalContext* globalCtx);
void ArrowBomb_Draw(Actor* thisx, GlobalContext* globalCtx);

void ArrowBomb_Charge(ArrowBomb* this, GlobalContext* globalCtx);
void ArrowBomb_Fly(ArrowBomb* this, GlobalContext* globalCtx);
void ArrowBomb_Hit(ArrowBomb* this, GlobalContext* globalCtx);

const ActorInit Arrow_Bomb_InitVars = {
    ACTOR_ARROW_BOMB,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(ArrowBomb),
    (ActorFunc)ArrowBomb_Init,
    (ActorFunc)ArrowBomb_Destroy,
    (ActorFunc)ArrowBomb_Update,
    (ActorFunc)ArrowBomb_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_STOP),
};

void ArrowBomb_SetupAction(ArrowBomb* this, ArrowBombActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ArrowBomb_Init(Actor* thisx, GlobalContext* globalCtx) {
    ArrowBomb* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ArrowBomb_SetupAction(this, ArrowBomb_Charge);
    Actor_SetScale(&this->actor, 0.01f);
    this->bomb = NULL;
    this->bombScale = 0.0f;
}

void ArrowBomb_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    func_800876C8(globalCtx);
    // Translates to: "Disappearance"
    LOG_STRING("消滅", "../z_arrow_bomb.c", 421);
}

void ArrowBomb_Charge(ArrowBomb* this, GlobalContext* globalCtx) {
    EnArrow* arrow;

    arrow = (EnArrow*)this->actor.parent;
    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_Kill(this->bomb);
        Actor_Kill(&this->actor);
        return;
    }

    // copy position and rotation from arrow
    this->actor.world.pos = arrow->actor.world.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;
    Math_StepToF(&this->bombScale, 0.005f, 0.001f);

    // if arrow has no parent, player has fired the arrow
    if (arrow->actor.parent == NULL) {
        ArrowBomb_SetupAction(this, ArrowBomb_Fly);
    }
}

void ArrowBomb_Hit(ArrowBomb* this, GlobalContext* globalCtx) {
    ((EnBom*)this->bomb)->timer = 0;
    Actor_Kill(&this->actor);
}

void ArrowBomb_Fly(ArrowBomb* this, GlobalContext* globalCtx) {
    EnArrow* arrow;

    arrow = (EnArrow*)this->actor.parent;
    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_Kill(this->bomb);
        Actor_Kill(&this->actor);
        return;
    }
    // copy position and rotation from arrow
    this->actor.world.pos = arrow->actor.world.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;
    Math_StepToF(&this->bombScale, 0.01f, 0.001f);

    if (arrow->hitFlags & 1) {
        ArrowBomb_SetupAction(this, ArrowBomb_Hit);
    } else if (arrow->timer < 2) {
        ((EnBom*)this->bomb)->timer = 0;
        Actor_Kill(&this->actor);
    }
}

void ArrowBomb_Update(Actor* thisx, GlobalContext* globalCtx) {
    ArrowBomb* this = THIS;

    if (globalCtx->msgCtx.msgMode == 0xD || globalCtx->msgCtx.msgMode == 0x11) {
        Actor_Kill(this->bomb);
        Actor_Kill(&this->actor);
    } else {
        if (this->bomb == NULL) {
            this->bomb = Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_BOM, 
            0, 0, 0, 0, 0, 0, 0);
        }
        ((EnBom*)this->bomb)->timer = 60;
        Actor_SetScale(this->bomb, this->bombScale);
        this->bomb->world.pos = this->actor.world.pos;
        this->bomb->world.pos.x += Math_SinS(this->actor.shape.rot.y) * 4.0f;
        this->bomb->world.pos.y -= 20;
        this->bomb->world.pos.z += Math_CosS(this->actor.shape.rot.y) * 4.0f;

        this->actionFunc(this, globalCtx);
    }
}

void ArrowBomb_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ArrowBomb* this = THIS;
    EnArrow* arrow;
    Actor* tranform;

    arrow = (EnArrow*)this->actor.parent;

    if ((arrow != NULL) && (arrow->actor.update != NULL)) {
        tranform = (arrow->hitFlags & 2) ? &this->actor : &arrow->actor;

        OPEN_DISPS(globalCtx->state.gfxCtx, "../z_arrow_bomb.c", 618);

        Matrix_Translate(tranform->world.pos.x, tranform->world.pos.y, tranform->world.pos.z, MTXMODE_NEW);
        Matrix_RotateY(tranform->shape.rot.y * (M_PI / 32768), MTXMODE_APPLY);
        Matrix_RotateX(tranform->shape.rot.x * (M_PI / 32768), MTXMODE_APPLY);
        Matrix_RotateZ(tranform->shape.rot.z * (M_PI / 32768), MTXMODE_APPLY);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

        CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_arrow_bomb.c", 682);
    }
}
