#ifndef _Z_POPCORN_H_
#define _Z_POPCORN_H_

#include <ultra64.h>
#include <global.h>

struct Popcorn;

typedef void (*PopcornActionFunc)(struct Popcorn*, PlayState*);

typedef struct Popcorn {
    Actor actor;
    s16 timer;
    ColliderCylinder collider;
} Popcorn;

#endif
