#ifndef _Z_HM_COMP_BOSS_H_
#define _Z_HM_COMP_BOSS_H_

#include <ultra64.h>
#include <global.h>

struct HmCompBoss;

typedef void (*HmCompBossActionFunc)(struct HmCompBoss*, PlayState*);

typedef struct HmCompBoss {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[16];
    Vec3s morphTable[16];
    HmCompBossActionFunc actionFunc;
    s16 timer;
    ColliderCylinder collider1;
    ColliderJntSph collider2;
    ColliderJntSphElement elements[1];
    Vec3f headPos;
} HmCompBoss;

#endif
