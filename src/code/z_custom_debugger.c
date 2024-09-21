#include "global.h"

enum CustomDebuggerPage {
    PAGE_MAIN,
    PAGE_ACTORS,
};

s8 sDebuggerShow = 0;
s8 sDebuggerPage = PAGE_ACTORS;
s8 sDebuggerIndex = 0;
s16 sDebuggerTimer = 0;
s16 sDebuggerActorOffset = 0;
s16 sDebuggerActorCount = 0;
s16 sDebuggerMaxActors = 8;
Actor* sDebuggerSelectedActor = NULL;

void CustomDebugger_DrawActorPage(PlayState* play, GfxPrint* gfxPrinter) {
    s32 line = 0;
    s32 category = 0;

    sDebuggerActorCount = 0;

    GfxPrint_SetColor(gfxPrinter, 250, 250, 50, 255);
    GfxPrint_SetPos(gfxPrinter, 4, 8);
    GfxPrint_Printf(gfxPrinter, "%-15s %-3s %-4s %-8s", "Name", "Id", "Para", "Address");
    for (; category < ACTORCAT_MAX; category++) {
        Actor* actor = play->actorCtx.actorLists[category].head;
        while (actor != NULL) {
            sDebuggerActorCount++;
            if (sDebuggerActorCount > sDebuggerActorOffset + sDebuggerMaxActors) {
                actor = actor->next;
                continue;
            }
            if (sDebuggerActorCount - 1 < sDebuggerActorOffset) {
                actor = actor->next;
                continue;
            }
            if (sDebuggerActorCount - 1 == sDebuggerIndex) {
                GfxPrint_SetColor(gfxPrinter, 250, 250, 50, 255);
                sDebuggerSelectedActor = actor;
            } else {
                GfxPrint_SetColor(gfxPrinter, 200, 200, 200, 255);
            }

            GfxPrint_SetPos(gfxPrinter, 4, 10 + line * 2);
            GfxPrint_Printf(gfxPrinter, "%-15s %03X %04X %08X", actor->overlayEntry->name, actor->id, actor->params & 0xFFFF, actor);
            line++;
            actor = actor->next;
        }
    }
}

void CustomDebugger_Draw(PlayState* play) {
    Gfx* gfx;
    Gfx* polyOpa;
    GfxPrint printer;
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    if (!sDebuggerShow || !OOT_DEBUG) {
        return;
    }

    OPEN_DISPS(gfxCtx, __FILE__, __LINE__);

    polyOpa = POLY_OPA_DISP;
    gfx = Gfx_Open(polyOpa);
    gSPDisplayList(OVERLAY_DISP++, gfx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);

    CustomDebugger_DrawActorPage(play, &printer);

    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    Gfx_Close(polyOpa, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx, __FILE__, __LINE__);
}

void CustomDebugger_Update(PlayState* play) {
    Input* input = &play->state.input[0];

    if (!OOT_DEBUG || (sDebuggerTimer > 0)) {
        sDebuggerTimer--;
        return;
    }

    if (CHECK_BTN_ALL(input->cur.button, BTN_L | BTN_DUP)) {
        sDebuggerShow = !sDebuggerShow;
        sDebuggerTimer = 15;
    }

    if (!sDebuggerShow) {
        return;
    }

    if (CHECK_BTN_ALL(input->cur.button, BTN_DUP)) {
        sDebuggerIndex = CLAMP_MIN(sDebuggerIndex - 1, 0);
        sDebuggerTimer = 2;
        if (sDebuggerIndex < sDebuggerActorOffset) {
            sDebuggerActorOffset = sDebuggerIndex;
        }
    }

    if (CHECK_BTN_ALL(input->cur.button, BTN_DDOWN)) {
        sDebuggerIndex = CLAMP_MAX(sDebuggerIndex + 1, sDebuggerActorCount - 1);
        sDebuggerTimer = 2;
        if (sDebuggerIndex >= sDebuggerActorOffset + sDebuggerMaxActors) {
            sDebuggerActorOffset = sDebuggerIndex - sDebuggerMaxActors + 1;
        }
    }

    if (CHECK_BTN_ALL(input->cur.button, BTN_R) && (sDebuggerSelectedActor != NULL)) {
        GET_ACTIVE_CAM(play)->player = (Player*) sDebuggerSelectedActor;
        sDebuggerTimer = 2;
    } else if (CHECK_BTN_ALL(input->cur.button, BTN_L)) {
        GET_ACTIVE_CAM(play)->player = GET_PLAYER(play);
        sDebuggerTimer = 2;
    }
}