/*
 * File: z_select.c
 * Overlay: ovl_select
 * Description: Debug Scene Select Menu
 */

#include "ultra64.h"
#include "global.h"
#include "terminal.h"
#include "alloca.h"

void MapSelect_LoadTitle(MapSelectState* this) {
    this->state.running = false;
    SET_NEXT_GAMESTATE(&this->state, ConsoleLogo_Init, ConsoleLogoState);
}

void MapSelect_LoadGame(MapSelectState* this, s32 entranceIndex) {
    PRINTF(VT_FGCOL(BLUE));
    PRINTF("\n\n\nＦＩＬＥ＿ＮＯ＝%x\n\n\n", gSaveContext.fileNum);
    PRINTF(VT_RST);
    if (gSaveContext.fileNum == 0xFF) {
        Sram_InitDebugSave();
        // Set the fill target to be the saved magic amount
        gSaveContext.magicFillTarget = gSaveContext.save.info.playerData.magic;
        // Set `magicLevel` and `magic` to 0 so `magicCapacity` then `magic` grows from nothing
        // to respectively the full capacity and `magicFillTarget`
        gSaveContext.magicCapacity = 0;
        gSaveContext.save.info.playerData.magicLevel = gSaveContext.save.info.playerData.magic = 0;
    }
    gSaveContext.buttonStatus[0] = gSaveContext.buttonStatus[1] = gSaveContext.buttonStatus[2] =
        gSaveContext.buttonStatus[3] = gSaveContext.buttonStatus[4] = BTN_ENABLED;
    gSaveContext.forceRisingButtonAlphas = gSaveContext.nextHudVisibilityMode = gSaveContext.hudVisibilityMode =
        gSaveContext.hudVisibilityModeTimer = 0; // false, HUD_VISIBILITY_NO_CHANGE
    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0);
    gSaveContext.save.entranceIndex = entranceIndex;
    gSaveContext.respawnFlag = 0;
    gSaveContext.respawn[RESPAWN_MODE_DOWN].entranceIndex = ENTR_LOAD_OPENING;
    gSaveContext.seqId = (u8)NA_BGM_DISABLED;
    gSaveContext.natureAmbienceId = 0xFF;
    gSaveContext.showTitleCard = true;
    gWeatherMode = WEATHER_MODE_CLEAR;

    this->state.running = false;
    SET_NEXT_GAMESTATE(&this->state, Play_Init, PlayState);
}

// "Translation" (Actual name)
static SceneSelectEntry sScenes[] = {
    { "  1:Hyrule Field", MapSelect_LoadGame, ENTR_HYRULE_FIELD_0 },
    { "  2:Kakariko Village", MapSelect_LoadGame, ENTR_KAKARIKO_VILLAGE_0 },
    { "  3:Graveyard", MapSelect_LoadGame, ENTR_GRAVEYARD_0 },
    { "  4:Zora's River", MapSelect_LoadGame, ENTR_ZORAS_RIVER_0 },
    { "  5:Kokiri Forest", MapSelect_LoadGame, ENTR_KOKIRI_FOREST_0 },
    { "  6:Sacred Forest Meadow", MapSelect_LoadGame, ENTR_SACRED_FOREST_MEADOW_0 },
    { "  7:Lake Hylia", MapSelect_LoadGame, ENTR_LAKE_HYLIA_0 },
    { "  8:Zora's Domain", MapSelect_LoadGame, ENTR_ZORAS_DOMAIN_0 },
    { "  9:Zora's Fountain", MapSelect_LoadGame, ENTR_ZORAS_FOUNTAIN_0 },
    { " 10:Gerudo Valley", MapSelect_LoadGame, ENTR_GERUDO_VALLEY_0 },
    { " 11:Lost Woods", MapSelect_LoadGame, ENTR_LOST_WOODS_0 },
    { " 12:Desert Colossus", MapSelect_LoadGame, ENTR_DESERT_COLOSSUS_0 },
    { " 13:Gerudo's Fortress", MapSelect_LoadGame, ENTR_GERUDOS_FORTRESS_0 },
    { " 14:Haunted Wasteland", MapSelect_LoadGame, ENTR_HAUNTED_WASTELAND_0 },
    { " 15:Hyrule Castle", MapSelect_LoadGame, ENTR_HYRULE_CASTLE_0 },
    { " 16:Death Mountain Trail", MapSelect_LoadGame, ENTR_DEATH_MOUNTAIN_TRAIL_0 },
    { " 17:Death Mountain Crater", MapSelect_LoadGame, ENTR_DEATH_MOUNTAIN_CRATER_0 },
    { " 18:Goron City", MapSelect_LoadGame, ENTR_GORON_CITY_0 },
    { " 19:Lon Lon Ranch", MapSelect_LoadGame, ENTR_LON_LON_RANCH_0 },
    { " 20:Temple Of Time", MapSelect_LoadGame, ENTR_TEMPLE_OF_TIME_0 },
    { " 21:Chamber of Sages", MapSelect_LoadGame, ENTR_CHAMBER_OF_THE_SAGES_0 },
    { " 22:Shooting Gallery", MapSelect_LoadGame, ENTR_SHOOTING_GALLERY_0 },
    { " 23:Castle Courtyard Game", MapSelect_LoadGame, ENTR_CASTLE_COURTYARD_GUARDS_DAY_0 },
    { " 24:Heart Piece Grave", MapSelect_LoadGame, ENTR_REDEAD_GRAVE_0 },
    { " 25:Hylian Shield Grave", MapSelect_LoadGame, ENTR_GRAVE_WITH_FAIRYS_FOUNTAIN_0 },
    { " 26:Royal Family's Tomb", MapSelect_LoadGame, ENTR_ROYAL_FAMILYS_TOMB_0 },
    { " 27:Great Fairy's Fountain (Din)", MapSelect_LoadGame, ENTR_GREAT_FAIRYS_FOUNTAIN_MAGIC_0 },
    { " 28:Great Fairy's Fountain (Farore)", MapSelect_LoadGame, ENTR_FAIRYS_FOUNTAIN_0 },
    { " 29:Great Fairy's Fountain (Nayru)", MapSelect_LoadGame, ENTR_GREAT_FAIRYS_FOUNTAIN_SPELLS_0 },
    { " 30:Ganon's Tower - Collapsing", MapSelect_LoadGame, ENTR_GANONS_TOWER_COLLAPSE_EXTERIOR_0 },
    { " 31:Castle Courtyard", MapSelect_LoadGame, ENTR_CASTLE_COURTYARD_ZELDA_0 },
    { " 32:Fishing Pond", MapSelect_LoadGame, ENTR_FISHING_POND_0 },
    { " 33:Bombchu Bowling Alley", MapSelect_LoadGame, ENTR_BOMBCHU_BOWLING_ALLEY_0 },
    { " 34:Lon Lon Ranch House", MapSelect_LoadGame, ENTR_LON_LON_BUILDINGS_0 },
    { " 35:Lon Lon Ranch Silo", MapSelect_LoadGame, ENTR_LON_LON_BUILDINGS_1 },
    { " 36:Lots O' Pots", MapSelect_LoadGame, ENTR_MARKET_GUARD_HOUSE_0 },
    { " 37:Potion Shop", MapSelect_LoadGame, ENTR_POTION_SHOP_GRANNY_0 },
    { " 38:Treasure Chest Game", MapSelect_LoadGame, ENTR_TREASURE_BOX_SHOP_0 },
    { " 39:House Of Skulltula", MapSelect_LoadGame, ENTR_HOUSE_OF_SKULLTULA_0 },
    { " 40:Market Entrance", MapSelect_LoadGame, ENTR_MARKET_ENTRANCE_DAY_0 },
    { " 41:Market", MapSelect_LoadGame, ENTR_MARKET_DAY_0 },
    { " 42:Back Alley", MapSelect_LoadGame, ENTR_BACK_ALLEY_DAY_0 },
    { " 43:Temple of Time Exterior", MapSelect_LoadGame, ENTR_TEMPLE_OF_TIME_EXTERIOR_DAY_0 },
    { " 44:Link's House", MapSelect_LoadGame, ENTR_LINKS_HOUSE_0 },
    { " 45:Kakariko House 1", MapSelect_LoadGame, ENTR_KAKARIKO_CENTER_GUEST_HOUSE_0 },
    { " 46:Back Alley House 1", MapSelect_LoadGame, ENTR_BACK_ALLEY_HOUSE_0 },
    { " 47:House of Know-it-All Brothers", MapSelect_LoadGame, ENTR_KNOW_IT_ALL_BROS_HOUSE_0 },
    { " 48:House of Twins", MapSelect_LoadGame, ENTR_TWINS_HOUSE_0 },
    { " 49:Mido's House", MapSelect_LoadGame, ENTR_MIDOS_HOUSE_0 },
    { " 50:Saria's House", MapSelect_LoadGame, ENTR_SARIAS_HOUSE_0 },
    { " 51:Stable", MapSelect_LoadGame, ENTR_STABLE_0 },
    { " 52:Grave Keeper's Hut", MapSelect_LoadGame, ENTR_GRAVEKEEPERS_HUT_0 },
    { " 53:Dog Lady's House", MapSelect_LoadGame, ENTR_DOG_LADY_HOUSE_0 },
    { " 54:Impa's House", MapSelect_LoadGame, ENTR_IMPAS_HOUSE_0 },
    { " 55:Lakeside Laboratory", MapSelect_LoadGame, ENTR_LAKESIDE_LABORATORY_0 },
    { " 56:Running Man's Tent", MapSelect_LoadGame, ENTR_CARPENTERS_TENT_0 },
    { " 57:Bazaar", MapSelect_LoadGame, ENTR_BAZAAR_0 },
    { " 58:Kokiri Shop", MapSelect_LoadGame, ENTR_KOKIRI_SHOP_0 },
    { " 59:Goron Shop", MapSelect_LoadGame, ENTR_GORON_SHOP_0 },
    { " 60:Zora Shop", MapSelect_LoadGame, ENTR_ZORA_SHOP_0 },
    { " 61:Kakariko Potion Shop", MapSelect_LoadGame, ENTR_POTION_SHOP_KAKARIKO_0 },
    { " 62:Potion Shop", MapSelect_LoadGame, ENTR_POTION_SHOP_MARKET_0 },
    { " 63:Bombchu Shop ", MapSelect_LoadGame, ENTR_BOMBCHU_SHOP_0 },
    { " 64:Happy Mask Shop", MapSelect_LoadGame, ENTR_HAPPY_MASK_SHOP_0 },
    { " 65:Gerudo Training Ground", MapSelect_LoadGame, ENTR_GERUDO_TRAINING_GROUND_0 },
    { " 66:Inside the Deku Tree", MapSelect_LoadGame, ENTR_DEKU_TREE_0 },
    { " 67:Gohma's Lair", MapSelect_LoadGame, ENTR_DEKU_TREE_BOSS_0 },
    { " 68:Dodongo's Cavern", MapSelect_LoadGame, ENTR_DODONGOS_CAVERN_0 },
    { " 69:King Dodongo's Lair", MapSelect_LoadGame, ENTR_DODONGOS_CAVERN_BOSS_0 },
    { " 70:Inside Jabu-Jabu's Belly", MapSelect_LoadGame, ENTR_JABU_JABU_0 },
    { " 71:Barinade's Lair", MapSelect_LoadGame, ENTR_JABU_JABU_BOSS_0 },
    { " 72:Forest Temple", MapSelect_LoadGame, ENTR_FOREST_TEMPLE_0 },
    { " 73:Phantom Ganon's Lair", MapSelect_LoadGame, ENTR_FOREST_TEMPLE_BOSS_0 },
    { " 74:Bottom of the Well", MapSelect_LoadGame, ENTR_BOTTOM_OF_THE_WELL_0 },
    { " 75:Shadow Temple", MapSelect_LoadGame, ENTR_SHADOW_TEMPLE_0 },
    { " 76:Bongo Bongo's Lair", MapSelect_LoadGame, ENTR_SHADOW_TEMPLE_BOSS_0 },
    { " 77:Fire Temple", MapSelect_LoadGame, ENTR_FIRE_TEMPLE_0 },
    { " 78:Volvagia's Lair", MapSelect_LoadGame, ENTR_FIRE_TEMPLE_BOSS_0 },
    { " 79:Water Temple", MapSelect_LoadGame, ENTR_WATER_TEMPLE_0 },
    { " 80:Morpha's Lair", MapSelect_LoadGame, ENTR_WATER_TEMPLE_BOSS_0 },
    { " 81:Spirit Temple", MapSelect_LoadGame, ENTR_SPIRIT_TEMPLE_0 },
    { " 82:Iron Knuckle's Lair", MapSelect_LoadGame, ENTR_SPIRIT_TEMPLE_BOSS_0 },
    { " 83:Twinrova's Lair", MapSelect_LoadGame, ENTR_SPIRIT_TEMPLE_BOSS_2 },
    { " 84:Ganon's Tower", MapSelect_LoadGame, ENTR_GANONS_TOWER_0 },
    { " 85:Ganondorf's Lair", MapSelect_LoadGame, ENTR_GANONDORF_BOSS_0 },
    { " 86:Ice Cavern", MapSelect_LoadGame, ENTR_ICE_CAVERN_0 },
    { " 87:Dampe's Grave (Windmill)", MapSelect_LoadGame, ENTR_WINDMILL_AND_DAMPES_GRAVE_0 },
    { " 88:Inside Ganon's Castle", MapSelect_LoadGame, ENTR_INSIDE_GANONS_CASTLE_0 },
    { " 89:Ganon's Lair", MapSelect_LoadGame, ENTR_GANON_BOSS_0 },
    { " 90:Escaping Ganon's Castle 1", MapSelect_LoadGame, ENTR_GANONS_TOWER_COLLAPSE_INTERIOR_0 },
    { " 91:Escaping Ganon's Castle 2", MapSelect_LoadGame, ENTR_GANONS_TOWER_COLLAPSE_INTERIOR_2 },
    { " 92:Escaping Ganon's Castle 3", MapSelect_LoadGame, ENTR_GANONS_TOWER_COLLAPSE_INTERIOR_4 },
    { " 93:Escaping Ganon's Castle 4", MapSelect_LoadGame, ENTR_GANONS_TOWER_COLLAPSE_INTERIOR_6 },
    { " 94:Escaping Ganon's Castle 5", MapSelect_LoadGame, ENTR_INSIDE_GANONS_CASTLE_COLLAPSE_0 },
    { " 95:Thieves' Hideout 1-2", MapSelect_LoadGame, ENTR_THIEVES_HIDEOUT_0 },
    { " 96:Thieves' Hideout 3-4 9-10", MapSelect_LoadGame, ENTR_THIEVES_HIDEOUT_2 },
    { " 97:Thieves' Hideout 5-6", MapSelect_LoadGame, ENTR_THIEVES_HIDEOUT_4 },
    { " 98:Thieves' Hideout 7-8", MapSelect_LoadGame, ENTR_THIEVES_HIDEOUT_6 },
    { " 99:Thieves' Hideout 11-12", MapSelect_LoadGame, ENTR_THIEVES_HIDEOUT_10 },
    { "100:Thieves' Hideout 13", MapSelect_LoadGame, ENTR_THIEVES_HIDEOUT_12 },
    { "101:Generic Grotto", MapSelect_LoadGame, ENTR_GROTTOS_0 },
    { "102:Grotto 1", MapSelect_LoadGame, ENTR_GROTTOS_1 },
    { "103:Heart Piece Scrub Grotto", MapSelect_LoadGame, ENTR_GROTTOS_2 },
    { "104:Kakariko Redead Grotto", MapSelect_LoadGame, ENTR_GROTTOS_3 },
    { "105:Grotto 4", MapSelect_LoadGame, ENTR_GROTTOS_4 },
    { "106:Hyrule Field Cow Grotto", MapSelect_LoadGame, ENTR_GROTTOS_5 },
    { "107:Octorock Grotto", MapSelect_LoadGame, ENTR_GROTTOS_6 },
    { "108:Grotto 7", MapSelect_LoadGame, ENTR_GROTTOS_7 },
    { "109:Wolfos Grotto", MapSelect_LoadGame, ENTR_GROTTOS_8 },
    { "110:Grotto 9", MapSelect_LoadGame, ENTR_GROTTOS_9 },
    { "111:Grotto 10", MapSelect_LoadGame, ENTR_GROTTOS_10 },
    { "112:Tektite Grotto", MapSelect_LoadGame, ENTR_GROTTOS_11 },
    { "113:Deku Theater Grotto", MapSelect_LoadGame, ENTR_GROTTOS_12 },
    { "114:Death Mountain Trail Cow Grotto", MapSelect_LoadGame, ENTR_GROTTOS_13 },
    { "115:Cutscene Map", MapSelect_LoadGame, ENTR_CUTSCENE_MAP_0 },
#if OOT_DEBUG
    { "116:Test Room", MapSelect_LoadGame, ENTR_BESITU_0 },
    { "117:SRD Map", MapSelect_LoadGame, ENTR_SASATEST_0 },
    { "118:Test Map", MapSelect_LoadGame, ENTR_TEST01_0 },
    { "119:Treasure Chest Warp", MapSelect_LoadGame, ENTR_TESTROOM_0 },
    { "120:Stalfos Miniboss Room", MapSelect_LoadGame, ENTR_SYOTES_0 },
    { "121:Stalfos Boss Room", MapSelect_LoadGame, ENTR_SYOTES2_0 },
    { "122:Dark Link Room", MapSelect_LoadGame, ENTR_SUTARU_0 },
    { "123:Shooting Gallery Duplicate", MapSelect_LoadGame, ENTR_TEST_SHOOTING_GALLERY_0 },
    { "124:Depth Test", MapSelect_LoadGame, ENTR_DEPTH_TEST_0 },
    { "125:Hyrule Garden Game (Broken)", MapSelect_LoadGame, ENTR_HAIRAL_NIWA2_0 },
#endif
    { "126:Title Screen", (void*)MapSelect_LoadTitle, 0 },
};

void MapSelect_UpdateMenu(MapSelectState* this) {
    Input* input = &this->state.input[0];
    s32 pad;
    SceneSelectEntry* selectedScene;

    if (this->verticalInputAccumulator == 0) {
        if (CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_START)) {
            selectedScene = &this->scenes[this->currentScene];
            if (selectedScene->loadFunc != NULL) {
                selectedScene->loadFunc(this, selectedScene->entranceIndex);
            }
        }

        if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
            if (LINK_AGE_IN_YEARS == YEARS_ADULT) {
                gSaveContext.save.linkAge = LINK_AGE_CHILD;
            } else {
                gSaveContext.save.linkAge = LINK_AGE_ADULT;
            }
        }

        if (CHECK_BTN_ALL(input->press.button, BTN_Z)) {
            if (gSaveContext.save.cutsceneIndex == 0x8000) {
                gSaveContext.save.cutsceneIndex = 0;
            } else if (gSaveContext.save.cutsceneIndex == 0) {
                gSaveContext.save.cutsceneIndex = 0xFFF0;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF0) {
                gSaveContext.save.cutsceneIndex = 0xFFF1;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF1) {
                gSaveContext.save.cutsceneIndex = 0xFFF2;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF2) {
                gSaveContext.save.cutsceneIndex = 0xFFF3;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF3) {
                gSaveContext.save.cutsceneIndex = 0xFFF4;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF4) {
                gSaveContext.save.cutsceneIndex = 0xFFF5;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF5) {
                gSaveContext.save.cutsceneIndex = 0xFFF6;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF6) {
                gSaveContext.save.cutsceneIndex = 0xFFF7;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF7) {
                gSaveContext.save.cutsceneIndex = 0xFFF8;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF8) {
                gSaveContext.save.cutsceneIndex = 0xFFF9;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF9) {
                gSaveContext.save.cutsceneIndex = 0xFFFA;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFFA) {
                gSaveContext.save.cutsceneIndex = 0x8000;
            }
        } else if (CHECK_BTN_ALL(input->press.button, BTN_R)) {
            if (gSaveContext.save.cutsceneIndex == 0x8000) {
                gSaveContext.save.cutsceneIndex = 0xFFFA;
            } else if (gSaveContext.save.cutsceneIndex == 0) {
                gSaveContext.save.cutsceneIndex = 0x8000;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF0) {
                gSaveContext.save.cutsceneIndex = 0;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF1) {
                gSaveContext.save.cutsceneIndex = 0xFFF0;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF2) {
                gSaveContext.save.cutsceneIndex = 0xFFF1;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF3) {
                gSaveContext.save.cutsceneIndex = 0xFFF2;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF4) {
                gSaveContext.save.cutsceneIndex = 0xFFF3;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF5) {
                gSaveContext.save.cutsceneIndex = 0xFFF4;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF6) {
                gSaveContext.save.cutsceneIndex = 0xFFF5;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF7) {
                gSaveContext.save.cutsceneIndex = 0xFFF6;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF8) {
                gSaveContext.save.cutsceneIndex = 0xFFF7;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFF9) {
                gSaveContext.save.cutsceneIndex = 0xFFF8;
            } else if (gSaveContext.save.cutsceneIndex == 0xFFFA) {
                gSaveContext.save.cutsceneIndex = 0xFFF9;
            }
        }

        gSaveContext.save.nightFlag = 0;
        if (gSaveContext.save.cutsceneIndex == 0) {
            gSaveContext.save.nightFlag = 1;
        }

        // user can change "opt", but it doesn't do anything
        if (CHECK_BTN_ALL(input->press.button, BTN_CUP)) {
            this->opt--;
        }
        if (CHECK_BTN_ALL(input->press.button, BTN_CDOWN)) {
            this->opt++;
        }

        if (CHECK_BTN_ALL(input->press.button, BTN_DUP)) {
            if (this->lockUp == true) {
                this->timerUp = 0;
            }
            if (this->timerUp == 0) {
                this->timerUp = 20;
                this->lockUp = true;
                Audio_PlaySfxGeneral(NA_SE_IT_SWORD_IMPACT, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                this->verticalInput = R_UPDATE_RATE;
            }
        }

        if (CHECK_BTN_ALL(input->cur.button, BTN_DUP) && this->timerUp == 0) {
            Audio_PlaySfxGeneral(NA_SE_IT_SWORD_IMPACT, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            this->verticalInput = R_UPDATE_RATE * 3;
        }

        if (CHECK_BTN_ALL(input->press.button, BTN_DDOWN)) {
            if (this->lockDown == true) {
                this->timerDown = 0;
            }
            if (this->timerDown == 0) {
                this->timerDown = 20;
                this->lockDown = true;
                Audio_PlaySfxGeneral(NA_SE_IT_SWORD_IMPACT, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                this->verticalInput = -R_UPDATE_RATE;
            }
        }

        if (CHECK_BTN_ALL(input->cur.button, BTN_DDOWN) && (this->timerDown == 0)) {
            Audio_PlaySfxGeneral(NA_SE_IT_SWORD_IMPACT, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            this->verticalInput = -R_UPDATE_RATE * 3;
        }

        if (CHECK_BTN_ALL(input->press.button, BTN_DLEFT) || CHECK_BTN_ALL(input->cur.button, BTN_DLEFT)) {
            Audio_PlaySfxGeneral(NA_SE_IT_SWORD_IMPACT, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            this->verticalInput = R_UPDATE_RATE;
        }

        if (CHECK_BTN_ALL(input->press.button, BTN_DRIGHT) || CHECK_BTN_ALL(input->cur.button, BTN_DRIGHT)) {
            Audio_PlaySfxGeneral(NA_SE_IT_SWORD_IMPACT, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            this->verticalInput = -R_UPDATE_RATE;
        }
    }

    if (CHECK_BTN_ALL(input->press.button, BTN_L)) {
        this->pageDownIndex++;
        this->pageDownIndex =
            (this->pageDownIndex + ARRAY_COUNT(this->pageDownStops)) % ARRAY_COUNT(this->pageDownStops);
        this->currentScene = this->topDisplayedScene = this->pageDownStops[this->pageDownIndex];
    }

    this->verticalInputAccumulator += this->verticalInput;

    if (this->verticalInputAccumulator < -7) {
        this->verticalInput = 0;
        this->verticalInputAccumulator = 0;

        this->currentScene++;
        this->currentScene = (this->currentScene + this->count) % this->count;

        if (this->currentScene == ((this->topDisplayedScene + this->count + 19) % this->count)) {
            this->topDisplayedScene++;
            this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;
        }
    }

    if (this->verticalInputAccumulator > 7) {
        this->verticalInput = 0;
        this->verticalInputAccumulator = 0;

        if (this->currentScene == this->topDisplayedScene) {
            this->topDisplayedScene -= 2;
            this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;
        }

        this->currentScene--;
        this->currentScene = (this->currentScene + this->count) % this->count;

        if (this->currentScene == ((this->topDisplayedScene + this->count) % this->count)) {
            this->topDisplayedScene--;
            this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;
        }
    }

    this->currentScene = (this->currentScene + this->count) % this->count;
    this->topDisplayedScene = (this->topDisplayedScene + this->count) % this->count;

    dREG(80) = this->currentScene;
    dREG(81) = this->topDisplayedScene;
    dREG(82) = this->pageDownIndex;

    if (this->timerUp != 0) {
        this->timerUp--;
    }

    if (this->timerUp == 0) {
        this->lockUp = false;
    }

    if (this->timerDown != 0) {
        this->timerDown--;
    }

    if (this->timerDown == 0) {
        this->lockDown = false;
    }
}

void MapSelect_PrintMenu(MapSelectState* this, GfxPrint* printer) {
    s32 scene;
    s32 i;
    char* name;

    GfxPrint_SetColor(printer, 255, 155, 150, 255);
    GfxPrint_SetPos(printer, 12, 2);
    GfxPrint_Printf(printer, "ZELDA MAP SELECT");
    GfxPrint_SetColor(printer, 255, 255, 255, 255);

    for (i = 0; i < 20; i++) {
        GfxPrint_SetPos(printer, 9, i + 4);

        scene = (this->topDisplayedScene + i + this->count) % this->count;
        if (scene == this->currentScene) {
            GfxPrint_SetColor(printer, 255, 20, 20, 255);
        } else {
            GfxPrint_SetColor(printer, 200, 200, 55, 255);
        }

        name = this->scenes[scene].name;
        if (name == NULL) {
            name = "**Null**";
        }

        GfxPrint_Printf(printer, "%s", name);
    };

    GfxPrint_SetColor(printer, 155, 55, 150, 255);
    GfxPrint_SetPos(printer, 20, 26);
    GfxPrint_Printf(printer, "OPT=%d", this->opt);
}

static const char* sLoadingMessages[] = {
    // "Please wait a minute"
    GFXP_HIRAGANA "ｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ",
    // "Hold on a sec"
    GFXP_HIRAGANA "ﾁｮｯﾄ ﾏｯﾃﾈ",
    // "Wait a moment"
    GFXP_KATAKANA "ｳｪｲﾄ ｱ ﾓｰﾒﾝﾄ",
    // "Loading"
    GFXP_KATAKANA "ﾛｰﾄﾞ" GFXP_HIRAGANA "ﾁｭｳ",
    // "Now working"
    GFXP_HIRAGANA "ﾅｳ ﾜｰｷﾝｸﾞ",
    // "Now creating"
    GFXP_HIRAGANA "ｲﾏ ﾂｸｯﾃﾏｽ",
    // "It's not broken"
    GFXP_HIRAGANA "ｺｼｮｳｼﾞｬﾅｲﾖ",
    // "Coffee Break"
    GFXP_KATAKANA "ｺｰﾋｰ ﾌﾞﾚｲｸ",
    // "Please set B side"
    GFXP_KATAKANA "Bﾒﾝｦｾｯﾄｼﾃｸﾀﾞｻｲ",
    // "Be patient, now"
    GFXP_HIRAGANA "ｼﾞｯﾄ" GFXP_KATAKANA "ｶﾞﾏﾝ" GFXP_HIRAGANA "ﾉ" GFXP_KATAKANA "ｺ" GFXP_HIRAGANA "ﾃﾞｱｯﾀ",
    // "Please wait just a minute"
    GFXP_HIRAGANA "ｲﾏｼﾊﾞﾗｸｵﾏﾁｸﾀﾞｻｲ",
    // "Don't worry, don't worry. Take a break, take a break."
    GFXP_HIRAGANA "ｱﾜﾃﾅｲｱﾜﾃﾅｲ｡ﾋﾄﾔｽﾐﾋﾄﾔｽﾐ｡",
};

void MapSelect_PrintLoadingMessage(MapSelectState* this, GfxPrint* printer) {
    s32 randomMsg;

    GfxPrint_SetPos(printer, 10, 15);
    GfxPrint_SetColor(printer, 255, 255, 255, 255);
    randomMsg = Rand_ZeroOne() * ARRAY_COUNT(sLoadingMessages);
    GfxPrint_Printf(printer, "%s", sLoadingMessages[randomMsg]);
}

static const char* sAgeLabels[] = {
    GFXP_HIRAGANA "17(ﾜｶﾓﾉ)", // "17(young)"
    GFXP_HIRAGANA "5(ﾜｶｽｷﾞ)", // "5(very young)"
};

void MapSelect_PrintAgeSetting(MapSelectState* this, GfxPrint* printer, s32 age) {
    GfxPrint_SetPos(printer, 4, 26);
    GfxPrint_SetColor(printer, 255, 255, 55, 255);
    GfxPrint_Printf(printer, "Age:%s", sAgeLabels[age]);
}

void MapSelect_PrintCutsceneSetting(MapSelectState* this, GfxPrint* printer, u16 csIndex) {
    char* label;

    GfxPrint_SetPos(printer, 4, 25);
    GfxPrint_SetColor(printer, 255, 255, 55, 255);

    switch (csIndex) {
        case 0:
            label = GFXP_HIRAGANA " ﾖﾙ " GFXP_KATAKANA "ｺﾞﾛﾝ";
            gSaveContext.save.dayTime = CLOCK_TIME(0, 0);
            break;
        case 0x8000:
            // clang-format off
            gSaveContext.save.dayTime = CLOCK_TIME(12, 0); label = GFXP_HIRAGANA "ｵﾋﾙ " GFXP_KATAKANA "ｼﾞｬﾗ";
            // clang-format on
            break;
        case 0xFFF0:
            // clang-format off
            gSaveContext.save.dayTime = CLOCK_TIME(12, 0); label = "ﾃﾞﾓ00";
            // clang-format on
            break;
        case 0xFFF1:
            label = "ﾃﾞﾓ01";
            break;
        case 0xFFF2:
            label = "ﾃﾞﾓ02";
            break;
        case 0xFFF3:
            label = "ﾃﾞﾓ03";
            break;
        case 0xFFF4:
            label = "ﾃﾞﾓ04";
            break;
        case 0xFFF5:
            label = "ﾃﾞﾓ05";
            break;
        case 0xFFF6:
            label = "ﾃﾞﾓ06";
            break;
        case 0xFFF7:
            label = "ﾃﾞﾓ07";
            break;
        case 0xFFF8:
            label = "ﾃﾞﾓ08";
            break;
        case 0xFFF9:
            label = "ﾃﾞﾓ09";
            break;
        case 0xFFFA:
            label = "ﾃﾞﾓ0A";
            break;
    };

    gSaveContext.skyboxTime = gSaveContext.save.dayTime;
    GfxPrint_Printf(printer, "Stage:" GFXP_KATAKANA "%s", label);
}

void MapSelect_DrawMenu(MapSelectState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    GfxPrint* printer;

    OPEN_DISPS(gfxCtx, "../z_select.c", 930);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);
    Gfx_SetupFrame(gfxCtx, 0, 0, 0);
    SET_FULLSCREEN_VIEWPORT(&this->view);
    View_Apply(&this->view, VIEW_ALL);
    Gfx_SetupDL_28Opa(gfxCtx);

    printer = alloca(sizeof(GfxPrint));
    GfxPrint_Init(printer);
    GfxPrint_Open(printer, POLY_OPA_DISP);
    MapSelect_PrintMenu(this, printer);
    MapSelect_PrintAgeSetting(this, printer, ((void)0, gSaveContext.save.linkAge));
    MapSelect_PrintCutsceneSetting(this, printer, ((void)0, gSaveContext.save.cutsceneIndex));
    POLY_OPA_DISP = GfxPrint_Close(printer);
    GfxPrint_Destroy(printer);

    CLOSE_DISPS(gfxCtx, "../z_select.c", 966);
}

void MapSelect_DrawLoadingScreen(MapSelectState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;
    GfxPrint* printer;

    OPEN_DISPS(gfxCtx, "../z_select.c", 977);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);
    Gfx_SetupFrame(gfxCtx, 0, 0, 0);
    SET_FULLSCREEN_VIEWPORT(&this->view);
    View_Apply(&this->view, VIEW_ALL);
    Gfx_SetupDL_28Opa(gfxCtx);

    printer = alloca(sizeof(GfxPrint));
    GfxPrint_Init(printer);
    GfxPrint_Open(printer, POLY_OPA_DISP);
    MapSelect_PrintLoadingMessage(this, printer);
    POLY_OPA_DISP = GfxPrint_Close(printer);
    GfxPrint_Destroy(printer);

    CLOSE_DISPS(gfxCtx, "../z_select.c", 1006);
}

void MapSelect_Draw(MapSelectState* this) {
    GraphicsContext* gfxCtx = this->state.gfxCtx;

    OPEN_DISPS(gfxCtx, "../z_select.c", 1013);

    gSPSegment(POLY_OPA_DISP++, 0x00, NULL);
    Gfx_SetupFrame(gfxCtx, 0, 0, 0);
    SET_FULLSCREEN_VIEWPORT(&this->view);
    View_Apply(&this->view, VIEW_ALL);

    if (!this->state.running) {
        MapSelect_DrawLoadingScreen(this);
    } else {
        MapSelect_DrawMenu(this);
    }

    CLOSE_DISPS(gfxCtx, "../z_select.c", 1037);
}

void MapSelect_Main(GameState* thisx) {
    MapSelectState* this = (MapSelectState*)thisx;

    MapSelect_UpdateMenu(this);
    MapSelect_Draw(this);
}

void MapSelect_Destroy(GameState* thisx) {
    PRINTF("%c", BEL);
    // "view_cleanup will hang, so it won't be called"
    PRINTF("*** view_cleanupはハングアップするので、呼ばない ***\n");
}

void MapSelect_Init(GameState* thisx) {
    MapSelectState* this = (MapSelectState*)thisx;

    this->state.main = MapSelect_Main;
    this->state.destroy = MapSelect_Destroy;
    this->scenes = sScenes;
    this->topDisplayedScene = 4;
    this->currentScene = 4;
    this->pageDownStops[0] = 0;  // Hyrule Field
    this->pageDownStops[1] = 19; // Temple Of Time
    this->pageDownStops[2] = 37; // Treasure Chest Game
    this->pageDownStops[3] = 51; // Gravekeeper's Hut
    this->pageDownStops[4] = 59; // Zora Shop
    this->pageDownStops[5] = 73; // Bottom of the Well
    this->pageDownStops[6] = 91; // Escaping Ganon's Tower 3
    this->pageDownIndex = 0;
    this->opt = 0;
    this->count = ARRAY_COUNT(sScenes);
    View_Init(&this->view, this->state.gfxCtx);
    this->view.flags = (VIEW_PROJECTION_ORTHO | VIEW_VIEWPORT);
    this->verticalInputAccumulator = 0;
    this->verticalInput = 0;
    this->timerUp = 0;
    this->timerDown = 0;
    this->lockUp = 0;
    this->lockDown = 0;
    this->unk_234 = 0;

    if ((dREG(80) >= 0) && (dREG(80) < this->count)) {
        this->currentScene = dREG(80);
        this->topDisplayedScene = dREG(81);
        this->pageDownIndex = dREG(82);
    }

    R_UPDATE_RATE = 1;

    {
        u32 size = (uintptr_t)_z_select_staticSegmentRomEnd - (uintptr_t)_z_select_staticSegmentRomStart;

        this->staticSegment = GAME_STATE_ALLOC(&this->state, size, "../z_select.c", 1114);
        DMA_REQUEST_SYNC(this->staticSegment, (uintptr_t)_z_select_staticSegmentRomStart, size, "../z_select.c", 1115);
    }

    gSaveContext.save.cutsceneIndex = 0x8000;
    gSaveContext.save.linkAge = LINK_AGE_ADULT;
}
