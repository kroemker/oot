/*
 * File: z_prop_hand.c
 * Overlay: ovl_Prop_Hand
 * Description: A moving hand that carries link
 */

#include "z_prop_hand.h"

#define FLAGS (ACTOR_FLAG_4)

void PropHand_Init(Actor* thisx, PlayState* play);
void PropHand_Destroy(Actor* thisx, PlayState* play);
void PropHand_Update(Actor* thisx, PlayState* play);
void PropHand_Draw(Actor* thisx, PlayState* play);

ActorProfile Prop_Hand_Profile = {
    /**/ ACTOR_PROP_HAND,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_GAMEPLAY_KEEP,
    /**/ sizeof(PropHand),
    /**/ PropHand_Init,
    /**/ PropHand_Destroy,
    /**/ PropHand_Update,
    /**/ PropHand_Draw,
};

void PropHand_Init(Actor* thisx, PlayState* play) {
    PropHand* this = (PropHand*)thisx;
}

void PropHand_Destroy(Actor* thisx, PlayState* play) {
    PropHand* this = (PropHand*)thisx;
}

void PropHand_Update(Actor* thisx, PlayState* play) {
    PropHand* this = (PropHand*)thisx;
}

void PropHand_Draw(Actor* thisx, PlayState* play) {
    PropHand* this = (PropHand*)thisx;
}