/*
 * File: z_popcorn.c
 * Overlay: ovl_Popcorn
 * Description: Popcorn projectile from octorok
 */

#include "z_popcorn.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_4)

void Popcorn_Init(Actor* thisx, PlayState* play);
void Popcorn_Destroy(Actor* thisx, PlayState* play);
void Popcorn_Update(Actor* thisx, PlayState* play);
void Popcorn_Draw(Actor* thisx, PlayState* play);

ActorProfile Popcorn_Profile = {
    /**/ ACTOR_POPCORN,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_GAMEPLAY_KEEP,
    /**/ sizeof(Popcorn),
    /**/ Popcorn_Init,
    /**/ Popcorn_Destroy,
    /**/ Popcorn_Update,
    /**/ Popcorn_Draw,
};

static ColliderCylinderInit sPopcornColliderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xFFCFFFFF, 0x00, 0x08 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        ATELEM_ON | ATELEM_SFX_HARD,
        ACELEM_ON,
        OCELEM_ON,
    },
    { 13, 20, 0, { 0, 0, 0 } },
};

void Popcorn_Init(Actor* thisx, PlayState* play) {
    Popcorn* this = (Popcorn*)thisx;

    ActorShape_Init(&thisx->shape, 1100.0f, ActorShadow_DrawCircle, 18.0f);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, thisx, &sPopcornColliderInit);
    this->timer = 30;
    thisx->shape.rot.y = 0;
    thisx->speed = 15.0f;
}

void Popcorn_Destroy(Actor* thisx, PlayState* play) {
    Popcorn* this = (Popcorn*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

void Popcorn_Update(Actor* thisx, PlayState* play) {
    Popcorn* this = (Popcorn*)thisx;
    Vec3f effectPos;
    Vec3f prevPos;
    s32 canRestorePrevPos;

    canRestorePrevPos = false;
    Actor_MoveXZGravity(&this->actor);
    Math_Vec3f_Copy(&prevPos, &this->actor.world.pos);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 15.0f, 30.0f,
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2);
    if ((this->actor.bgCheckFlags & BGCHECKFLAG_WALL) &&
        SurfaceType_IsIgnoredByProjectiles(&play->colCtx, this->actor.wallPoly, this->actor.wallBgId)) {
        canRestorePrevPos = true;
        this->actor.bgCheckFlags &= ~BGCHECKFLAG_WALL;
    }
    if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) &&
        SurfaceType_IsIgnoredByProjectiles(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
        canRestorePrevPos = true;
        this->actor.bgCheckFlags &= ~BGCHECKFLAG_GROUND;
    }
    if (canRestorePrevPos && !(this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_WALL))) {
        Math_Vec3f_Copy(&this->actor.world.pos, &prevPos);
    }

    this->timer--;
    if (this->timer == 0) {
        this->actor.gravity = -1.0f;
    }
    this->actor.home.rot.z += 0x1554;
    if ((this->actor.bgCheckFlags & BGCHECKFLAG_WALL) || (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) ||
        (this->collider.base.atFlags & AT_HIT) || this->collider.base.acFlags & AC_HIT ||
        this->collider.base.ocFlags1 & OC1_HIT || this->actor.floorHeight == BGCHECK_Y_MIN) {
        PRINTF("Popcorn hit\n");
        effectPos.x = this->actor.world.pos.x;
        effectPos.y = this->actor.world.pos.y + 11.0f;
        effectPos.z = this->actor.world.pos.z;
        EffectSsHahen_SpawnBurst(play, &effectPos, 6.0f, 0, 1, 2, 15, 7, 10, gPopcornDL);
        SfxSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 20, NA_SE_EN_OCTAROCK_ROCK);
        Actor_Kill(&this->actor);
    } else if (this->timer == -300) {
        Actor_Kill(&this->actor);
    }

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);

    Actor_SetFocus(&this->actor, 15.0f);
}

void Popcorn_Draw(Actor* thisx, PlayState* play) {
    Popcorn* this = (Popcorn*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
    Matrix_RotateZ(BINANG_TO_RAD(this->actor.home.rot.z), MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, MATRIX_NEW(play->state.gfxCtx, __FILE__, __LINE__),
                G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gPopcornDL);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

