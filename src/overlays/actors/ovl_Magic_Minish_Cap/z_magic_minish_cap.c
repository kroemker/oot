/*
 * File: z_magic_minish_cap.c
 * Overlay: ovl_Magic_Minish_Cap
 * Description: Minish Cap
 */

#include "z_magic_minish_cap.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS 0x02000010

#define THIS ((MagicMinishCap*)thisx)

void MagicMinishCap_Init(Actor* thisx, GlobalContext* globalCtx);
void MagicMinishCap_Destroy(Actor* thisx, GlobalContext* globalCtx);
void MagicMinishCap_Update(Actor* thisx, GlobalContext* globalCtx);
void MagicMinishCap_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Magic_Minish_Cap_InitVars = {
    ACTOR_UNSET_128,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(MagicMinishCap),
    (ActorFunc)MagicMinishCap_Init,
    (ActorFunc)MagicMinishCap_Destroy,
    (ActorFunc)MagicMinishCap_Update,
    (ActorFunc)MagicMinishCap_Draw,
};

void MagicMinishCap_Init(Actor* thisx, GlobalContext* globalCtx) {
    MagicMinishCap* this = THIS;
}

void MagicMinishCap_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    MagicMinishCap* this = THIS;
}

void MagicMinishCap_Update(Actor* thisx, GlobalContext* globalCtx) {
    MagicMinishCap* this = THIS;

    this->timer++;
}

void MagicMinishCap_Draw(Actor* thisx, GlobalContext* globalCtx) {
    MagicMinishCap* this = THIS;
}