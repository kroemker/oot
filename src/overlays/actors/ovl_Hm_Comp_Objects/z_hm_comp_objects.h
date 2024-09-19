#ifndef _Z_HM_COMP_OBJECTS_H_
#define _Z_HM_COMP_OBJECTS_H_

#include <ultra64.h>
#include <global.h>

struct HmCompObjects;

typedef void (*HmCompObjectsActionFunc)(struct HmCompObjects*, PlayState*);

typedef struct HmCompObjects {
    DynaPolyActor dyna;
    HmCompObjectsActionFunc actionFunc;
    s16 type;
    s16 switchFlag;
    u8 inverted;
    u8 moved;
    s16 timer;
    ColliderCylinder collider;
    s8 direction;
} HmCompObjects;

#endif
