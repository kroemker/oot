/*
 * File: z_vine_spot.c
 * Overlay: Vine_Spot
 * Description: Vines created by forest arrow
 */

#include "z_vine_spot.h"

#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS 0x00000010

#define THIS ((VineSpot*)thisx)

void VineSpot_Init(Actor* thisx, PlayState* play);
void VineSpot_Destroy(Actor* thisx, PlayState* play);
void VineSpot_Update(Actor* thisx, PlayState* play);
void VineSpot_Draw(Actor* thisx, PlayState* play);

const ActorInit Vine_Spot_InitVars = {
    ACTOR_VINE_SPOT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(VineSpot),
    (ActorFunc)VineSpot_Init,
    (ActorFunc)VineSpot_Destroy,
    (ActorFunc)VineSpot_Update,
    (ActorFunc)VineSpot_Draw,
};

static Color_RGBA8 sDustPrimColor = { 36, 23, 3, 255 };
static Color_RGBA8 sDustEnvColor = { 66, 44, 11, 170 };

void VineSpot_SpawnDust(VineSpot* this, PlayState* play) {
    f32 sign[] = {-1.0f, 1.0f};
    Vec3f* vinePos;
    Vec3f dustPos;
    Vec3f dustVel;
    Vec3f dustAccel;
    Vec3f posOffset;
    f32 centerDist;
    s32 i;
    Vec3f direction;

    centerDist = this->size * 15.0f;
    vinePos = &this->dyna.actor.world.pos;
    direction.x = cosf(this->dyna.actor.world.rot.y * (M_PI / 32768.0f));
    direction.y = 0;
    direction.z = sinf(this->dyna.actor.world.rot.y * (M_PI / 32768.0f));

    for (i = 0; i < 12; i++) {
        f32 factor = Rand_ZeroOne() * sign[(int)(Rand_ZeroOne() + 0.5f)];
        Math_Vec3f_Copy(&posOffset, &direction);
        Math_Vec3f_Scale(&posOffset, centerDist);
        Math_Vec3f_Scale(&posOffset, factor);
        Math_Vec3f_Sum(&posOffset, vinePos, &dustPos);

        dustVel.x = (Rand_ZeroOne() * 3.0f) - 1.5f;
        dustVel.y = -(Rand_ZeroOne() * centerDist * 0.1f);
        dustVel.z = (Rand_ZeroOne() * 3.0f) - 1.5f;

        dustAccel.x = (Rand_ZeroOne() * 0.14f) - 0.07f;
        dustAccel.y = -(Rand_ZeroOne() * 1.1f);
        dustAccel.z = (Rand_ZeroOne() * 0.14f) - 0.07f;

        func_8002829C(play, &dustPos, &dustVel, &dustAccel, &sDustPrimColor, &sDustEnvColor, 225,
                      (Rand_ZeroOne() * 20.0f) + 20.0f);
    }
}

void VineSpot_Init(Actor* thisx, PlayState* play) {
    VineSpot* this = THIS;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&gVineSpotDL_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

    this->size = 0.1f;
    this->lifetime = 0;
    this->status = 0;
    Actor_SetScale(&this->dyna.actor, this->size);
}

void VineSpot_Destroy(Actor* thisx, PlayState* play) {
    VineSpot* this = THIS;
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void VineSpot_Update(Actor* thisx, PlayState* play) {
    VineSpot* this = THIS;
    s32 maxLifetime = this->dyna.actor.params == 0 ? 220 : this->dyna.actor.params & 0xFF;
    f32 maxSize = 5.0f;
    f32 sizeStep = 0.1f;

    Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 0, 0, 0, 0x3F);
    
    if (this->status == 0) {
        SfxSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 0x3C, NA_SE_EV_DEKU_DEATH);
        this->status = 1;
    }

    this->lifetime++;

    if (this->lifetime < 50 || this->lifetime > maxLifetime) {
        VineSpot_SpawnDust(this, play);
    }

    if (this->size < maxSize && this->lifetime < maxLifetime) {
        this->size += sizeStep;
        if (this->size >= maxSize) {
            this->size = maxSize;
        }
        Actor_SetScale(&this->dyna.actor, this->size);
    }

    if (this->lifetime >= maxLifetime) {
        if (this->size > 0.01f) {
            this->size -= 0.8f;
            this->size = this->size < 0.01f ? 0.01f : this->size;
            Actor_SetScale(&this->dyna.actor, this->size);
            VineSpot_SpawnDust(this, play);
        }
        else {
            Actor_Kill(&this->dyna.actor);
        }
    }
}

void VineSpot_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, gVineSpotDL);
}