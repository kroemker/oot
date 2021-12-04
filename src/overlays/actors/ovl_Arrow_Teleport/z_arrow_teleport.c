/*
 * File: z_arrow_teleport.c
 * Overlay: ovl_Arrow_Teleport
 * Description: Teleport Arrow. Spawned as a child of a normal arrow.
 */

#include "z_arrow_teleport.h"
#include "overlays/actors/ovl_En_Arrow/z_en_arrow.h"

#define FLAGS 0x02000010

#define THIS ((ArrowTeleport*)thisx)

void ArrowTeleport_Init(Actor* thisx, GlobalContext* globalCtx);
void ArrowTeleport_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArrowTeleport_Update(Actor* thisx, GlobalContext* globalCtx);
void ArrowTeleport_Draw(Actor* thisx, GlobalContext* globalCtx);

void ArrowTeleport_Charge(ArrowTeleport* this, GlobalContext* globalCtx);
void ArrowTeleport_Fly(ArrowTeleport* this, GlobalContext* globalCtx);
void ArrowTeleport_Hit(ArrowTeleport* this, GlobalContext* globalCtx);

static u64 s1Tex[256];
static u64 s2Tex[256];
static Vtx sVtx[43];
static Gfx sMaterialDL[22];
static Gfx sModelDL[24];

static u64 s1Tex[256] = {
#include "assets/overlays/ovl_Arrow_Light/light_tex_1.ia8.inc.c"
};

static u64 s2Tex[256] = {
#include "assets/overlays/ovl_Arrow_Light/light_tex_2.ia8.inc.c"
};

static Vtx sVtx[43] = {
#include "assets/overlays/ovl_Arrow_Light/sVtx.vtx.inc"
};

static Gfx sMaterialDL[22] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(s1Tex, G_IM_FMT_I, G_IM_SIZ_8b, 32, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                         5, 6, 13, 15),
    gsDPLoadMultiBlock(s2Tex, 0x0100, 1, G_IM_FMT_I, G_IM_SIZ_8b, 32, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_MIRROR |
                       G_TX_WRAP, 5, 6, 14, 14),
    gsDPSetCombineLERP(TEXEL1, PRIMITIVE, ENV_ALPHA, TEXEL0, TEXEL1, 1, ENVIRONMENT, TEXEL0, PRIMITIVE, ENVIRONMENT,
                       COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_CLD_SURF2),
    gsSPClearGeometryMode(G_CULL_BACK | G_FOG | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

static Gfx sModelDL[24] = {
    gsSPVertex(sVtx, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
    gsSP2Triangles(5, 4, 6, 0, 2, 7, 8, 0),
    gsSP2Triangles(2, 8, 4, 0, 4, 8, 9, 0),
    gsSP2Triangles(4, 9, 6, 0, 6, 9, 10, 0),
    gsSP2Triangles(8, 11, 12, 0, 8, 12, 9, 0),
    gsSP2Triangles(9, 12, 13, 0, 9, 13, 10, 0),
    gsSP2Triangles(10, 13, 14, 0, 12, 15, 16, 0),
    gsSP2Triangles(12, 16, 13, 0, 13, 16, 17, 0),
    gsSP2Triangles(13, 17, 14, 0, 14, 17, 18, 0),
    gsSP2Triangles(16, 19, 17, 0, 17, 19, 20, 0),
    gsSP2Triangles(17, 20, 18, 0, 21, 22, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 24, 26, 22, 0),
    gsSP2Triangles(22, 26, 27, 0, 22, 27, 23, 0),
    gsSP2Triangles(23, 27, 28, 0, 26, 29, 30, 0),
    gsSP2Triangles(26, 30, 27, 0, 27, 30, 31, 0),
    gsSP1Triangle(27, 31, 28, 0),
    gsSPVertex(&sVtx[32], 11, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 1, 0, 1, 5, 6, 0),
    gsSP2Triangles(1, 6, 2, 0, 2, 6, 7, 0),
    gsSP1Triangle(8, 9, 10, 0),
    gsSPEndDisplayList(),
};

const ActorInit Arrow_Teleport_InitVars = {
    ACTOR_ARROW_FOREST,
    ACTORCAT_ITEMACTION,
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
    
    this->alpha = 130;
    this->radius = 0;
    this->unk_160 = 1.0f;
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

    if (this->radius < 10) {
        this->radius += 1;
    }
    // copy position and rotation from arrow
    this->actor.world.pos = arrow->actor.world.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;

    // if arrow has no parent, player has fired the arrow
    if (arrow->actor.parent == NULL) {
        this->radius = 10;
        this->alpha = 255;
        ArrowTeleport_SetupAction(this, ArrowTeleport_Fly);
    }
}

void ArrowTeleport_WaitForDeletion(ArrowTeleport* this, GlobalContext* globalCtx) {
    EnArrow* arrow = (EnArrow*)this->actor.parent;
    if (this->alpha > 10) {
        this->alpha -= 10;
        this->radius += 15;
    }
    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_Kill(&this->actor);
        return;
    }
}

void ArrowTeleport_Hit(ArrowTeleport* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    
    Vec3f pos = player->actor.world.pos;
    pos.x += Math_SinS(player->actor.world.rot.y) * 15.0f;
    pos.z += Math_CosS(player->actor.world.rot.y) * 15.0f;
    
    ArrowTeleport_SetupAction(this, ArrowTeleport_WaitForDeletion);
}

void ArrowTeleport_Fly(ArrowTeleport* this, GlobalContext* globalCtx) {
    EnArrow* arrow;

    arrow = (EnArrow*)this->actor.parent;
    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_Kill(&this->actor);
        return;
    }
    // copy position and rotation from arrow
    this->actor.world.pos = arrow->actor.world.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;

    if (arrow->hitFlags & 1) {
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
    u32 stateFrames = globalCtx->state.frames;
    Actor* tranform;

    arrow = (EnArrow*)this->actor.parent;

    if ((arrow != NULL) && (arrow->actor.update != NULL)) {
        tranform = (arrow->hitFlags & 2) ? &this->actor : &arrow->actor;

        OPEN_DISPS(globalCtx->state.gfxCtx, "../z_arrow_teleport.c", 137);

        Matrix_Translate(tranform->world.pos.x, tranform->world.pos.y, tranform->world.pos.z, MTXMODE_NEW);
        Matrix_RotateY(tranform->shape.rot.y * (M_PI / 0x8000), MTXMODE_APPLY);
        Matrix_RotateX(tranform->shape.rot.x * (M_PI / 0x8000), MTXMODE_APPLY);
        Matrix_RotateZ(tranform->shape.rot.z * (M_PI / 0x8000), MTXMODE_APPLY);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

        // Draw effect on the arrow
        func_80093D84(globalCtx->state.gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 170, 255, 170, this->alpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 255, 0, 128);
        Matrix_RotateZYX(0x4000, 0x0, 0x0, MTXMODE_APPLY);
        if (arrow->timer != 0) {
            Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        } else {
            Matrix_Translate(0.0f, 1500.0f, 0.0f, MTXMODE_APPLY);
        }
        Matrix_Scale(this->radius * 0.2f, this->unk_160 * 4.0f, this->radius * 0.2f, MTXMODE_APPLY);
        Matrix_Translate(0.0f, -700.0f, 0.0f, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_arrow_teleport.c", 167),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, sMaterialDL);
        gSPDisplayList(POLY_XLU_DISP++,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 511 - (stateFrames * 5) % 512, 0, 4, 32, 1,
                                        511 - (stateFrames * 10) % 512, 511 - (stateFrames * 30) % 512, 8, 16));
        gSPDisplayList(POLY_XLU_DISP++, sModelDL);

        CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_arrow_teleport.c", 175);
    }
}
