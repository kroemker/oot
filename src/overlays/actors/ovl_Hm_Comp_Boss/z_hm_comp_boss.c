/*
 * File: z_hm_comp_boss.c
 * Overlay: ovl_Hm_Comp_Boss
 * Description: Hm comp boss
 */

#include "z_hm_comp_boss.h"
#include "assets/objects/object_dh/object_dh.h"

#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_4 | ACTOR_FLAG_5)

void HmCompBoss_Init(Actor* thisx, PlayState* play);
void HmCompBoss_Destroy(Actor* thisx, PlayState* play);
void HmCompBoss_Update(Actor* thisx, PlayState* play);
void HmCompBoss_Draw(Actor* thisx, PlayState* play);

void HmCompBoss_Action_Appear(HmCompBoss* this, PlayState* play);
void HmCompBoss_Action_Idle(HmCompBoss* this, PlayState* play);
void HmCompBoss_Action_Attack(HmCompBoss* this, PlayState* play);

ActorProfile Hm_Comp_Boss_Profile = {
    /**/ ACTOR_HM_COMP_BOSS,
    /**/ ACTORCAT_BOSS,
    /**/ FLAGS,
    /**/ OBJECT_DH,
    /**/ sizeof(HmCompBoss),
    /**/ HmCompBoss_Init,
    /**/ HmCompBoss_Destroy,
    /**/ HmCompBoss_Update,
    /**/ HmCompBoss_Draw,
};

void HmCompBoss_SetupAction(HmCompBoss* this, PlayState* play, HmCompBossActionFunc actionFunc) {
    this->actionFunc = actionFunc;

    if (this->actionFunc == HmCompBoss_Action_Appear) {
        Animation_Change(&this->skelAnime, &object_dh_Anim_005880, 1.0f, 0.0f, Animation_GetLastFrame(&object_dh_Anim_005880), ANIMMODE_ONCE_INTERP, 4.0f);
    } else if (this->actionFunc == HmCompBoss_Action_Idle) {
        Animation_Change(&this->skelAnime, &object_dh_Anim_0015B0, 1.0f, 0.0f, Animation_GetLastFrame(&object_dh_Anim_0015B0), ANIMMODE_LOOP, 4.0f);
    } else if (this->actionFunc == HmCompBoss_Action_Attack) {
        Animation_Change(&this->skelAnime, &object_dh_Anim_0015B0, 1.0f, 0.0f, Animation_GetLastFrame(&object_dh_Anim_0015B0), ANIMMODE_LOOP, 4.0f);
    }
}

void HmCompBoss_Action_Attack(HmCompBoss* this, PlayState* play) {
}

void HmCompBoss_Action_Appear(HmCompBoss* this, PlayState* play) {
}

void HmCompBoss_Action_Idle(HmCompBoss* this, PlayState* play) {
}

void HmCompBoss_Init(Actor* thisx, PlayState* play) {
    HmCompBoss* this = (HmCompBoss*)thisx;
    SkelAnime_InitFlex(play, &this->skelAnime, &object_dh_Skel_007E88, &object_dh_Anim_005880, this->jointTable, this->morphTable, 16);

    HmCompBoss_SetupAction(this, play, HmCompBoss_Action_Appear);
}

void HmCompBoss_Destroy(Actor* thisx, PlayState* play) {
    HmCompBoss* this = (HmCompBoss*)thisx;
}

void HmCompBoss_Update(Actor* thisx, PlayState* play) {
    HmCompBoss* this = (HmCompBoss*)thisx;

    this->actionFunc(this, play);
}

void HmCompBoss_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    Vec3f headOffset = { 2000.0f, 1000.0f, 0.0f };
    HmCompBoss* this = (HmCompBoss*)thisx;

    if (limbIndex == 13) {
        Matrix_MultVec3f(&headOffset, &this->headPos);
        Matrix_Push();
        Matrix_Translate(headOffset.x, headOffset.y, headOffset.z, MTXMODE_APPLY);
        Collider_UpdateSpheres(1, &this->collider2);
        Matrix_Pop();
    }
}

void HmCompBoss_Draw(Actor* thisx, PlayState* play) {
    HmCompBoss* this = (HmCompBoss*)thisx;

    
    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
    
    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    POLY_OPA_DISP =
        SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                            NULL, HmCompBoss_PostLimbDraw, &this->actor, POLY_OPA_DISP);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

