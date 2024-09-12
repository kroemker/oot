#ifndef _Z_PROP_HAND_H_
#define _Z_PROP_HAND_H_

#include <ultra64.h>
#include <global.h>

struct PropHand;

typedef void (*PropHandActionFunc)(struct PropHand*, PlayState*);

typedef struct PropHand {
    DynaPolyActor dyna;
    PropHandActionFunc actionFunc;
    s16 switchFlag;
    u8 inverted;
    u8 moved;
} PropHand;

#endif
