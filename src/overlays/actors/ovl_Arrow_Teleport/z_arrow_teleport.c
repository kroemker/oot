/*
 * File: z_arrow_teleport.c
 * Overlay: ovl_Arrow_Teleport
 * Description: Teleport Arrow. Spawned as a child of a normal arrow.
 */

#include "z_arrow_teleport.h"
#include "overlays/actors/ovl_En_Arrow/z_en_arrow.h"
#include "overlays/effects/ovl_Effect_Ss_Fhg_Flash/z_eff_ss_fhg_flash.h"

#define FLAGS 0x02000010

#define THIS ((ArrowTeleport*)thisx)

void ArrowTeleport_Init(Actor* thisx, GlobalContext* globalCtx);
void ArrowTeleport_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArrowTeleport_Update(Actor* thisx, GlobalContext* globalCtx);
void ArrowTeleport_Draw(Actor* thisx, GlobalContext* globalCtx);

void ArrowTeleport_Charge(ArrowTeleport* this, GlobalContext* globalCtx);
void ArrowTeleport_Fly(ArrowTeleport* this, GlobalContext* globalCtx);
void ArrowTeleport_Hit(ArrowTeleport* this, GlobalContext* globalCtx);

const ActorInit Arrow_Teleport_InitVars = {
    ACTOR_ARROW_BOMB,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(ArrowTeleport),
    (ActorFunc)ArrowTeleport_Init,
    (ActorFunc)ArrowTeleport_Destroy,
    (ActorFunc)ArrowTeleport_Update,
    (ActorFunc)ArrowTeleport_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_STOP),
};

static s32 sTestActor = 0xDEADBEEF;
static s32 sActorVar = 0xABCD1234;

void ArrowTeleport_SetupAction(ArrowTeleport* this, ArrowTeleportActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ArrowTeleport_Init(Actor* thisx, GlobalContext* globalCtx) {
    ArrowTeleport* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ArrowTeleport_SetupAction(this, ArrowTeleport_Charge);
    Actor_SetScale(&this->actor, 0.01f);
}

void ArrowTeleport_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    func_800876C8(globalCtx);
    // Translates to: "Disappearance"
    LOG_STRING("消滅", "../z_arrow_teleport.c", 421);
}

void ArrowTeleport_Charge(ArrowTeleport* this, GlobalContext* globalCtx) {
    EnArrow* arrow;

    arrow = (EnArrow*)this->actor.parent;
    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_Kill(&this->actor);
        return;
    }

    // copy position and rotation from arrow
    this->actor.posRot.pos = arrow->actor.posRot.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;

    // if arrow has no parent, player has fired the arrow
    if (arrow->actor.parent == NULL) {
        ArrowTeleport_SetupAction(this, ArrowTeleport_Fly);
    }
}

void ArrowTeleport_WaitForDeletion(ArrowTeleport* this, GlobalContext* globalCtx) {
    EnArrow* arrow = (EnArrow*)this->actor.parent;
    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_Kill(&this->actor);
        return;
    }
}

void ArrowTeleport_Hit(ArrowTeleport* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f pos = player->actor.posRot.pos;
    pos.x += Math_Sins(player->actor.posRot.rot.y) * 15.0f;
    pos.z += Math_Coss(player->actor.posRot.rot.y) * 15.0f;
    //player->actor.posRot.pos = this->actor.posRot.pos;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, sTestActor, pos.x, pos.y, pos.z, 0, 0, 0, sActorVar);

    Actor_Kill(&this->actor);
}

void ArrowTeleport_Fly(ArrowTeleport* this, GlobalContext* globalCtx) {
    EnArrow* arrow;

    arrow = (EnArrow*)this->actor.parent;
    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_Kill(&this->actor);
        return;
    }
    // copy position and rotation from arrow
    this->actor.posRot.pos = arrow->actor.posRot.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;

    if (arrow->hitWall & 1) {
        ArrowTeleport_SetupAction(this, ArrowTeleport_Hit);
    } else if (arrow->timer < 2) {
        Actor_Kill(&this->actor);
    }
}

void ArrowTeleport_Update(Actor* thisx, GlobalContext* globalCtx) {
    ArrowTeleport* this = THIS;

    if (globalCtx->msgCtx.msgMode == 0xD || globalCtx->msgCtx.msgMode == 0x11) {
        Actor_Kill(&this->actor);
    } else {
        this->actionFunc(this, globalCtx);
    }
}

void ArrowTeleport_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ArrowTeleport* this = THIS;
    EnArrow* arrow;
    Actor* tranform;

    arrow = (EnArrow*)this->actor.parent;

    if ((arrow != NULL) && (arrow->actor.update != NULL)) {
        tranform = (arrow->hitWall & 2) ? &this->actor : &arrow->actor;

        OPEN_DISPS(globalCtx->state.gfxCtx, "../z_arrow_teleport.c", 618);

        Matrix_Translate(tranform->posRot.pos.x, tranform->posRot.pos.y, tranform->posRot.pos.z, MTXMODE_NEW);
        Matrix_RotateY(tranform->shape.rot.y * (M_PI / 32768), MTXMODE_APPLY);
        Matrix_RotateX(tranform->shape.rot.x * (M_PI / 32768), MTXMODE_APPLY);
        Matrix_RotateZ(tranform->shape.rot.z * (M_PI / 32768), MTXMODE_APPLY);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

        CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_arrow_teleport.c", 682);
    }
}
