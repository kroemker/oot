/*
 * File: z_prop_hand.c
 * Overlay: ovl_Prop_Hand
 * Description: A moving hand that carries link
 */

#include "z_prop_hand.h"
#include "assets/objects/object_hand/object_hand.h"

#define FLAGS (ACTOR_FLAG_4)

#define PROP_HAND_INVERTED(thisx) ((thisx)->params & 1)
#define PROP_HAND_GET_SWITCH_FLAG(thisx) (((thisx)->params >> 8) & 0x7F)

#define PROP_HAND_ACCEL 1.0f
#define PROP_HAND_SPEED 5.0f
#define PROP_MOVE_DISTANCE 500.0f

void PropHand_Init(Actor* thisx, PlayState* play);
void PropHand_Destroy(Actor* thisx, PlayState* play);
void PropHand_Update(Actor* thisx, PlayState* play);
void PropHand_Draw(Actor* thisx, PlayState* play);

void PropHand_Action_Idle(PropHand* this, PlayState* play);
void PropHand_Action_Move(PropHand* this, PlayState* play);

ActorProfile Prop_Hand_Profile = {
    /**/ ACTOR_PROP_HAND,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_HAND,
    /**/ sizeof(PropHand),
    /**/ PropHand_Init,
    /**/ PropHand_Destroy,
    /**/ PropHand_Update,
    /**/ PropHand_Draw,
};

void PropHand_SetupAction(PropHand* this, PlayState* play, PropHandActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void PropHand_Action_Idle(PropHand* this, PlayState* play) {
    if (this->moved ^ (Flags_GetSwitch(play, this->switchFlag) || this->inverted)) {
        Math_Vec3f_Copy(&this->dyna.actor.home.pos, &this->dyna.actor.world.pos);
        PropHand_SetupAction(this, play, PropHand_Action_Move);
    }
}

void PropHand_Action_Move(PropHand* this, PlayState* play) {
    f32 multiplier = this->moved ? -1.0f : 1.0f;
    
    Math_StepToF(&this->dyna.actor.speed, PROP_HAND_SPEED, PROP_HAND_ACCEL);
    
    func_8002F974(&this->dyna.actor, NA_SE_EV_ELEVATOR_MOVE - SFX_FLAG);


    this->dyna.actor.world.pos.x += multiplier * this->dyna.actor.speed * Math_SinS(this->dyna.actor.shape.rot.y);
    this->dyna.actor.world.pos.z += multiplier * this->dyna.actor.speed * Math_CosS(this->dyna.actor.shape.rot.y);

    if (Math_Vec3f_DistXZ(&this->dyna.actor.world.pos, &this->dyna.actor.home.pos) >= PROP_MOVE_DISTANCE) {
        this->moved ^= 1;
        this->dyna.actor.speed = 0.0f;
        PropHand_SetupAction(this, play, PropHand_Action_Idle);
    }
}

void PropHand_Init(Actor* thisx, PlayState* play) {
    PropHand* this = (PropHand*)thisx;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS | DYNA_TRANSFORM_ROT_Y);
    CollisionHeader_GetVirtual(&gHand_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

    this->switchFlag = PROP_HAND_GET_SWITCH_FLAG(thisx);
    this->inverted = PROP_HAND_INVERTED(thisx);
    this->dyna.actor.gravity = 0;

    if (Flags_GetSwitch(play, this->switchFlag) || this->inverted) {
        this->dyna.actor.world.pos.x += Math_SinF(this->dyna.actor.shape.rot.y) * PROP_MOVE_DISTANCE;
        this->dyna.actor.world.pos.z += Math_CosF(this->dyna.actor.shape.rot.y) * PROP_MOVE_DISTANCE;
        this->moved = 1;
    }
    else {
        this->moved = 0;
    }

    PropHand_SetupAction(this, play, PropHand_Action_Idle);
}

void PropHand_Destroy(Actor* thisx, PlayState* play) {
    PropHand* this = (PropHand*)thisx;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void PropHand_Update(Actor* thisx, PlayState* play) {
    PropHand* this = (PropHand*)thisx;

    this->actionFunc(this, play);
}

void PropHand_Draw(Actor* thisx, PlayState* play) {
    PropHand* this = (PropHand*)thisx;

    Gfx_DrawDListOpa(play, gHand);
}