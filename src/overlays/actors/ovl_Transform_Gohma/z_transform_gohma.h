#ifndef _Z_TRANSFORM_GOHMA_H_
#define _Z_TRANSFORM_GOHMA_H_

#include <ultra64.h>
#include <global.h>

#include "../ovl_En_Goma/z_en_goma.h"

struct TransformGohma;

typedef void (*TransformGohmaActionFunc)(struct TransformGohma*, PlayState*);

typedef enum {
    /*  0 */ BOSSGOMA_LIMB_NONE,
    /*  1 */ BOSSGOMA_LIMB_ROOT1,
    /*  2 */ BOSSGOMA_LIMB_ROOT2,
    /*  3 */ BOSSGOMA_LIMB_BODY,
    /*  4 */ BOSSGOMA_LIMB_BODY_SHELL,
    /*  5 */ BOSSGOMA_LIMB_EYE,
    /*  6 */ BOSSGOMA_LIMB_TAIL_ROOT,
    /*  7 */ BOSSGOMA_LIMB_TAIL1_ROOT,
    /*  8 */ BOSSGOMA_LIMB_TAIL2_ROOT,
    /*  9 */ BOSSGOMA_LIMB_TAIL3_ROOT,
    /* 10 */ BOSSGOMA_LIMB_TAIL4_ROOT,
    /* 11 */ BOSSGOMA_LIMB_TAIL4,
    /* 12 */ BOSSGOMA_LIMB_TAIL3,
    /* 13 */ BOSSGOMA_LIMB_TAIL2,
    /* 14 */ BOSSGOMA_LIMB_TAIL1,
    /* 15 */ BOSSGOMA_LIMB_R_LEG_ROOT,
    /* 16 */ BOSSGOMA_LIMB_R_THIGH_ROOT,
    /* 17 */ BOSSGOMA_LIMB_R_LEG_LOWER_ROOT,
    /* 18 */ BOSSGOMA_LIMB_R_FEET_ROOT,
    /* 19 */ BOSSGOMA_LIMB_R_FEET_BACK_ROOT1,
    /* 20 */ BOSSGOMA_LIMB_R_FEET_BACK_ROOT2,
    /* 21 */ BOSSGOMA_LIMB_R_FEET_BACK,
    /* 22 */ BOSSGOMA_LIMB_R_FEET,
    /* 23 */ BOSSGOMA_LIMB_R_SHIN,
    /* 24 */ BOSSGOMA_LIMB_R_KNEE_ROOT1,
    /* 25 */ BOSSGOMA_LIMB_R_KNEE_ROOT2,
    /* 26 */ BOSSGOMA_LIMB_R_KNEE,
    /* 27 */ BOSSGOMA_LIMB_R_THIGH_SHELL_ROOT1,
    /* 28 */ BOSSGOMA_LIMB_R_THIGH_SHELL_ROOT2,
    /* 29 */ BOSSGOMA_LIMB_R_THIGH_SHELL,
    /* 30 */ BOSSGOMA_LIMB_R_THIGH,
    /* 31 */ BOSSGOMA_LIMB_EYE_LID_BOTTOM_ROOT1,
    /* 32 */ BOSSGOMA_LIMB_EYE_LID_BOTTOM_ROOT2,
    /* 33 */ BOSSGOMA_LIMB_EYE_LID_BOTTOM,
    /* 34 */ BOSSGOMA_LIMB_EYE_LID_TOP_ROOT1,
    /* 35 */ BOSSGOMA_LIMB_EYE_LID_TOP_ROOT2,
    /* 36 */ BOSSGOMA_LIMB_EYE_LID_TOP,
    /* 37 */ BOSSGOMA_LIMB_IRIS_ROOT1,
    /* 38 */ BOSSGOMA_LIMB_IRIS_ROOT2,
    /* 39 */ BOSSGOMA_LIMB_IRIS,
    /* 40 */ BOSSGOMA_LIMB_MANDIBLES_ROOT1,
    /* 41 */ BOSSGOMA_LIMB_MANDIBLES_ROOT2,
    /* 42 */ BOSSGOMA_LIMB_MANDIBLES_BODY,
    /* 43 */ BOSSGOMA_LIMB_L_MANDIBLES_ROOT,
    /* 44 */ BOSSGOMA_LIMB_L_MANDIBLES1_ROOT,
    /* 45 */ BOSSGOMA_LIMB_L_MANDIBLES2_ROOT,
    /* 46 */ BOSSGOMA_LIMB_L_MANDIBLES2,
    /* 47 */ BOSSGOMA_LIMB_L_MANDIBLES1,
    /* 48 */ BOSSGOMA_LIMB_R_MANDIBLES_ROOT,
    /* 49 */ BOSSGOMA_LIMB_R_MANDIBLES1_ROOT,
    /* 50 */ BOSSGOMA_LIMB_R_MANDIBLES2_ROOT,
    /* 51 */ BOSSGOMA_LIMB_R_MANDIBLES2,
    /* 52 */ BOSSGOMA_LIMB_R_MANDIBLES1,
    /* 53 */ BOSSGOMA_LIMB_L_ANTENNA_ROOT,
    /* 54 */ BOSSGOMA_LIMB_L_ANTENNA_BODY_ROOT,
    /* 55 */ BOSSGOMA_LIMB_L_ANTENNA_SHELL_ROOT,
    /* 56 */ BOSSGOMA_LIMB_L_ANTENNA_CLAW_ROOT,
    /* 57 */ BOSSGOMA_LIMB_L_ANTENNA_CLAW,
    /* 58 */ BOSSGOMA_LIMB_L_ANTENNA_SHELL,
    /* 59 */ BOSSGOMA_LIMB_L_ANTENNA_BODY,
    /* 60 */ BOSSGOMA_LIMB_R_ANTENNA_ROOT,
    /* 61 */ BOSSGOMA_LIMB_R_ANTENNA_BODY_ROOT,
    /* 62 */ BOSSGOMA_LIMB_R_ANTENNA_SHELL_ROOT,
    /* 63 */ BOSSGOMA_LIMB_R_ANTENNA_CLAW_ROOT,
    /* 64 */ BOSSGOMA_LIMB_R_ANTENNA_CLAW,
    /* 65 */ BOSSGOMA_LIMB_R_ANTENNA_SHELL,
    /* 66 */ BOSSGOMA_LIMB_R_ANTENNA_BODY,
    /* 67 */ BOSSGOMA_LIMB_L_LEG_ROOT,
    /* 68 */ BOSSGOMA_LIMB_L_THIGH_ROOT,
    /* 69 */ BOSSGOMA_LIMB_L_LEG_LOWER_ROOT,
    /* 70 */ BOSSGOMA_LIMB_L_FEET_ROOT,
    /* 71 */ BOSSGOMA_LIMB_L_FEET_BACK_ROOT1,
    /* 72 */ BOSSGOMA_LIMB_L_FEET_BACK_ROOT2,
    /* 73 */ BOSSGOMA_LIMB_L_FEET_BACK,
    /* 74 */ BOSSGOMA_LIMB_L_FEET,
    /* 75 */ BOSSGOMA_LIMB_L_SHIN,
    /* 76 */ BOSSGOMA_LIMB_L_KNEE_ROOT1,
    /* 77 */ BOSSGOMA_LIMB_L_KNEE_ROOT2,
    /* 78 */ BOSSGOMA_LIMB_L_KNEE,
    /* 79 */ BOSSGOMA_LIMB_L_THIGH_SHELL_ROOT1,
    /* 80 */ BOSSGOMA_LIMB_L_THIGH_SHELL_ROOT2,
    /* 81 */ BOSSGOMA_LIMB_L_THIGH_SHELL,
    /* 82 */ BOSSGOMA_LIMB_L_THIGH,
    /* 83 */ BOSSGOMA_LIMB_BODY_SHELL_BACK_ROOT1,
    /* 84 */ BOSSGOMA_LIMB_BODY_SHELL_BACK_ROOT2,
    /* 85 */ BOSSGOMA_LIMB_BODY_SHELL_BACK,
    /* 86 */ BOSSGOMA_LIMB_MAX
} TransformGohmaLimb;

typedef struct TransformGohma {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[BOSSGOMA_LIMB_MAX];
    Vec3s morphTable[BOSSGOMA_LIMB_MAX];
    TransformGohmaActionFunc actionFunc;
    s16 eyeLidBottomRotX;
    s16 eyeLidTopRotX;
    s16 eyeClosedTimer;
    s16 eyeIrisRotX;
    s16 eyeIrisRotY;
    f32 eyeIrisScaleX;
    f32 eyeIrisScaleY;
    s16 tailLimbsScaleTimers[4];
    f32 tailLimbsScale[4];
    s16 eyeState;
    s16 visualState;
    f32 mainEnvColor[3];
    f32 eyeEnvColor[3];
    Vec3f lastTailLimbWorldPos;
    Vec3f firstTailLimbWorldPos;
    Vec3f rightHandBackLimbWorldPos;
    Vec3f leftHandBackLimbWorldPos;
    ColliderJntSph collider;
    ColliderJntSphElement colliderItems[13];
    s32 invincibilityFrames;    
    Vec3f beamStartPos;
    Vec3f beamEffectPos;
    Vec3f beamHitPos;
    Vec3f beamScale;
    Vec3s beamRot;
    Vec3s beamLimbRot;
    s16 beamTexScroll;
    ColliderQuad beamCollider;
    s8 laserHit;
    s16 beamDelayTimer;
    s16 slopePitch;
    s16 slopeRoll;
} TransformGohma;

#endif
