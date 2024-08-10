/*
 * File: z_opening.c
 * Overlay: ovl_opening
 * Description: Initializes the game into the title screen
 */

#include "global.h"

void TitleSetup_SetupTitleScreen(TitleSetupState* this) {
    gSaveContext.gameMode = GAMEMODE_NORMAL;
    this->state.running = false;
    SET_NEXT_GAMESTATE(&this->state, MapSelect_Init, MapSelectState);
}

void func_80803C5C(TitleSetupState* this) {
}

void TitleSetup_Main(GameState* thisx) {
    TitleSetupState* this = (TitleSetupState*)thisx;

    Gfx_SetupFrame(this->state.gfxCtx, 0, 0, 0);
    TitleSetup_SetupTitleScreen(this);
    func_80803C5C(this);
}

void TitleSetup_Destroy(GameState* thisx) {
}

void TitleSetup_Init(GameState* thisx) {
    TitleSetupState* this = (TitleSetupState*)thisx;

    R_UPDATE_RATE = 1;
    Matrix_Init(&this->state);
    View_Init(&this->view, this->state.gfxCtx);
    this->state.main = TitleSetup_Main;
    this->state.destroy = TitleSetup_Destroy;
}
