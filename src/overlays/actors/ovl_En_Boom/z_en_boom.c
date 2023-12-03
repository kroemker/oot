/*
 * File: z_en_boom.c
 * Overlay: ovl_En_Boom
 * Description: Thrown Boomerang. Actor spawns when thrown and is killed when caught.
 */

#include "z_en_boom.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

void EnBoom_Init(Actor* thisx, PlayState* play);
void EnBoom_Destroy(Actor* thisx, PlayState* play);
void EnBoom_Update(Actor* thisx, PlayState* play);
void EnBoom_Draw(Actor* thisx, PlayState* play);

void EnBoom_Fly(EnBoom* this, PlayState* play);

ActorInit En_Boom_InitVars = {
    /**/ ACTOR_EN_BOOM,
    /**/ ACTORCAT_MISC,
    /**/ FLAGS,
    /**/ OBJECT_LINK_BOY,
    /**/ sizeof(EnBoom),
    /**/ EnBoom_Init,
    /**/ EnBoom_Destroy,
    /**/ EnBoom_Update,
    /**/ EnBoom_Draw,
};

static Vtx itemVertices[] = {
    VTX(486, 364, -100, 71, 2, 79, 0, 0, 255),
	VTX(-973, 375, -113, 215, 251, 79, 0, 0, 255),
	VTX(-909, 517, 2, 135, 240, 79, 0, 0, 255),
	VTX(-973, 375, 117, 215, 251, 79, 0, 0, 255),
	VTX(486, 364, 104, 71, 2, 79, 0, 0, 255),
	VTX(-909, 232, 2, 282, 240, 79, 0, 0, 255),
	VTX(486, 490, 2, 6, 2, 79, 0, 0, 255),
	VTX(486, 238, 2, 160, 40, 79, 0, 0, 255),
	VTX(486, 238, 2, 135, 2, 79, 0, 0, 255),

	VTX(1449, 1155, 7, 438, 346, 0, 120, 0, 255),
	VTX(2327, 1155, 7, 249, 178, 0, 120, 0, 255),
	VTX(1888, 1155, -428, 234, 292, 0, 120, 0, 255),

	VTX(1449, 693, 7, 372, 408, 173, 234, 173, 255),
	VTX(1449, 1155, 7, 248, 419, 172, 0, 171, 255),
	VTX(1888, 1155, -428, 243, 322, 172, 0, 171, 255),
	VTX(1888, 693, -428, 367, 311, 175, 222, 174, 255),
	VTX(2327, 1155, 7, 238, 224, 84, 0, 171, 255),
	VTX(2327, 693, 7, 362, 213, 81, 222, 174, 255),
	VTX(1888, 693, -428, 367, 311, 83, 234, 173, 255),
	VTX(1888, 1155, -428, 243, 322, 84, 0, 171, 255),
	VTX(1449, 693, 7, 372, 408, 175, 222, 82, 255),
	VTX(1888, 693, 441, 367, 311, 173, 234, 83, 255),
	VTX(1449, 1155, 7, 248, 419, 172, 0, 85, 255),
	VTX(1888, 1155, 441, 243, 322, 84, 0, 85, 255),
	VTX(2327, 693, 7, 362, 213, 83, 234, 83, 255),
	VTX(2327, 1155, 7, 238, 224, 84, 0, 85, 255),
	VTX(1888, 1155, 441, 243, 322, 172, 0, 85, 255),
	VTX(1449, 1155, 7, 438, 346, 0, 120, 0, 255),
	VTX(1888, 1155, 441, 453, 233, 0, 120, 0, 255),
	VTX(2327, 1155, 7, 249, 178, 0, 120, 0, 255),
	VTX(1888, 693, 441, 367, 311, 81, 222, 82, 255),
	VTX(1888, 210, 7, 496, 299, 185, 192, 72, 255),
	VTX(1888, 210, 7, 496, 299, 185, 192, 184, 255),
	VTX(1888, 210, 7, 496, 299, 71, 192, 184, 255),
	VTX(1888, 210, 7, 496, 299, 71, 192, 72, 255),

	VTX(2359, 154, 2, 601, 236, 253, 180, 93, 255),
	VTX(486, 364, 104, 71, 189, 252, 224, 115, 255),
	VTX(486, 238, 2, 74, 131, 253, 181, 93, 255),
	VTX(2255, 364, 172, 567, 324, 30, 25, 113, 255),
	VTX(486, 490, 2, 68, 247, 252, 76, 93, 255),
	VTX(486, 490, 2, 68, 247, 253, 75, 163, 255),
	VTX(2359, 575, 2, 590, 428, 253, 76, 163, 255),
	VTX(486, 364, -100, 71, 189, 252, 32, 141, 255),
	VTX(2359, 575, 2, 590, 428, 103, 39, 47, 255),
	VTX(2359, 154, 2, 601, 236, 102, 0, 62, 255),
	VTX(2359, 575, 2, 590, 428, 102, 0, 62, 255),
	VTX(2255, 364, 172, 567, 324, 102, 0, 62, 255),
	VTX(2255, 364, -168, 567, 324, 30, 231, 143, 255),
	VTX(2359, 154, 2, 601, 236, 102, 0, 194, 255),
	VTX(2255, 364, -168, 567, 324, 102, 0, 194, 255),
	VTX(2359, 575, 2, 590, 428, 102, 0, 194, 255),
	VTX(486, 238, 2, 74, 131, 252, 180, 163, 255),
	VTX(2359, 154, 2, 601, 236, 103, 217, 209, 255),

	VTX(1582, -584, 5, 396, 273, 221, 241, 113, 255),
	VTX(2087, -85, 231, 232, 82, 221, 8, 114, 255),
	VTX(1360, -89, 4, 270, 410, 221, 26, 111, 255),
	VTX(1688, 66, 4, 211, 274, 204, 21, 105, 255),
	VTX(1360, -89, 4, 270, 410, 221, 26, 145, 255),
	VTX(2087, -85, -223, 232, 82, 221, 8, 142, 255),
	VTX(1582, -584, 5, 396, 273, 221, 240, 143, 255),
	VTX(2087, -85, -223, 232, 82, 110, 210, 0, 255),
	VTX(2087, -85, 231, 232, 82, 116, 226, 0, 255),
	VTX(1582, -584, 5, 396, 273, 84, 171, 0, 255),
	VTX(1688, 693, 176, 74, 311, 178, 248, 91, 255),
	VTX(2087, 693, 176, 54, 131, 0, 8, 119, 255),
	VTX(1688, 693, -168, 74, 311, 151, 241, 201, 255),
	VTX(1688, 66, 4, 211, 274, 168, 16, 177, 255),
	VTX(2087, 693, -168, 54, 131, 120, 0, 0, 255),
	VTX(2087, 693, 176, 54, 131, 120, 0, 0, 255),
	VTX(1688, 693, -168, 74, 311, 0, 8, 137, 255),
	VTX(2087, 693, -168, 54, 131, 0, 8, 137, 255)
};

Gfx hammer2DL[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(0x04001A00, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR |
                         G_TX_WRAP, 3, 3, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPClearGeometryMode(G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_FOG),
    gsSPDisplayList(0x0C000000),
    gsDPSetPrimColor(0, 0, 79, 0, 0, 255),
    gsSPVertex(itemVertices, 9, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 2, 0),
    gsSP2Triangles(5, 1, 0, 0, 2, 6, 0, 0),
    gsSP2Triangles(7, 3, 5, 0, 7, 5, 0, 0),
    gsSP2Triangles(8, 4, 3, 0, 4, 6, 2, 0),
    gsSP2Triangles(3, 2, 1, 0, 3, 1, 5, 0),
    gsDPPipeSync(),
    gsSPTexture(0x07D0, 0x09C4, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(0x04000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR |
                         G_TX_WRAP, 4, 4, G_TX_NOLOD, 15),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
    gsSPSetGeometryMode(G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsDPSetPrimColor(0, 0, 155, 192, 201, 255),
    gsSPVertex(&itemVertices[9], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPVertex(&itemVertices[12], 23, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 11, 12, 13, 0),
    gsSP2Triangles(9, 14, 10, 0, 15, 16, 17, 0),
    gsSP2Triangles(12, 11, 18, 0, 9, 8, 19, 0),
    gsSP2Triangles(0, 3, 20, 0, 6, 5, 21, 0),
    gsSP1Triangle(12, 18, 22, 0),
    gsSPVertex(&itemVertices[25], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
    gsSP2Triangles(3, 4, 1, 0, 5, 6, 7, 0),
    gsSP2Triangles(3, 8, 4, 0, 9, 10, 11, 0),
    gsSP2Triangles(12, 7, 6, 0, 13, 14, 15, 0),
    gsSP2Triangles(16, 12, 17, 0, 12, 16, 7, 0),
    gsSPVertex(&itemVertices[43], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 8, 9, 0),
    gsSP2Triangles(1, 10, 3, 0, 1, 11, 10, 0),
    gsSP2Triangles(12, 13, 10, 0, 8, 14, 15, 0),
    gsSP2Triangles(8, 7, 14, 0, 5, 16, 17, 0),
    gsSP2Triangles(13, 12, 5, 0, 13, 5, 4, 0),
    gsSPEndDisplayList(),
};

Gfx gHammerRefDL[] = {
    gsSPDisplayList(hammer2DL),
    gsSPEndDisplayList(),
};

static ColliderQuadInit sQuadInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0x40000040, 0x00, 0x04 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(targetMode, 5, ICHAIN_CONTINUE),
    ICHAIN_VEC3S(shape.rot, 0, ICHAIN_STOP),
};

void EnBoom_SetupAction(EnBoom* this, EnBoomActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnBoom_Init(Actor* thisx, PlayState* play) {
    EnBoom* this = (EnBoom*)thisx;
    EffectBlureInit1 blure;

    this->actor.room = -1;

    Actor_ProcessInitChain(&this->actor, sInitChain);

    blure.p1StartColor[0] = 255;
    blure.p1StartColor[1] = 255;
    blure.p1StartColor[2] = 255;
    blure.p1StartColor[3] = 255;

    blure.p2StartColor[0] = 255;
    blure.p2StartColor[1] = 255;
    blure.p2StartColor[2] = 255;
    blure.p2StartColor[3] = 64;

    blure.p1EndColor[0] = 255;
    blure.p1EndColor[1] = 255;
    blure.p1EndColor[2] = 255;
    blure.p1EndColor[3] = 0;

    blure.p2EndColor[0] = 255;
    blure.p2EndColor[1] = 255;
    blure.p2EndColor[2] = 255;
    blure.p2EndColor[3] = 0;

    blure.elemDuration = 8;
    blure.unkFlag = 0;
    blure.calcMode = 0;

    Effect_Add(play, &this->effectIndex, EFFECT_BLURE1, 0, 0, &blure);

    Collider_InitQuad(play, &this->collider);
    Collider_SetQuad(play, &this->collider, &this->actor, &sQuadInit);

    EnBoom_SetupAction(this, EnBoom_Fly);
}

void EnBoom_Destroy(Actor* thisx, PlayState* play) {
    EnBoom* this = (EnBoom*)thisx;

    Effect_Delete(play, this->effectIndex);
    Collider_DestroyQuad(play, &this->collider);
}

void EnBoom_Fly(EnBoom* this, PlayState* play) {
    Actor* target;
    Player* player;
    s32 collided;
    s16 yawTarget;
    s16 yawDiff;
    s16 pitchTarget;
    s16 pitchDiff;
    s32 pad1;
    f32 distXYZScale;
    f32 distFromLink;
    DynaPolyActor* hitActor;
    s32 hitDynaID;
    Vec3f hitPoint;
    s32 pad2;

    player = GET_PLAYER(play);
    target = this->moveTo;

    // If the boomerang is moving toward a targeted actor, handle setting the proper x and y angle to fly toward it.
    if (target != NULL) {
        yawTarget = Actor_WorldYawTowardPoint(&this->actor, &target->focus.pos);
        yawDiff = this->actor.world.rot.y - yawTarget;

        pitchTarget = Actor_WorldPitchTowardPoint(&this->actor, &target->focus.pos);
        pitchDiff = this->actor.world.rot.x - pitchTarget;

        distXYZScale = (200.0f - Math_Vec3f_DistXYZ(&this->actor.world.pos, &target->focus.pos)) * 0.005f;
        if (distXYZScale < 0.12f) {
            distXYZScale = 0.12f;
        }

        if ((target != &player->actor) && ((target->update == NULL) || (ABS(yawDiff) > 0x4000))) {
            //! @bug  This condition is why the boomerang will randomly fly off in a the down left direction sometimes.
            //      If the actor targetted is not Link and the difference between the 2 y angles is greater than 0x4000,
            //      the moveTo pointer is nulled and it flies off in a seemingly random direction.
            this->moveTo = NULL;
        } else {
            Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, (s16)(ABS(yawDiff) * distXYZScale));
            Math_ScaledStepToS(&this->actor.world.rot.x, pitchTarget, (s16)(ABS(pitchDiff) * distXYZScale));
        }
    }

    // Set xyz speed, move forward, and play the boomerang sound effect
    Actor_SetProjectileSpeed(&this->actor, 12.0f);
    Actor_MoveXZGravity(&this->actor);
    func_8002F974(&this->actor, NA_SE_IT_BOOMERANG_FLY - SFX_FLAG);

    // If the boomerang collides with EnItem00 or a Skulltula token, set grabbed pointer to pick it up
    collided = this->collider.base.atFlags & AT_HIT;
    collided = !!(collided);
    if (collided) {
        if (((this->collider.base.at->id == ACTOR_EN_ITEM00) || (this->collider.base.at->id == ACTOR_EN_SI))) {
            this->grabbed = this->collider.base.at;
            if (this->collider.base.at->id == ACTOR_EN_SI) {
                this->collider.base.at->flags |= ACTOR_FLAG_13;
            }
        }
    }

    // Decrement the return timer and check if it's 0. If it is, check if Link can catch it and handle accordingly.
    // Otherwise handle grabbing and colliding.
    if (DECR(this->returnTimer) == 0) {
        distFromLink = Math_Vec3f_DistXYZ(&this->actor.world.pos, &player->actor.focus.pos);
        this->moveTo = &player->actor;

        // If the boomerang is less than 40 units away from Link, he can catch it.
        if (distFromLink < 40.0f) {
            target = this->grabbed;
            if (target != NULL) {
                Math_Vec3f_Copy(&target->world.pos, &player->actor.world.pos);

                // If the grabbed actor is EnItem00 (HP/Key etc) set gravity and flags so it falls in front of Link.
                // Otherwise if it's a Skulltula Token, just set flags so he collides with it to collect it.
                if (target->id == ACTOR_EN_ITEM00) {
                    target->gravity = -0.9f;
                    target->bgCheckFlags &= ~(BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH);
                } else {
                    target->flags &= ~ACTOR_FLAG_13;
                }
            }
            // Set player flags and kill the boomerang beacause Link caught it.
            player->stateFlags1 &= ~PLAYER_STATE1_25;
            Actor_Kill(&this->actor);
        }
    } else {
        collided = (this->collider.base.atFlags & AT_HIT);
        collided = (!!(collided));
        if (collided) {
            // Copy the position from the prevous frame to the boomerang to start the bounce back.
            Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.prevPos);
        } else {
            collided = BgCheck_EntityLineTest1(&play->colCtx, &this->actor.prevPos, &this->actor.world.pos, &hitPoint,
                                               &this->actor.wallPoly, true, true, true, true, &hitDynaID);

            if (collided) {
                // If the boomerang collides with something and it's is a Jabu Object actor with params equal to 0, then
                // set collided to 0 so that the boomerang will go through the wall.
                // Otherwise play a clank sound effect and keep collided set to bounce back.
                if (func_8002F9EC(play, &this->actor, this->actor.wallPoly, hitDynaID, &hitPoint) != 0 ||
                    (hitDynaID != BGCHECK_SCENE && ((hitActor = DynaPoly_GetActor(&play->colCtx, hitDynaID)) != NULL) &&
                     hitActor->actor.id == ACTOR_BG_BDAN_OBJECTS && hitActor->actor.params == 0)) {
                    collided = false;
                } else {
                    CollisionCheck_SpawnShieldParticlesMetal(play, &hitPoint);
                }
            }
        }

        // If the boomerang needs to bounce back, set x and y angle accordingly.
        // Set timer to 0 and set return actor to player so it goes back to Link.
        if (collided) {
            this->actor.world.rot.x = -this->actor.world.rot.x;
            this->actor.world.rot.y += 0x8000;
            this->moveTo = &player->actor;
            this->returnTimer = 0;
        }
    }

    // If the actor the boomerang is holding has a null update function, set grabbed to null.
    // Otherwise, copy the position from the boomerang to the actor to move it.
    target = this->grabbed;
    if (target != NULL) {
        if (target->update == NULL) {
            this->grabbed = NULL;
        } else {
            Math_Vec3f_Copy(&target->world.pos, &this->actor.world.pos);
        }
    }
}

void EnBoom_Update(Actor* thisx, PlayState* play) {
    EnBoom* this = (EnBoom*)thisx;
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags1 & PLAYER_STATE1_29)) {
        this->actionFunc(this, play);
        Actor_SetFocus(&this->actor, 0.0f);
        this->activeTimer = this->activeTimer + 1;
    }
}

void EnBoom_Draw(Actor* thisx, PlayState* play) {
    static Vec3f sMultVec1 = { -960.0f, 0.0f, 0.0f };
    static Vec3f sMultVec2 = { 960.0f, 0.0f, 0.0f };
    EnBoom* this = (EnBoom*)thisx;
    Vec3f vec1;
    Vec3f vec2;

    OPEN_DISPS(play->state.gfxCtx, "../z_en_boom.c", 567);

    Matrix_RotateY(BINANG_TO_RAD(this->actor.world.rot.y), MTXMODE_APPLY);
    Matrix_RotateZ(BINANG_TO_RAD(this->actor.world.rot.z), MTXMODE_APPLY);
    Matrix_RotateX(BINANG_TO_RAD(0x4000), MTXMODE_APPLY);
    Matrix_MultVec3f(&sMultVec1, &vec1);
    Matrix_MultVec3f(&sMultVec2, &vec2);

    if (func_80090480(play, &this->collider, &this->boomerangInfo, &vec1, &vec2)) {
        EffectBlure_AddVertex(Effect_GetByIndex(this->effectIndex), &vec1, &vec2);
    }

    Gfx_SetupDL_25Opa(play->state.gfxCtx);
    Matrix_RotateZ(BINANG_TO_RAD(this->activeTimer * 12000), MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, "../z_en_boom.c", 601),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gHammerRefDL);

    CLOSE_DISPS(play->state.gfxCtx, "../z_en_boom.c", 604);
}
