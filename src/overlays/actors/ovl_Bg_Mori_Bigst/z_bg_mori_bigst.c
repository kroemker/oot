/*
 * File: z_bg_mori_bigst.c
 * Overlay: ovl_Bg_Mori_Bigst
 * Description: Forest Temple falling platform and Stalfos fight
 */

#include "z_bg_mori_bigst.h"
#include "assets/objects/object_mori_objects/object_mori_objects.h"
#include "quake.h"

#define FLAGS ACTOR_FLAG_4

void BgMoriBigst_Init(Actor* thisx, PlayState* play);
void BgMoriBigst_Destroy(Actor* thisx, PlayState* play);
void BgMoriBigst_Update(Actor* thisx, PlayState* play);
void BgMoriBigst_Draw(Actor* thisx, PlayState* play);

void BgMoriBigst_SetupWaitForMoriTex(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_WaitForMoriTex(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_SetupNoop(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_SetupStalfosFight(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_StalfosFight(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_SetupFall(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_Fall(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_SetupLanding(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_Landing(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_SetupStalfosPairFight(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_StalfosPairFight(BgMoriBigst* this, PlayState* play);
void BgMoriBigst_SetupDone(BgMoriBigst* this, PlayState* play);

ActorProfile Bg_Mori_Bigst_Profile = {
    /**/ ACTOR_BG_MORI_BIGST,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ OBJECT_MORI_OBJECTS,
    /**/ sizeof(BgMoriBigst),
    /**/ BgMoriBigst_Init,
    /**/ BgMoriBigst_Destroy,
    /**/ BgMoriBigst_Update,
    /**/ NULL,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),      ICHAIN_F32(uncullZoneScale, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 3000, ICHAIN_CONTINUE),     ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -12000, ICHAIN_CONTINUE), ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

void BgMoriBigst_SetupAction(BgMoriBigst* this, BgMoriBigstActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void BgMoriBigst_InitDynapoly(BgMoriBigst* this, PlayState* play, CollisionHeader* collision, s32 moveFlag) {
    s32 pad;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, moveFlag);
    CollisionHeader_GetVirtual(collision, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

#if OOT_DEBUG
    if (this->dyna.bgId == BG_ACTOR_MAX) {
        s32 pad2;

        PRINTF("Warning : move BG login failed(%s %d)(name %d)(arg_data 0x%04x)\n", "../z_bg_mori_bigst.c", 190,
               this->dyna.actor.id, this->dyna.actor.params);
    }
#endif
}

void BgMoriBigst_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    BgMoriBigst* this = (BgMoriBigst*)thisx;

    PRINTF("mori (bigST.keyceiling)(arg : %04x)(sw %d)(noE %d)(roomC %d)(playerPosY %f)\n", this->dyna.actor.params,
           Flags_GetSwitch(play, (this->dyna.actor.params >> 8) & 0x3F),
           Flags_GetTempClear(play, this->dyna.actor.room), Flags_GetClear(play, this->dyna.actor.room),
           GET_PLAYER(play)->actor.world.pos.y);
    BgMoriBigst_InitDynapoly(this, play, &gMoriBigstCol, 0);
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->moriTexObjectSlot = Object_GetSlot(&play->objectCtx, OBJECT_MORI_TEX);
    if (this->moriTexObjectSlot < 0) {
        PRINTF("【Big Stalfos key ceiling】 bank danger!！\n");
        PRINTF("%s %d\n", "../z_bg_mori_bigst.c", 234);
        Actor_Kill(&this->dyna.actor);
        return;
    }
    if (Flags_GetSwitch(play, (this->dyna.actor.params >> 8) & 0x3F)) {
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
    } else {
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 270.0f;
    }
    Actor_SetFocus(&this->dyna.actor, 50.0f);
    BgMoriBigst_SetupWaitForMoriTex(this, play);
}

void BgMoriBigst_Destroy(Actor* thisx, PlayState* play) {
    s32 pad;
    BgMoriBigst* this = (BgMoriBigst*)thisx;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgMoriBigst_SetupWaitForMoriTex(BgMoriBigst* this, PlayState* play) {
    BgMoriBigst_SetupAction(this, BgMoriBigst_WaitForMoriTex);
}

void BgMoriBigst_WaitForMoriTex(BgMoriBigst* this, PlayState* play) {
    Actor* thisx = &this->dyna.actor;

    if (Object_IsLoaded(&play->objectCtx, this->moriTexObjectSlot)) {
        thisx->draw = BgMoriBigst_Draw;
        if (Flags_GetClear(play, thisx->room) && (GET_PLAYER(play)->actor.world.pos.y > 700.0f)) {
            if (Flags_GetSwitch(play, (thisx->params >> 8) & 0x3F)) {
                BgMoriBigst_SetupDone(this, play);
            } else {
                BgMoriBigst_SetupStalfosFight(this, play);
            }
        } else {
            BgMoriBigst_SetupNoop(this, play);
        }
    }
}

void BgMoriBigst_SetupNoop(BgMoriBigst* this, PlayState* play) {
    BgMoriBigst_SetupAction(this, NULL);
}

void BgMoriBigst_SetupStalfosFight(BgMoriBigst* this, PlayState* play) {
    Actor* stalfos;

    BgMoriBigst_SetupAction(this, BgMoriBigst_StalfosFight);
    Flags_UnsetClear(play, this->dyna.actor.room);
    stalfos = Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, ACTOR_EN_TEST, 209.0f, 827.0f, -3320.0f, 0,
                                 0, 0, 1);
    if (stalfos != NULL) {
        this->dyna.actor.child = NULL;
        this->dyna.actor.home.rot.z++;
    } else {
        PRINTF("Warning : Second Stalfos failure\n");
    }
    Flags_SetClear(play, this->dyna.actor.room);
}

void BgMoriBigst_StalfosFight(BgMoriBigst* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((this->dyna.actor.home.rot.z == 0) &&
        ((this->dyna.actor.home.pos.y - 5.0f) <= GET_PLAYER(play)->actor.world.pos.y)) {
        BgMoriBigst_SetupFall(this, play);
        OnePointCutscene_Init(play, 3220, 72, &this->dyna.actor, CAM_ID_MAIN);
    }
}

void BgMoriBigst_SetupFall(BgMoriBigst* this, PlayState* play) {
    BgMoriBigst_SetupAction(this, BgMoriBigst_Fall);
}

void BgMoriBigst_Fall(BgMoriBigst* this, PlayState* play) {
    Actor_MoveXZGravity(&this->dyna.actor);
    if (this->dyna.actor.world.pos.y <= this->dyna.actor.home.pos.y) {
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
        BgMoriBigst_SetupLanding(this, play);
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_STONE_BOUND);
        OnePointCutscene_Init(play, 1020, 8, &this->dyna.actor, CAM_ID_MAIN);
        Player_SetCsAction(play, NULL, PLAYER_CSACTION_60);
    }
}

void BgMoriBigst_SetupLanding(BgMoriBigst* this, PlayState* play) {
    s32 pad;
    s32 quakeIndex;

    BgMoriBigst_SetupAction(this, BgMoriBigst_Landing);
    this->waitTimer = 18;

    quakeIndex = Quake_Request(GET_ACTIVE_CAM(play), QUAKE_TYPE_3);
    Quake_SetSpeed(quakeIndex, 25000);
    Quake_SetPerturbations(quakeIndex, 5, 0, 0, 0);
    Quake_SetDuration(quakeIndex, 16);
}

void BgMoriBigst_Landing(BgMoriBigst* this, PlayState* play) {
    if (this->waitTimer <= 0) {
        BgMoriBigst_SetupStalfosPairFight(this, play);
    }
}

void BgMoriBigst_SetupStalfosPairFight(BgMoriBigst* this, PlayState* play) {
    Actor* stalfos1;
    Actor* stalfos2;

    BgMoriBigst_SetupAction(this, BgMoriBigst_StalfosPairFight);
    Flags_UnsetClear(play, this->dyna.actor.room);
    stalfos1 = Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, ACTOR_EN_TEST, 70.0f, 827.0f, -3383.0f, 0,
                                  0, 0, 5);
    if (stalfos1 != NULL) {
        this->dyna.actor.child = NULL;
        this->dyna.actor.home.rot.z++;
    } else {
        PRINTF("Warning : Warning: 3-1 Stalfos failure\n");
    }
    stalfos2 = Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, ACTOR_EN_TEST, 170.0f, 827.0f, -3260.0f, 0,
                                  0, 0, 5);
    if (stalfos2 != NULL) {
        this->dyna.actor.child = NULL;
        this->dyna.actor.home.rot.z++;
    } else {
        PRINTF("Warning : Warning: 3-2 Stalfos failure\n");
    }
    Flags_SetClear(play, this->dyna.actor.room);
}

void BgMoriBigst_StalfosPairFight(BgMoriBigst* this, PlayState* play) {
    if ((this->dyna.actor.home.rot.z == 0) && !Player_InCsMode(play)) {
        Flags_SetSwitch(play, (this->dyna.actor.params >> 8) & 0x3F);
        BgMoriBigst_SetupDone(this, play);
    }
}

void BgMoriBigst_SetupDone(BgMoriBigst* this, PlayState* play) {
    BgMoriBigst_SetupAction(this, NULL);
}

void BgMoriBigst_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    BgMoriBigst* this = (BgMoriBigst*)thisx;

    Actor_SetFocus(&this->dyna.actor, 50.0f);
    if (this->waitTimer > 0) {
        this->waitTimer--;
    }
    if (DynaPolyActor_IsPlayerAbove(&this->dyna)) {
        Environment_ChangeLightSetting(play, 6);
    }
    if (this->actionFunc != NULL) {
        this->actionFunc(this, play);
    }
}

void BgMoriBigst_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    BgMoriBigst* this = (BgMoriBigst*)thisx;

    OPEN_DISPS(play->state.gfxCtx, "../z_bg_mori_bigst.c", 541);
    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, play->objectCtx.slots[this->moriTexObjectSlot].segment);

    gSPMatrix(POLY_OPA_DISP++, MATRIX_NEW(play->state.gfxCtx, "../z_bg_mori_bigst.c", 548),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_OPA_DISP++, gMoriBigstDL);
    CLOSE_DISPS(play->state.gfxCtx, "../z_bg_mori_bigst.c", 553);
}
