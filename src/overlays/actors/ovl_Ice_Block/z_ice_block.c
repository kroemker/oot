/*
 * File: z_ice_block.c
 * Overlay: ovl_Ice_Block
 * Description: Ice Block. Spawned by ice arrow.
 */

#include "z_ice_block.h"

#define FLAGS 0x00000010

#define THIS ((IceBlock*)thisx)

extern Gfx gIceBlockDL[];
extern CollisionHeader gIceBlockCol_collisionHeader;

void IceBlock_Init(Actor* thisx, GlobalContext* globalCtx);
void IceBlock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void IceBlock_Update(Actor* thisx, GlobalContext* globalCtx);
void IceBlock_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Ice_Block_InitVars = {
    ACTOR_ICE_BLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(IceBlock),
    (ActorFunc)IceBlock_Init,
    (ActorFunc)IceBlock_Destroy,
    (ActorFunc)IceBlock_Update,
    (ActorFunc)IceBlock_Draw,
};

static Color_RGBA8 sDustPrimColor = { 250, 250, 250, 255 };
static Color_RGBA8 sDustEnvColor = { 180, 180, 180, 255 };

void IceBlock_SpawnDust(IceBlock* this, GlobalContext* globalCtx) {
    f32 direction[] = { -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f };
    Vec3f* icePos;
    Vec3f dustPos;
    Vec3f dustVel;
    Vec3f dustAccel;
    Vec3f posOffset;
    f32 centerDist;
    s32 i;

    centerDist = this->size * 1000.0f;

    for (i = 0; i < 4; i++) {
        icePos = &this->dyna.actor.world.pos;

        posOffset.x = ((Rand_ZeroOne() * centerDist) - centerDist * 0.5f) * direction[i * 2];
        posOffset.y = 15.0f;
        posOffset.z = ((Rand_ZeroOne() * centerDist) - centerDist * 0.5f) * direction[i * 2 + 1];

        Math_Vec3f_Sum(&posOffset, icePos, &dustPos);

        dustVel.x = (Rand_ZeroOne() * 3.0f) - 1.5f;
        dustVel.y = 0.0f;
        dustVel.z = (Rand_ZeroOne() * 3.0f) - 1.5f;

        dustAccel.x = (Rand_ZeroOne() * 0.14f) - 0.07f;
        dustAccel.y = 0.8f;
        dustAccel.z = (Rand_ZeroOne() * 0.14f) - 0.07f;

        func_8002829C(globalCtx, &dustPos, &dustVel, &dustAccel, &sDustPrimColor, &sDustEnvColor, 225,
                      (Rand_ZeroOne() * 20.0f) + 20.0f);
    }
}

void IceBlock_Init(Actor* thisx, GlobalContext* globalCtx) {
    IceBlock* this = THIS;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, 1);
    CollisionHeader_GetVirtual(&gIceBlockCol_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);

    this->size = 0.001f;
    this->lifetime = 0;
    this->status = 0;
    Actor_SetScale(&this->dyna.actor, this->size);
}

void IceBlock_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    IceBlock* this = THIS;
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void IceBlock_Update(Actor* thisx, GlobalContext* globalCtx) {
    IceBlock* this = THIS;
    s32 maxLifetime = this->dyna.actor.params & 0xFF;

    Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0, 0, 0, 0x3F);
    if (this->dyna.actor.floorPoly != 0) {
        u32 cspeed = SurfaceType_GetConveyorSpeed(&globalCtx->colCtx, this->dyna.actor.floorPoly, this->dyna.actor.floorBgId);
        u32 dir = SurfaceType_GetConveyorDirection(&globalCtx->colCtx, this->dyna.actor.floorPoly, this->dyna.actor.floorBgId);

        this->dyna.actor.world.rot.y = dir << 10;
        this->dyna.actor.speedXZ = (f32)cspeed;
        Actor_MoveForward(&this->dyna.actor);
        if (this->dyna.actor.yDistToWater < 0 && this->dyna.actor.yDistToWater > -10000.0f) {
            this->dyna.actor.world.pos.y += this->dyna.actor.yDistToWater;
        }
    }

    if (this->status == 0) {
        Audio_PlaySoundAtPosition(globalCtx, &this->dyna.actor.world.pos, 0x3C, NA_SE_EV_ICE_FREEZE);
        this->status = 1;
    }

    this->lifetime++;

    if (this->lifetime < 20 || this->lifetime > maxLifetime) {
        IceBlock_SpawnDust(this, globalCtx);
    }

    if (this->size < 0.15f && this->lifetime < maxLifetime) {
        this->size += 0.01f;
        if (this->size >= 0.15f) {
            this->size = 0.15f;
        }
        Actor_SetScale(&this->dyna.actor, this->size);
    }

    if (this->lifetime >= maxLifetime) {
        if (this->status == 1) {
            Audio_PlaySoundAtPosition(globalCtx, &this->dyna.actor.world.pos, 0x3C, NA_SE_EV_ICE_MELT);
            this->status = 2;
        }

        if (this->size > 0.0001f) {
            this->size -= 0.008f;
            this->size = this->size < 0.0001f ? 0.0001f : this->size;
            Actor_SetScale(&this->dyna.actor, this->size);
            IceBlock_SpawnDust(this, globalCtx);
        }
        else {
            Actor_Kill(&this->dyna.actor);
        }
    }
}

void IceBlock_Draw(Actor* thisx, GlobalContext* globalCtx) {
    IceBlock* this = THIS;
    Gfx_DrawDListOpa(globalCtx, gIceBlockDL);
}