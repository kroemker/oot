/*
 * File: z_light_ball.c
 * Overlay: ovl_Light_Ball
 * Description: Holding Item Conserver.
 */

#include "z_light_ball.h"

#define FLAGS 0x02000010

#define THIS ((LightBall*)thisx)

void LightBall_Init(Actor* thisx, GlobalContext* globalCtx);
void LightBall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void LightBall_Update(Actor* thisx, GlobalContext* globalCtx);
void LightBall_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Light_Ball_InitVars = {
    ACTOR_MAGIC_CONSERVE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
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
    Actor_SetScale(&this->actor, 0.01f);

    if (player->conservedActorId > 0) {
        Actor* conservedActor= Actor_Spawn(&globalCtx->actorCtx, globalCtx, player->conservedActorId, 0, 0, 0, 0, 0, 0, player->conservedActorParams);
        if (player->heldActor != NULL) {
            player->conservedActorId = player->heldActor->id;
            player->conservedActorParams = player->heldActor->params;
            Actor_Kill(player->heldActor);
        }
        else {
            player->conservedActorId = 0;
            player->conservedActorParams = 0;
        }
        player->heldActor = conservedActor;
    }
    else if (player->heldActor != NULL) {
        player->conservedActorId = player->heldActor->id;
        player->conservedActorParams = player->heldActor->params;
        Actor_Kill(player->heldActor);
        player->heldActor = NULL;
    }
}

void LightBall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void LightBall_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void LightBall_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
