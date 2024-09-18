/*
 * File: z_hm_comp_objects.c
 * Overlay: ovl_hm_comp_objects
 * Description: HM COMP Objects (Pillar, Stairs, Platform, Chess Board & Pieces)
 */

#include "z_hm_comp_objects.h"
#include "assets/objects/object_hm_comp/object_hm_comp.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

#define HMCO_GET_TYPE(thisx) ((thisx)->params & 0x7)
#define HMCO_INVERTED(thisx) (((thisx)->params >> 15) & 1)
#define HMCO_GET_SWITCH_FLAG(thisx) (((thisx)->params >> 8) & 0x7F)

#define HAND_ACCEL 1.0f
#define HAND_SPEED 5.0f
#define HAND_MOVE_DISTANCE 500.0f

#define PILLAR_MOVE_DISTANCE 1000.0f

#define CHESS_PIECE_GRAVITY -1.2f

enum HmCompObjectsType {
    HMCO_TYPE_HAND = 0,
    HMCO_TYPE_PILLAR,
    HMCO_TYPE_STAIRS,
    HMCO_TYPE_PLATFORM,
    HMCO_TYPE_CHESS_BOARD,
    HMCO_TYPE_CHESS_BISHOP,
    HMCO_TYPE_CHESS_ROOK,
    HMCO_TYPE_CHESS_KNIGHT,
};

void HmCompObjects_Init(Actor* thisx, PlayState* play);
void HmCompObjects_Destroy(Actor* thisx, PlayState* play);
void HmCompObjects_Update(Actor* thisx, PlayState* play);
void HmCompObjects_Draw(Actor* thisx, PlayState* play);

void HmCompObjects_Action_Hand_Move(HmCompObjects* this, PlayState* play);
void HmCompObjects_Action_Hand_Idle(HmCompObjects* this, PlayState* play);

void HmCompObjects_Action_Pillar_Idle(HmCompObjects* this, PlayState* play);
void HmCompObjects_Action_Pillar_Fall(HmCompObjects* this, PlayState* play);
void HmCompObjects_Action_Pillar_Shake(HmCompObjects* this, PlayState* play);


void HmCompObjects_Action_ChessPieceHeld(HmCompObjects* this, PlayState* play);
void HmCompObjects_Action_ChessPieceIdle(HmCompObjects* this, PlayState* play);

static ColliderCylinderInit sPillarColliderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x20000000, 0x00, 0x00 },
        ATELEM_NONE,
        ACELEM_ON,
        OCELEM_ON,
    },
    { 50, 400, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sBishopColliderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        ATELEM_NONE,
        ACELEM_NONE,
        OCELEM_ON,
    },
    { 20, 100, 0, { 0, 0, 0 } },
};

ActorProfile Hm_Comp_Objects_Profile = {
    /**/ ACTOR_HM_COMP_OBJECTS,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_HM_COMP,
    /**/ sizeof(HmCompObjects),
    /**/ HmCompObjects_Init,
    /**/ HmCompObjects_Destroy,
    /**/ HmCompObjects_Update,
    /**/ HmCompObjects_Draw,
};

void HmCompObjects_SetupAction(HmCompObjects* this, PlayState* play, HmCompObjectsActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

// HAND
void HmCompObjects_Action_Hand_Move(HmCompObjects* this, PlayState* play) {
    f32 multiplier = this->moved ? -1.0f : 1.0f;
    
    Math_StepToF(&this->dyna.actor.speed, HAND_SPEED, HAND_ACCEL);
    
    func_8002F974(&this->dyna.actor, NA_SE_EV_ELEVATOR_MOVE - SFX_FLAG);


    this->dyna.actor.world.pos.x += multiplier * this->dyna.actor.speed * Math_SinS(this->dyna.actor.shape.rot.y);
    this->dyna.actor.world.pos.z += multiplier * this->dyna.actor.speed * Math_CosS(this->dyna.actor.shape.rot.y);

    if (Math_Vec3f_DistXZ(&this->dyna.actor.world.pos, &this->dyna.actor.home.pos) >= HAND_MOVE_DISTANCE) {
        this->moved ^= 1;
        this->dyna.actor.speed = 0.0f;
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Hand_Idle);
    }
}

void HmCompObjects_Action_Hand_Idle(HmCompObjects* this, PlayState* play) {
    if (this->moved ^ (Flags_GetSwitch(play, this->switchFlag) || this->inverted)) {
        Math_Vec3f_Copy(&this->dyna.actor.home.pos, &this->dyna.actor.world.pos);
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Hand_Move);
    }
}

void HmCompObjects_InitHand(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS | DYNA_TRANSFORM_ROT_Y);
    CollisionHeader_GetVirtual(&gHand_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

    if (Flags_GetSwitch(play, this->switchFlag) || this->inverted) {
        this->dyna.actor.world.pos.x += Math_SinF(this->dyna.actor.shape.rot.y) * HAND_MOVE_DISTANCE;
        this->dyna.actor.world.pos.z += Math_CosF(this->dyna.actor.shape.rot.y) * HAND_MOVE_DISTANCE;
        this->moved = 1;
    }
    else {
        this->moved = 0;
    }

    HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Hand_Idle);
}

// PILLAR
void HmCompObjects_Action_Pillar_Shake(HmCompObjects* this, PlayState* play) {
    if (this->timer != 0) {
        this->timer--;
    }

    this->dyna.actor.world.pos.x = (Math_SinS(this->dyna.actor.world.rot.y + (this->timer << 0xE)) * 5.0f) + this->dyna.actor.home.pos.x;
    this->dyna.actor.world.pos.z = (Math_CosS(this->dyna.actor.world.rot.y + (this->timer << 0xE)) * 5.0f) + this->dyna.actor.home.pos.z;

    if (!(this->timer % 4)) {
        Rumble_Request(this->dyna.actor.xyzDistToPlayerSq, 180, 10, 100);
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_BLOCK_SHAKE);
    }

    if (this->timer == 0) {
        this->dyna.actor.home.pos.y -= PILLAR_MOVE_DISTANCE;

        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Pillar_Fall);
        this->dyna.actor.world.pos.x = this->dyna.actor.home.pos.x;
        this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z;
    }
}

void HmCompObjects_Action_Pillar_Fall(HmCompObjects* this, PlayState* play) {
    this->dyna.actor.velocity.y++;

    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, this->dyna.actor.velocity.y)) {
        this->dyna.actor.flags &= ~(ACTOR_FLAG_4 | ACTOR_FLAG_5);
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_BLOCK_BOUND);

        this->moved = 1;
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Pillar_Idle);
    }
}

void HmCompObjects_Action_Pillar_Idle(HmCompObjects* this, PlayState* play) {
    if (this->moved) {
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        CollisionCheck_SpawnShieldParticlesMetal(play, &this->dyna.actor.world.pos);

        this->timer = 20;
        Flags_SetSwitch(play, this->switchFlag);
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Pillar_Shake);
        OnePointCutscene_AttentionSetSfx(play, &this->dyna.actor, NA_SE_SY_CORRECT_CHIME);
    }

    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
}

void HmCompObjects_InitPillar(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS | DYNA_TRANSFORM_ROT_Y);
    CollisionHeader_GetVirtual(&gPillar_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sPillarColliderInit);

    if (Flags_GetSwitch(play, this->switchFlag)) {
        this->moved = 1;
        this->dyna.actor.world.pos.y -= PILLAR_MOVE_DISTANCE;
    }
    else {
        this->moved = 0;
    }

    HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Pillar_Idle);

    this->dyna.actor.room = -1;
}

//CHESS PIECE
void HmCompObjects_Action_ChessPieceHeld(HmCompObjects* this, PlayState* play) {
    if (Actor_HasNoParent(&this->dyna.actor, play)) {
        this->dyna.actor.room = play->roomCtx.curRoom.num;
        Actor_PlaySfx(&this->dyna.actor, NA_SE_PL_PUT_DOWN_POT);
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_ChessPieceIdle);
        Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 60.0f, 20.0f, 0.0f, UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2);
    }
}

void HmCompObjects_Action_ChessPieceIdle(HmCompObjects* this, PlayState* play) {
    if (Actor_HasParent(&this->dyna.actor, play)) {
        this->dyna.actor.room = -1;
        Actor_PlaySfx(&this->dyna.actor, NA_SE_PL_PULL_UP_POT);
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_ChessPieceHeld);
    }
    else if (this->dyna.actor.xzDistToPlayer < 100.0f) {
        Actor_OfferCarry(&this->dyna.actor, play);
    }
    
    Actor_MoveXZGravity(&this->dyna.actor);
    Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 60.0f, 20.0f, 0.0f, UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2);

    if (this->dyna.actor.xzDistToPlayer < 180.0f) {
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void HmCompObjects_InitChessPiece(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;
    CollisionHeader* colHeader = NULL;

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sBishopColliderInit);

    this->dyna.actor.flags |= ACTOR_FLAG_ALWAYS_PUT_DOWN;
    this->dyna.actor.gravity = CHESS_PIECE_GRAVITY;
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;

    HmCompObjects_SetupAction(this, play, HmCompObjects_Action_ChessPieceIdle);
}

//
void HmCompObjects_Init(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;

    PRINTF("HM COMP OBJECTS INIT params=0x%04x\n", thisx->params);

    this->type = HMCO_GET_TYPE(thisx);
    this->switchFlag = HMCO_GET_SWITCH_FLAG(thisx);
    this->inverted = HMCO_INVERTED(thisx);
    this->dyna.actor.gravity = 0;

    switch (this->type) {
    case HMCO_TYPE_HAND:
        HmCompObjects_InitHand(thisx, play);
        break;
    case HMCO_TYPE_PILLAR:
        HmCompObjects_InitPillar(thisx, play);
        break;
    case HMCO_TYPE_CHESS_BISHOP:
    case HMCO_TYPE_CHESS_ROOK:
    case HMCO_TYPE_CHESS_KNIGHT:
        HmCompObjects_InitChessPiece(thisx, play);
        break;
    }
}

void HmCompObjects_Destroy(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;

    if (this->type <= HMCO_TYPE_CHESS_BOARD) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    }

    if (this->type == HMCO_TYPE_PILLAR || this->type >= HMCO_TYPE_CHESS_BISHOP) {
        Collider_DestroyCylinder(play, &this->collider);
    }
}

void HmCompObjects_Update(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;

    this->actionFunc(this, play);
}

void HmCompObjects_Draw(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;

    if (this->type == HMCO_TYPE_HAND) {
        Gfx_DrawDListOpa(play, gHand);
    } else if (this->type == HMCO_TYPE_PILLAR) {
        Gfx_DrawDListOpa(play, gPillar);
    } else if (this->type == HMCO_TYPE_STAIRS) {
        Gfx_DrawDListOpa(play, gStairs);
    } else if (this->type == HMCO_TYPE_PLATFORM) {
        Gfx_DrawDListOpa(play, gPlatform);
    // } else if (this->type == HMCO_TYPE_CHESS_BOARD) {
    //     Gfx_DrawDListOpa(play, gBoard);
    } else if (this->type == HMCO_TYPE_CHESS_BISHOP) {
        Gfx_DrawDListOpa(play, gBishop);
    // } else if (this->type == HMCO_TYPE_CHESS_ROOK) {
    //     Gfx_DrawDListOpa(play, gRook);
    // } else if (this->type == HMCO_TYPE_CHESS_KNIGHT) {
    //     Gfx_DrawDListOpa(play, gKnight);
    }
}

