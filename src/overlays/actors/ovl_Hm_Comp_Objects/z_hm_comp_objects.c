/*
 * File: z_hm_comp_objects.c
 * Overlay: ovl_hm_comp_objects
 * Description: HM COMP Objects (Pillar, Stairs, Platform, Chess Board & Pieces)
 */

#include "z_hm_comp_objects.h"
#include "assets/objects/object_hm_comp/object_hm_comp.h"
#include "assets/scenes/hm_comp/hm_comp_scene.h"

#include "../ovl_Door_Warp1/z_door_warp1.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

#define HMCO_GET_TYPE(thisx) ((thisx)->params & 0xF)
#define HMCO_INVERTED(thisx) (((thisx)->params >> 15) & 1)
#define HMCO_GET_SWITCH_FLAG(thisx) (((thisx)->params >> 8) & 0x7F)

#define HAND_ACCEL 1.0f
#define HAND_SPEED 5.0f
#define HAND_MOVE_DISTANCE 500.0f

#define PILLAR_MOVE_DISTANCE 1000.0f

#define STAIRS_MOVE_DISTANCE 1000.0f
#define STAIRS_RISE_SPEED 6.0f

#define GATE_MOVE_DISTANCE 115.0f
#define GATE_RISE_SPEED 9.0f

#define PLATFORM_MOVE_DISTANCE 500.0f
#define PLATFORM_MOVE_SPEED 5.0f

#define CHESS_PIECE_GRAVITY -1.2f

enum HmCompObjectsType {
    HMCO_TYPE_HAND = 0,
    HMCO_TYPE_PILLAR,
    HMCO_TYPE_STAIRS,
    HMCO_TYPE_PLATFORM,
    HMCO_TYPE_GATE_1,
    HMCO_TYPE_GATE_2,
    HMCO_TYPE_CHESS_BOARD_SWITCH_TRIGGER,
    HMCO_TYPE_CHESS_BOARD_ICE_TRAP,
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

void HmCompObjects_Action_Stairs_Rise(HmCompObjects* this, PlayState* play);
void HmCompObjects_Action_Stairs_Idle(HmCompObjects* this, PlayState* play);

void HmCompObjects_Action_Gate_Rise(HmCompObjects* this, PlayState* play);
void HmCompObjects_Action_Gate_Idle(HmCompObjects* this, PlayState* play);

void HmCompObjects_Action_Platform_Move(HmCompObjects* this, PlayState* play);

void HmCompObjects_Action_ChessPiecePuzzleSolved(HmCompObjects* this, PlayState* play);
void HmCompObjects_Action_ChessPieceHeld(HmCompObjects* this, PlayState* play);
void HmCompObjects_Action_ChessPieceIdle(HmCompObjects* this, PlayState* play);

void HmCompObjects_Action_ChessBoardSwitchTrigger_Idle(HmCompObjects* this, PlayState* play);

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

static ColliderCylinderInit sChessPieceColliderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_OTHER,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000001, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        ATELEM_ON,
        ACELEM_NONE,
        OCELEM_ON,
    },
    { 20, 100, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sChessBoardSwitchColliderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_OTHER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000001, 0x00, 0x00 },
        ATELEM_NONE,
        ACELEM_ON,
        OCELEM_NONE,
    },
    { 10, 10, 0, { 0, 0, 0 } },
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

    if (Math_Vec3f_DistXZ(&this->dyna.actor.world.pos, &this->dyna.actor.home.pos) <= 6.0f) {
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_BLOCK_BOUND);
        Math_Vec3f_Copy(&this->dyna.actor.world.pos, &this->dyna.actor.home.pos);
        this->moved ^= 1;
        this->dyna.actor.speed = 0.0f;
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Hand_Idle);
    }
}

void HmCompObjects_Action_Hand_Idle(HmCompObjects* this, PlayState* play) {
    if (this->moved ^ (Flags_GetSwitch(play, this->switchFlag) || this->inverted)) {
        f32 multiplier = this->moved ? -1.0f : 1.0f;
        this->dyna.actor.home.pos.x += multiplier * HAND_MOVE_DISTANCE * Math_SinS(this->dyna.actor.shape.rot.y);
        this->dyna.actor.home.pos.z += multiplier * HAND_MOVE_DISTANCE * Math_CosS(this->dyna.actor.shape.rot.y);
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
        this->dyna.actor.world.pos.x += Math_SinS(this->dyna.actor.shape.rot.y) * HAND_MOVE_DISTANCE;
        this->dyna.actor.world.pos.z += Math_CosS(this->dyna.actor.shape.rot.y) * HAND_MOVE_DISTANCE;
        Math_Vec3f_Copy(&this->dyna.actor.home.pos, &this->dyna.actor.world.pos);
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
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_STONE_BOUND);
        Actor_RequestQuakeAndRumble(&this->dyna.actor, play, 10, 10);

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
        this->dyna.actor.home.pos.y = this->dyna.actor.world.pos.y -= PILLAR_MOVE_DISTANCE;
    }
    else {
        this->moved = 0;
    }

    HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Pillar_Idle);
}

// STAIRS
void HmCompObjects_Action_Stairs_Rise(HmCompObjects* this, PlayState* play) {
    this->dyna.actor.velocity.y = CLAMP_MAX(this->dyna.actor.velocity.y + 0.3f, STAIRS_RISE_SPEED);

    func_8002F974(&this->dyna.actor, NA_SE_EV_ELEVATOR_MOVE - SFX_FLAG);

    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, this->dyna.actor.velocity.y)) {
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_BLOCK_BOUND);

        this->moved = 1;
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Stairs_Idle);
    }
}


void HmCompObjects_Action_Stairs_WaitForCsStart(HmCompObjects* this, PlayState* play) {
    if (!Play_InCsMode(play)) {
        Cutscene_SetScript(play, gBridgeCutscene);
        gSaveContext.cutsceneTrigger = 1;
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Stairs_Rise);
    }
}

void HmCompObjects_Action_Stairs_Idle(HmCompObjects* this, PlayState* play) {
    if (this->moved) {
        return;
    }

    if (Flags_GetSwitch(play, this->switchFlag)) {
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Stairs_WaitForCsStart);
    }
}

void HmCompObjects_InitStairs(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS);
    CollisionHeader_GetVirtual(&gStairs_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);
    Actor_SetScale(&this->dyna.actor, 0.1f);

    if (Flags_GetSwitch(play, this->switchFlag)) {
        this->moved = 1;
    }
    else {
        this->dyna.actor.world.pos.y -= STAIRS_MOVE_DISTANCE;
        this->moved = 0;
    }

    HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Stairs_Idle);
}

// PLATFORM
void HmCompObjects_Action_Platform_Move(HmCompObjects* this, PlayState* play) {
    if (this->timer != 0) {
        this->timer--;
        return;
    }

    this->dyna.actor.velocity.y = CLAMP_MAX(this->dyna.actor.velocity.y + 0.5f, PLATFORM_MOVE_SPEED);

    if (ABS(this->dyna.actor.world.pos.y - this->dyna.actor.home.pos.y) < 5.0f) {
        this->dyna.actor.velocity.y = 0.0f;
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
        this->direction *= -1;
        this->dyna.actor.home.pos.y += PLATFORM_MOVE_DISTANCE * this->direction;
        this->timer = 10;
    } else {
        func_8002F974(&this->dyna.actor, NA_SE_EV_ELEVATOR_MOVE3 - SFX_FLAG);
        this->dyna.actor.world.pos.y += this->direction * this->dyna.actor.velocity.y;
    }
}

void HmCompObjects_InitPlatform(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS);
    CollisionHeader_GetVirtual(&gPlatform_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

    if (this->inverted) {
        this->direction = -1;
        this->dyna.actor.home.pos.y -= PLATFORM_MOVE_DISTANCE; // move down initially if inverted
    } else {
        this->direction = 1;
        this->dyna.actor.home.pos.y += PLATFORM_MOVE_DISTANCE;
    }

    HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Platform_Move);
}

// GATE
void HmCompObjects_Action_Gate_Rise(HmCompObjects* this, PlayState* play) {
    this->dyna.actor.velocity.y = CLAMP_MAX(this->dyna.actor.velocity.y + 1.0f, GATE_RISE_SPEED);

    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, this->dyna.actor.velocity.y)) {
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Gate_Idle);
    }
}

void HmCompObjects_Action_Gate_WaitForRise(HmCompObjects* this, PlayState* play) {
    if (DECR(this->timer) == 0) {
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_METALDOOR_OPEN);
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Gate_Rise);
    }
}

void HmCompObjects_Action_Gate_Idle(HmCompObjects* this, PlayState* play) {
    if (this->moved) {
        return;
    }

    if (Flags_GetSwitch(play, this->switchFlag)) {
        this->moved = 1;
        this->timer = 55;
        this->dyna.actor.home.pos.y += GATE_MOVE_DISTANCE;
        OnePointCutscene_Attention(play, &this->dyna.actor);
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Gate_WaitForRise);
    }
}

void HmCompObjects_InitGate(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS);
    CollisionHeader_GetVirtual(&gGate_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

    if (Flags_GetSwitch(play, this->switchFlag)) {
        this->moved = 1;
        this->dyna.actor.home.pos.y = this->dyna.actor.world.pos.y += GATE_MOVE_DISTANCE;
    }
    else {
        this->moved = 0;
    }

    HmCompObjects_SetupAction(this, play, HmCompObjects_Action_Gate_Idle);
}

//CHESS BOARD
void HmCompObjects_Action_ChessBoardSwitchTrigger_PuzzleSolved(HmCompObjects* this, PlayState* play) {
}

void HmCompObjects_Action_ChessBoardSwitchTrigger_Idle(HmCompObjects* this, PlayState* play) {
    if (Flags_GetSwitch(play, this->switchFlag)) {
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_ChessBoardSwitchTrigger_PuzzleSolved);
    } else if ((this->collider.base.acFlags & AC_HIT)) {
        this->collider.base.acFlags &= ~AC_HIT;
        if ((this->collider.base.ac->id == ACTOR_HM_COMP_OBJECTS) && (HMCO_GET_TYPE(this->collider.base.ac) >= HMCO_TYPE_CHESS_BISHOP)) {
            HmCompObjects* piece = (HmCompObjects*)this->collider.base.ac;
            if (piece->actionFunc != HmCompObjects_Action_ChessPieceIdle) {
                return;
            }

            if (this->type == HMCO_TYPE_CHESS_BOARD_SWITCH_TRIGGER) {
                Flags_SetSwitch(play, this->switchFlag);
                OnePointCutscene_Init(play, 5010, 50, &this->dyna.actor, CAM_ID_MAIN);
                Sfx_PlaySfxCentered(NA_SE_SY_CORRECT_CHIME);

                piece->dyna.actor.velocity.y = 0.0f;
                Math_Vec3f_Copy(&piece->dyna.actor.home.pos, &piece->dyna.actor.world.pos);
                piece->actionFunc = HmCompObjects_Action_ChessPiecePuzzleSolved;

                Actor_Spawn(&play->actorCtx, play, ACTOR_DOOR_WARP1, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, 0, 0, 0, WARP_ORANGE + piece->type - HMCO_TYPE_CHESS_BISHOP);
            }
            else {
                Player* player = GET_PLAYER(play);
                player->iceTrapFlag = 1;
                Sfx_PlaySfxCentered(NA_SE_SY_ERROR);
                Actor_Kill(&this->dyna.actor);
            }
        }
    } else {
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }
}

void HmCompObjects_InitChessBoardSwitchTrigger(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;
    CollisionHeader* colHeader = NULL;

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sChessBoardSwitchColliderInit);
    Actor_ChangeCategory(play, &play->actorCtx, thisx, ACTORCAT_SWITCH);

    if (Flags_GetSwitch(play, this->switchFlag)) {
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_ChessBoardSwitchTrigger_PuzzleSolved);
    } else {
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_ChessBoardSwitchTrigger_Idle);
    }
}

// CHESS PIECE
Actor* HmCompObjects_GetCorrectChessSquare(HmCompObjects* this, PlayState* play) {
    s32 actorCategory;

    for (actorCategory = 0; actorCategory < ACTORCAT_MAX; actorCategory++) {
        Actor* actor = play->actorCtx.actorLists[actorCategory].head;
        while (actor != NULL) {
            if ((actor->id == ACTOR_HM_COMP_OBJECTS) && (HMCO_GET_TYPE(actor) == HMCO_TYPE_CHESS_BOARD_SWITCH_TRIGGER) && (HMCO_GET_SWITCH_FLAG(actor) == this->switchFlag)) {
                return actor;
            }
            actor = actor->next;
        }
    }

    return NULL;
}

void HmCompObjects_Action_ChessPiecePuzzleSolved(HmCompObjects* this, PlayState* play) {
    Actor* square = HmCompObjects_GetCorrectChessSquare(this, play);
    if (square != NULL) {
        s32 angleDiff;
        
        Math_StepToAngleS(&this->dyna.actor.shape.rot.y, square->shape.rot.y, 0x400);
        angleDiff = (s32)square->shape.rot.y - (s32)this->dyna.actor.shape.rot.y;
        if (ABS(angleDiff) < 0x400) {
            this->dyna.actor.shape.rot.y = square->shape.rot.y;
        }
        this->dyna.actor.world.rot.y = this->dyna.actor.shape.rot.y;

        Math_ApproachF(&this->dyna.actor.world.pos.x, square->world.pos.x, 1.0f, 2.0f);
        Math_ApproachF(&this->dyna.actor.world.pos.y, square->world.pos.y, 1.0f, 2.0f);
        Math_ApproachF(&this->dyna.actor.world.pos.z, square->world.pos.z, 1.0f, 2.0f);
    }

    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

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
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
}

void HmCompObjects_InitChessPiece(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;
    CollisionHeader* colHeader = NULL;

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sChessPieceColliderInit);
    Actor_ChangeCategory(play, &play->actorCtx, thisx, ACTORCAT_ITEMACTION);
    Actor_SetScale(&this->dyna.actor, 0.0075f);

    this->dyna.actor.flags |= ACTOR_FLAG_ALWAYS_PUT_DOWN;
    this->dyna.actor.gravity = CHESS_PIECE_GRAVITY;
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;

    if (Flags_GetSwitch(play, this->switchFlag)) {
        Actor* square = HmCompObjects_GetCorrectChessSquare(this, play);
        if (square != NULL) {
            Math_Vec3f_Copy(&this->dyna.actor.world.pos, &square->world.pos);
            Math_Vec3f_Copy(&this->dyna.actor.home.pos, &this->dyna.actor.world.pos);
            this->dyna.actor.shape.rot.y = square->shape.rot.y;
        }
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_ChessPiecePuzzleSolved);
    } else {
        HmCompObjects_SetupAction(this, play, HmCompObjects_Action_ChessPieceIdle);
    }
}

//
void HmCompObjects_Init(Actor* thisx, PlayState* play) {
    HmCompObjects* this = (HmCompObjects*)thisx;

    this->type = HMCO_GET_TYPE(thisx);
    this->switchFlag = HMCO_GET_SWITCH_FLAG(thisx);
    this->inverted = HMCO_INVERTED(thisx);
    this->dyna.actor.gravity = 0;

    PRINTF("HM COMP OBJECTS INIT params=0x%04x\n", thisx->params);
    PRINTF("HM COMP OBJECTS INIT type=%d switchFlag=%d inverted=%d\n", this->type, this->switchFlag, this->inverted);

    switch (this->type) {
    case HMCO_TYPE_HAND:
        HmCompObjects_InitHand(thisx, play);
        break;
    case HMCO_TYPE_PILLAR:
        HmCompObjects_InitPillar(thisx, play);
        break;
    case HMCO_TYPE_STAIRS:
        HmCompObjects_InitStairs(thisx, play);
        break;
    case HMCO_TYPE_GATE_1:
    case HMCO_TYPE_GATE_2:
        HmCompObjects_InitGate(thisx, play);
        break;
    case HMCO_TYPE_PLATFORM:
        HmCompObjects_InitPlatform(thisx, play);
        break;
    case HMCO_TYPE_CHESS_BOARD_SWITCH_TRIGGER:
    case HMCO_TYPE_CHESS_BOARD_ICE_TRAP:
        HmCompObjects_InitChessBoardSwitchTrigger(thisx, play);
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

    if (this->type < HMCO_TYPE_CHESS_BOARD_SWITCH_TRIGGER) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    }

    if (this->type == HMCO_TYPE_PILLAR || this->type >= HMCO_TYPE_CHESS_BOARD_SWITCH_TRIGGER) {
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
    } else if (this->type == HMCO_TYPE_GATE_1) {
        Gfx_DrawDListOpa(play, gGate1);
    } else if (this->type == HMCO_TYPE_GATE_2) {
        Gfx_DrawDListOpa(play, gGate2);
    } else if (this->type == HMCO_TYPE_CHESS_BISHOP) {
        Gfx_DrawDListOpa(play, gBishop);
    } else if (this->type == HMCO_TYPE_CHESS_ROOK) {
        Gfx_DrawDListOpa(play, gRook);
    } else if (this->type == HMCO_TYPE_CHESS_KNIGHT) {
        Gfx_DrawDListOpa(play, gKnight);
    }
}
