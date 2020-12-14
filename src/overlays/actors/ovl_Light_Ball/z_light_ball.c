/*
 * File: z_light_ball.c
 * Overlay: ovl_Light_Ball
 * Description: Light Ball. Spawned as primary magic attack.
 */

#include "z_light_ball.h"
#include "overlays/effects/ovl_Effect_Ss_Fhg_Flash/z_eff_ss_fhg_flash.h"

#define FLAGS 0x02000010

#define THIS ((LightBall*)thisx)

void LightBall_Init(Actor* thisx, GlobalContext* globalCtx);
void LightBall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void LightBall_Update(Actor* thisx, GlobalContext* globalCtx);
void LightBall_Draw(Actor* thisx, GlobalContext* globalCtx);

void LightBall_Fly(LightBall* this, GlobalContext* globalCtx);

const ActorInit Light_Ball_InitVars = {
    ACTOR_LIGHT_BALL,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_FHG,
    sizeof(LightBall),
    (ActorFunc)LightBall_Init,
    (ActorFunc)LightBall_Destroy,
    (ActorFunc)LightBall_Update,
    (ActorFunc)LightBall_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_STOP),
};

void LightBall_SetupAction(LightBall* this, LightBallActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void LightBall_Init(Actor* thisx, GlobalContext* globalCtx) {
    LightBall* this = THIS;
    Player* player = PLAYER;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    LightBall_SetupAction(this, LightBall_Fly);
    Actor_SetScale(&this->actor, 0.01f);
    this->timer = 30;
    this->actor.speedXZ = 17.0f;

    this->actor.posRot = player->actor.posRot;
    this->actor.posRot.pos.x += 25.0f * Math_Sins(player->actor.posRot.rot.y);
    this->actor.posRot.pos.y += 50.0f;
    this->actor.posRot.pos.z += 25.0f * Math_Coss(player->actor.posRot.rot.y);
}

void LightBall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void LightBall_Fly(LightBall* this, GlobalContext* globalCtx) {
    Vec3f pos;
    Vec3f vel = {0.0f, 0.0f, 0.0f};
    Vec3f accel = {0.0f, 0.0f, 0.0f};
    s16 i;

    Actor_MoveForward(&this->actor);

    for (i = 0; i < 3; i++) {
        vel.x = Math_Sins(this->actor.posRot.rot.y) * Math_Rand_CenteredFloat(4.0f);
        vel.y = Math_Rand_ZeroOne() * 2.0f;
        vel.z = Math_Coss(this->actor.posRot.rot.y) * Math_Rand_CenteredFloat(4.0f);

        EffectSsFhgFlash_SpawnLightBall(globalCtx, &this->actor.posRot.pos, &this->actor.velocity, &accel, 550, FHGFLASH_LIGHTBALL_GREEN);
    }
}

void LightBall_Update(Actor* thisx, GlobalContext* globalCtx) {
    LightBall* this = THIS;

    if (globalCtx->msgCtx.msgMode == 0xD || globalCtx->msgCtx.msgMode == 0x11) {
        Actor_Kill(&this->actor);
    } else {
        this->actionFunc(this, globalCtx);
    }

    if (this->timer > 0) {
        this->timer--;
    }
    else {
        Actor_Kill(&this->actor);
    }
}

void LightBall_Draw(Actor* thisx, GlobalContext* globalCtx) {
    /*LightBall* this = THIS;
    Actor* tranform;


    if ((arrow != NULL) && (arrow->actor.update != NULL)) {
        tranform = (arrow->hitWall & 2) ? &this->actor : &arrow->actor;

        OPEN_DISPS(globalCtx->state.gfxCtx, "../z_arrow_teleport.c", 618);

        Matrix_Translate(tranform->posRot.pos.x, tranform->posRot.pos.y, tranform->posRot.pos.z, MTXMODE_NEW);
        Matrix_RotateY(tranform->shape.rot.y * (M_PI / 32768), MTXMODE_APPLY);
        Matrix_RotateX(tranform->shape.rot.x * (M_PI / 32768), MTXMODE_APPLY);
        Matrix_RotateZ(tranform->shape.rot.z * (M_PI / 32768), MTXMODE_APPLY);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

        CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_arrow_teleport.c", 682);
    }*/
}
