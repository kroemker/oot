#ifndef Z_BG_MIZU_SHUTTER_H
#define Z_BG_MIZU_SHUTTER_H

#include "ultra64.h"
#include "global.h"

#define BGMIZUSHUTTER_CLEAR_ROOM_PARAM(thisx) (((u16)(thisx)->params >> 0xF) & 1)
#define BGMIZUSHUTTER_SIZE_PARAM(thisx)   (((u16)(thisx)->params >> 0xC) & 0x7)
#define BGMIZUSHUTTER_TIMER_PARAM(thisx)  (((u16)(thisx)->params >> 0x6) & 0x3F)
#define BGMIZUSHUTTER_SWITCH_PARAM(thisx) (((u16)(thisx)->params >> 0x0) & 0x3F)
#define BGMIZUSHUTTER_PARAMS(size, timer, switchFlag) (((size) << 0xC) | ((timer) << 0x6) | (switchFlag))

struct BgMizuShutter;

typedef void (*BgMizuShutterActionFunc)(struct BgMizuShutter*, PlayState*);

typedef struct BgMizuShutter {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x0164 */ BgMizuShutterActionFunc actionFunc;
    /* 0x0168 */ s32 timer;
    /* 0x016C */ s32 timerMax;
    /* 0x0170 */ Gfx* displayList;
    /* 0x0174 */ f32 maxSpeed;
    /* 0x0178 */ Vec3f closedPos;
    /* 0x0184 */ Vec3f openPos;
} BgMizuShutter; // size = 0x0190

typedef enum BgMizuShutterSize {
    BGMIZUSHUTTER_SMALL,
    BGMIZUSHUTTER_LARGE
} BgMizuShutterSize;

#endif
