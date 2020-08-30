/*
 * File: z_bg_mizu_water.c
 * Overlay: ovl_Bg_Mizu_Water
 * Description: Water plane in Water Temple. Changes height based on switches 0x1C, 0x1D, 0x1E.
 */

#include "z_bg_mizu_water.h"

#define FLAGS 0x00000030

#define THIS ((BgMizuWater*)thisx)

void BgMizuWater_Init(Actor* thisx, GlobalContext* globalCtx);
void BgMizuWater_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgMizuWater_Update(Actor* thisx, GlobalContext* globalCtx);
void BgMizuWater_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgMizuWater_Idle(BgMizuWater* this, GlobalContext* globalCtx);
void BgMizuWater_ChangeWaterLevel(BgMizuWater* this, GlobalContext* globalCtx);

extern UNK_TYPE D_06004B20;

typedef struct {
    s32 switchID;
    s32 yDiff;
} WaterLevel;

static WaterLevel waterLevels[] = {
    { 0x00, 0 },
    { 0x1E, 0 },
    { 0x1D, -320 },
    { 0x1C, -780 },
};

const ActorInit Bg_Mizu_Water_InitVars = {
    ACTOR_BG_MIZU_WATER,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_MIZU_OBJECTS,
    sizeof(BgMizuWater),
    (ActorFunc)BgMizuWater_Init,
    (ActorFunc)BgMizuWater_Destroy,
    (ActorFunc)BgMizuWater_Update,
    (ActorFunc)BgMizuWater_Draw,
};

static u32 unk_808A0550 = 0;
static f32 unk_808A0554 = 110.0f;

static u32 waterBoxIDs[] = { 0x00000002, 0x00000003, 0x00000005, 0x00000007,
                             0x0000000C, 0x00000014, 0x00000015, 0x00000016 };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_STOP),
};

u32 BgMizuWater_getWaterLevelActionIndex(s16 switchID, GlobalContext* globalCtx) {
    u32 ret;

    if (bREG(0) != 0) {
        switch (bREG(1)) {
            case 0:
                Flags_SetSwitch(globalCtx, 0x1C);
                break;
            case 1:
                Flags_SetSwitch(globalCtx, 0x1D);
                break;
            case 2:
                Flags_SetSwitch(globalCtx, 0x1E);
                break;
        }
        bREG(0) = 0;
    }
    if ((Flags_GetSwitch(globalCtx, 0x1C) != 0) && (switchID != 0x1C))
        ret = 3;
    else if ((Flags_GetSwitch(globalCtx, 0x1D) != 0) && (switchID != 0x1D))
        ret = 2;
    else if ((Flags_GetSwitch(globalCtx, 0x1E) != 0) && (switchID != 0x1E))
        ret = 1;
    else
        ret = 0;

    return ret;
}

void BgMizuWater_setWaterBoxesHeights(WaterBox* waterBoxes, s16 height) {
    u32 i;

    for (i = 0; i < 8; i += 4) {
        waterBoxes[waterBoxIDs[i]].unk_02 = height;
        waterBoxes[waterBoxIDs[i + 1]].unk_02 = height;
        waterBoxes[waterBoxIDs[i + 2]].unk_02 = height;
        waterBoxes[waterBoxIDs[i + 3]].unk_02 = height;
    }
}

void BgMizuWater_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgMizuWater* this = THIS;
    f32 initialActorY;
    WaterBox* waterBoxes;
    s32 waterLevelActionIndex;

    waterBoxes = globalCtx->colCtx.stat.colHeader->waterBoxes;
    this->type = this->actor.params & 0xFF;
    this->switchTriggerID = (this->actor.params >> 8) & 0xFF;
    Actor_ProcessInitChain(&this->actor, sInitChain);
    initialActorY = this->actor.posRot.pos.y;
    this->baseY = initialActorY;
    this->targetY = initialActorY;

    switch (this->type) {
        case 0:
            if (bREG(15) == 0) {
                osSyncPrintf("<コンストラクト>%x %x %x\n", Flags_GetSwitch(globalCtx, 0x1C),
                             Flags_GetSwitch(globalCtx, 0x1D), Flags_GetSwitch(globalCtx, 0x1E));
            }
            waterLevelActionIndex = BgMizuWater_getWaterLevelActionIndex(-1, globalCtx);
            this->actor.posRot.pos.y = waterLevels[waterLevelActionIndex].yDiff + this->baseY;
            BgMizuWater_setWaterBoxesHeights(waterBoxes, this->actor.posRot.pos.y);
            this->actor.params = waterLevels[waterLevelActionIndex].switchID;
            Flags_UnsetSwitch(globalCtx, 0x1C);
            Flags_UnsetSwitch(globalCtx, 0x1D);
            Flags_UnsetSwitch(globalCtx, 0x1E);

            switch (this->actor.params) {
                case 0x1E:
                    Flags_SetSwitch(globalCtx, 0x1E);
                    break;
                case 0x1D:
                    Flags_SetSwitch(globalCtx, 0x1D);
                    break;
                case 0x1C:
                default:
                    Flags_SetSwitch(globalCtx, 0x1C);
                    break;
            }
            this->targetY = this->actor.posRot.pos.y;
            break;
        case 1:
            break;
        case 2:
            if (Flags_GetSwitch(globalCtx, this->switchTriggerID) != 0) {
                this->actor.posRot.pos.y = this->baseY + 85.0f;
            }
            waterBoxes[6].unk_02 = this->actor.posRot.pos.y;
            break;
        case 3:
            if (Flags_GetSwitch(globalCtx, this->switchTriggerID) != 0) {
                this->actor.posRot.pos.y = this->baseY + 110.0f;
                if (1) {}
                this->targetY = this->actor.posRot.pos.y;
            }
            waterBoxes[8].unk_02 = this->actor.posRot.pos.y;
            break;
        case 4:
            if (Flags_GetSwitch(globalCtx, this->switchTriggerID) != 0) {
                this->actor.posRot.pos.y = this->baseY + 160.0f;
                if (1) {}
                this->targetY = this->actor.posRot.pos.y;
            }
            waterBoxes[16].unk_02 = this->actor.posRot.pos.y;
            break;
    }

    this->actionFunc = BgMizuWater_Idle;
}

void BgMizuWater_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void BgMizuWater_Idle(BgMizuWater* this, GlobalContext* globalCtx) {
    u32 pad;
    s32 waterLevelActionIndex;
    s16 params;

    switch (this->type) {
        case 0:
            params = this->actor.params;
            waterLevelActionIndex = BgMizuWater_getWaterLevelActionIndex(this->actor.params, globalCtx);
            if (waterLevelActionIndex != 0) {
                if (params != waterLevels[waterLevelActionIndex].switchID) {
                    func_800800F8(globalCtx, 0xC30, -0x64 - waterLevelActionIndex, 0, 0);
                    this->actor.params = waterLevels[waterLevelActionIndex].switchID;
                    this->targetY = waterLevels[waterLevelActionIndex].yDiff + this->baseY;
                }
            }
            if ((params != this->actor.params) && (params != 0))
                Flags_UnsetSwitch(globalCtx, params);
            break;
        case 1:
            break;
        case 2:
            if (Flags_GetSwitch(globalCtx, this->switchTriggerID) != 0)
                this->targetY = this->baseY + 85.0f;
            else
                this->targetY = this->baseY;
            break;
        case 3:
            if (Flags_GetSwitch(globalCtx, this->switchTriggerID) != 0)
                this->targetY = this->baseY + 110.0f;
            else
                this->targetY = this->baseY;
            break;
        case 4:
            if (Flags_GetSwitch(globalCtx, this->switchTriggerID) != 0)
                this->targetY = this->baseY + 160.0f;
            else
                this->targetY = this->baseY;
    }

    if (this->targetY != this->actor.posRot.pos.y) {
        this->actionFunc = BgMizuWater_ChangeWaterLevel;
    }
}

void BgMizuWater_ChangeWaterLevel(BgMizuWater* this, GlobalContext* globalCtx) {
    u32 pad;
    s16 params;
    s32 waterLevelActionIndex;
    WaterBox* waterBoxes;

    waterBoxes = globalCtx->colCtx.stat.colHeader->waterBoxes;
    switch (this->type) {
        case 0:
            params = this->actor.params;
            waterLevelActionIndex = BgMizuWater_getWaterLevelActionIndex(this->actor.params, globalCtx);
            if (waterLevelActionIndex != 0) {
                if (params != waterLevels[waterLevelActionIndex].switchID) {
                    this->actor.params = waterLevels[waterLevelActionIndex].switchID;
                    this->targetY = waterLevels[waterLevelActionIndex].yDiff + this->baseY;
                }
            }

            if ((params != this->actor.params) && (params != 0))
                Flags_UnsetSwitch(globalCtx, params);

            if (Math_ApproxF(&this->actor.posRot.pos.y, this->targetY, 5.0f) != 0) {
                globalCtx->unk_11D30[0] = 0;
                this->actionFunc = BgMizuWater_Idle;
                func_80106CCC(globalCtx);
            }
            BgMizuWater_setWaterBoxesHeights(globalCtx->colCtx.stat.colHeader->waterBoxes, this->actor.posRot.pos.y);
            break;
        case 1:
            break;
        case 2:
            if (Flags_GetSwitch(globalCtx, this->switchTriggerID) != 0) {
                this->targetY = this->baseY + 85.0f;
            } else {
                this->targetY = this->baseY;
            }
            if (Math_ApproxF(&this->actor.posRot.pos.y, this->targetY, 1.0f) != 0) {
                globalCtx->unk_11D30[0] = 0;
                this->actionFunc = BgMizuWater_Idle;
            }
            waterBoxes[6].unk_02 = this->actor.posRot.pos.y;
            break;
        case 3:
            if (Flags_GetSwitch(globalCtx, this->switchTriggerID) != 0) {
                this->targetY = this->baseY + 110.0f;
            } else {
                this->targetY = this->baseY;
            }
            if (Math_ApproxF(&this->actor.posRot.pos.y, this->targetY, 1.0f) != 0) {
                globalCtx->unk_11D30[0] = 0;
                this->actionFunc = BgMizuWater_Idle;
            }
            waterBoxes[8].unk_02 = this->actor.posRot.pos.y;
            break;
        case 4:
            if (Flags_GetSwitch(globalCtx, this->switchTriggerID) != 0) {
                this->targetY = this->baseY + 160.0f;
            } else {
                this->targetY = this->baseY;
            }
            if (Math_ApproxF(&this->actor.posRot.pos.y, this->targetY, 1.0f) != 0) {
                globalCtx->unk_11D30[0] = 0;
                this->actionFunc = BgMizuWater_Idle;
            }
            waterBoxes[16].unk_02 = this->actor.posRot.pos.y;
            break;
    }

    if (this->targetY < this->actor.posRot.pos.y) {
        func_800AA000(0.0f, 0x78, 0x14, 0xA);
        func_8002F948(&this->actor, NA_SE_EV_WATER_LEVEL_DOWN - SFX_FLAG);
    } else if (this->targetY > this->actor.posRot.pos.y) {
        func_800AA000(0.0f, 0x78, 0x14, 0xA);
        func_8002F948(&this->actor, NA_SE_EV_WATER_LEVEL_DOWN - SFX_FLAG);
    }
}

void BgMizuWater_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgMizuWater* this = THIS;
    s32 y;
    s32 unk0;
    s32 unk1;
    u32 pad;

    if (bREG(15) == 0) {
        osSyncPrintf("%x %x %x\n", Flags_GetSwitch(globalCtx, 0x1C), Flags_GetSwitch(globalCtx, 0x1D),
                     Flags_GetSwitch(globalCtx, 0x1E));
    }

    if (this->type == 0) {
        y = this->actor.posRot.pos.y;
        unk0 = 0;
        unk1 = 0;
        if (y < -15.0f) {
            unk0 = 0;
            unk1 = ((y - -835.0f) / 820.0f) * 200.0f;
        } else if (y < 445.0f) {
            unk0 = 1;
            unk1 = 0xFF - (s32)(((y - -15.0f) / 460.0f) * 95.0f);
        } else if (y <= 765.0f) {
            unk0 = 2;
            unk1 = 0xFF - (s32)(((y - 445.0f) / 320.0f) * 95.0f);
        }
        globalCtx->unk_11D30[1] = ((u8)unk0 << 8) | (unk1 & 0xFF);
    }

    this->actionFunc(this, globalCtx);
}

void BgMizuWater_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgMizuWater* this = THIS;
    s32 gameplayFrames;
    GraphicsContext* gfxCtx;
    Gfx* dispRefs[4];

    gfxCtx = globalCtx->state.gfxCtx;
    Graph_OpenDisps(dispRefs, globalCtx->state.gfxCtx, "../z_bg_mizu_water.c", 738);
    gameplayFrames = globalCtx->gameplayFrames;
    func_80093D84(globalCtx->state.gfxCtx);

    gSPSegment(gfxCtx->polyXlu.p++, 0x0C,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, -gameplayFrames * 1, gameplayFrames * 1, 32, 32, 1, 0,
                                -gameplayFrames * 1, 32, 32));

    gSPMatrix(gfxCtx->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_bg_mizu_water.c", 749),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xFF, 0xFF, 0x80);

    gDPSetPrimColor(gfxCtx->polyXlu.p++, 0, 0, 0xFF, 0xFF, 0xFF, 0x66);

    gSPDisplayList(gfxCtx->polyXlu.p++, &D_06004B20);

    Graph_CloseDisps(dispRefs, globalCtx->state.gfxCtx, "../z_bg_mizu_water.c", 756);
}
