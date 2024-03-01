#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "hm_comp_scene.h"
#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

/**
 * Header Child Day (Default)
*/
#define LENGTH_HM_COMP_ROOM_7_HEADER00_OBJECTLIST 5
#define LENGTH_HM_COMP_ROOM_7_HEADER00_ACTORLIST 7
SceneCmd hm_comp_room_7_header00[] = {
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, true, true),
    SCENE_CMD_SKYBOX_DISABLES(true, true),
    SCENE_CMD_TIME_SETTINGS(0xFF, 0xFF, 0),
    SCENE_CMD_ROOM_SHAPE(&hm_comp_room_7_shapeHeader),
    SCENE_CMD_WIND_SETTINGS(0, 0, 0, 0),
    SCENE_CMD_OBJECT_LIST(LENGTH_HM_COMP_ROOM_7_HEADER00_OBJECTLIST, hm_comp_room_7_header00_objectList),
    SCENE_CMD_ACTOR_LIST(LENGTH_HM_COMP_ROOM_7_HEADER00_ACTORLIST, hm_comp_room_7_header00_actorList),
    SCENE_CMD_END(),
};

s16 hm_comp_room_7_header00_objectList[LENGTH_HM_COMP_ROOM_7_HEADER00_OBJECTLIST] = {
    OBJECT_IK,
    OBJECT_ST,
    OBJECT_GI_SUTARU,
    OBJECT_JYA_IRON,
    OBJECT_HIDAN_OBJECTS,
};

ActorEntry hm_comp_room_7_header00_actorList[LENGTH_HM_COMP_ROOM_7_HEADER00_ACTORLIST] = {
    // Lower Part of Megaton Statue
    {
        /* Actor ID   */ ACTOR_BG_HIDAN_DALM,
        /* Position   */ { 1270, 776, -997 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0900
    },

    // Iron Knuckle
    {
        /* Actor ID   */ ACTOR_EN_IK,
        /* Position   */ { 902, 736, -997 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x4801
    },

    // Brick Pillar (Spirit Temple)
    {
        /* Actor ID   */ ACTOR_BG_JYA_IRONOBJ,
        /* Position   */ { 935, 736, -997 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0001
    },

    // Lower Part of Megaton Statue
    {
        /* Actor ID   */ ACTOR_BG_HIDAN_DALM,
        /* Position   */ { 1270, 816, -997 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0A01
    },

    // Brick Pillar (Spirit Temple)
    {
        /* Actor ID   */ ACTOR_BG_JYA_IRONOBJ,
        /* Position   */ { 935, 736, -1187 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0000
    },

    // Lower Part of Megaton Statue
    {
        /* Actor ID   */ ACTOR_BG_HIDAN_DALM,
        /* Position   */ { 1270, 736, -997 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0800
    },

    // Brick Pillar (Spirit Temple)
    {
        /* Actor ID   */ ACTOR_BG_JYA_IRONOBJ,
        /* Position   */ { 935, 736, -807 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0000
    },
};

RoomShapeNormal hm_comp_room_7_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(hm_comp_room_7_shapeDListEntry),
    hm_comp_room_7_shapeDListEntry,
    hm_comp_room_7_shapeDListEntry + ARRAY_COUNT(hm_comp_room_7_shapeDListEntry)
};

RoomShapeDListsEntry hm_comp_room_7_shapeDListEntry[1] = {
    { hm_comp_room_7_entry_0_opaque, NULL },
};

Gfx hm_comp_room_7_entry_0_opaque[] = {
	gsSPDisplayList(hm_comp_dl_Circle_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

Vtx hm_comp_dl_Circle_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {596, 736, -659}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {596, 1159, -659}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {596, 1159, -1335}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {596, 736, -1335}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1311, 736, -659}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1311, 1159, -659}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1311, 1159, -1335}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1311, 736, -1335}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx hm_comp_dl_Circle_mesh_layer_Opaque_vtx_0[79] = {
	{{ {1291, 736, -1137}, 0, {2046, 7448}, {127, 127, 127, 255} }},
	{{ {1093, 1071, -1335}, 0, {8563, -1001}, {100, 100, 100, 255} }},
	{{ {1093, 736, -1335}, 0, {8563, 7448}, {127, 127, 127, 255} }},
	{{ {1291, 1071, -1137}, 0, {2046, -1001}, {100, 100, 100, 255} }},
	{{ {1291, 1071, -857}, 0, {-4471, -1001}, {100, 100, 100, 255} }},
	{{ {1291, 836, -1027}, 0, {-513, 4926}, {120, 120, 120, 255} }},
	{{ {1291, 736, -1027}, 0, {-513, 7448}, {127, 127, 127, 255} }},
	{{ {1291, 836, -967}, 0, {-1911, 4926}, {120, 120, 120, 255} }},
	{{ {1291, 736, -967}, 0, {-1911, 7448}, {127, 127, 127, 255} }},
	{{ {1291, 736, -857}, 0, {-4471, 7448}, {127, 127, 127, 255} }},
	{{ {616, 736, -857}, 0, {2046, 7448}, {127, 127, 127, 255} }},
	{{ {814, 1071, -659}, 0, {-4471, -1001}, {100, 100, 100, 255} }},
	{{ {814, 736, -659}, 0, {-4471, 7448}, {127, 127, 127, 255} }},
	{{ {616, 1071, -857}, 0, {2046, -1001}, {100, 100, 100, 255} }},
	{{ {616, 1071, -1060}, 0, {6779, -1001}, {100, 100, 100, 255} }},
	{{ {616, 836, -967}, 0, {4606, 4926}, {127, 127, 127, 255} }},
	{{ {616, 736, -967}, 0, {4606, 7448}, {127, 127, 127, 255} }},
	{{ {616, 836, -1027}, 0, {6003, 4926}, {128, 128, 128, 255} }},
	{{ {616, 736, -1027}, 0, {6003, 7448}, {128, 128, 128, 255} }},
	{{ {616, 1071, -1137}, 0, {8563, -1001}, {100, 100, 100, 255} }},
	{{ {616, 736, -1137}, 0, {8563, 7448}, {127, 127, 127, 255} }},
	{{ {616, 1159, -1066}, 0, {6912, -3211}, {0, 0, 0, 224} }},
	{{ {616, 1159, -1137}, 0, {8563, -3211}, {0, 0, 0, 255} }},
	{{ {616, 1159, -857}, 0, {2046, -3211}, {0, 0, 0, 0} }},
	{{ {814, 1159, -659}, 0, {-4471, -3211}, {0, 0, 0, 255} }},
	{{ {814, 736, -1335}, 0, {688, 7448}, {127, 127, 127, 255} }},
	{{ {616, 1071, -1137}, 0, {-5828, -1001}, {100, 100, 100, 255} }},
	{{ {616, 736, -1137}, 0, {-5828, 7448}, {127, 127, 127, 255} }},
	{{ {814, 1071, -1335}, 0, {688, -1001}, {100, 100, 100, 255} }},
	{{ {1093, 736, -1335}, 0, {7205, 7448}, {127, 127, 127, 255} }},
	{{ {1093, 1071, -1335}, 0, {7205, -1001}, {100, 100, 100, 255} }},
	{{ {814, 1159, -1335}, 0, {688, -3211}, {0, 0, 0, 255} }},
	{{ {1093, 1071, -1335}, 0, {7205, -1001}, {100, 100, 100, 255} }},
	{{ {1093, 1159, -1335}, 0, {7205, -3211}, {0, 0, 0, 255} }},
	{{ {814, 1159, -1335}, 0, {688, -3211}, {0, 0, 0, 255} }},
	{{ {814, 1071, -1335}, 0, {688, -1001}, {100, 100, 100, 255} }},
	{{ {616, 1159, -1137}, 0, {-5828, -3211}, {0, 0, 0, 255} }},
	{{ {616, 1071, -1137}, 0, {-5828, -1001}, {100, 100, 100, 255} }},
	{{ {1291, 1071, -857}, 0, {-4471, -1001}, {100, 100, 100, 255} }},
	{{ {1291, 1159, -857}, 0, {-4471, -3211}, {0, 0, 0, 255} }},
	{{ {1291, 1159, -1137}, 0, {2046, -3211}, {2, 2, 2, 255} }},
	{{ {1291, 1071, -1137}, 0, {2046, -1001}, {100, 100, 100, 255} }},
	{{ {1093, 1159, -1335}, 0, {8563, -3211}, {0, 0, 0, 255} }},
	{{ {1093, 1071, -1335}, 0, {8563, -1001}, {100, 100, 100, 255} }},
	{{ {814, 1071, -659}, 0, {-5828, -1001}, {100, 100, 100, 255} }},
	{{ {814, 1159, -659}, 0, {-5828, -3211}, {0, 0, 0, 255} }},
	{{ {1093, 1159, -659}, 0, {688, -3211}, {0, 0, 0, 255} }},
	{{ {1093, 1071, -659}, 0, {688, -1001}, {100, 100, 100, 255} }},
	{{ {1291, 1159, -857}, 0, {7205, -3211}, {0, 0, 0, 255} }},
	{{ {1291, 1071, -857}, 0, {7205, -1001}, {100, 100, 100, 255} }},
	{{ {1093, 736, -659}, 0, {688, 7448}, {127, 127, 127, 255} }},
	{{ {1291, 736, -857}, 0, {7205, 7448}, {127, 127, 127, 255} }},
	{{ {814, 736, -659}, 0, {-5828, 7448}, {127, 127, 127, 255} }},
	{{ {616, 836, -967}, 0, {-7467, 4926}, {127, 127, 127, 255} }},
	{{ {616, 736, -967}, 0, {-7467, 7448}, {127, 127, 127, 255} }},
	{{ {596, 736, -967}, 0, {-7933, 7448}, {253, 253, 253, 255} }},
	{{ {596, 836, -967}, 0, {-7933, 4926}, {255, 255, 255, 255} }},
	{{ {616, 836, -1027}, 0, {-6888, -1812}, {128, 128, 128, 255} }},
	{{ {616, 836, -967}, 0, {-7467, -414}, {127, 127, 127, 255} }},
	{{ {596, 836, -967}, 0, {-7933, -607}, {255, 255, 255, 255} }},
	{{ {596, 836, -1027}, 0, {-7354, -2005}, {255, 255, 255, 255} }},
	{{ {616, 736, -1027}, 0, {-6888, 7448}, {128, 128, 128, 255} }},
	{{ {616, 836, -1027}, 0, {-6888, 4926}, {128, 128, 128, 255} }},
	{{ {596, 836, -1027}, 0, {-7354, 4926}, {255, 255, 255, 255} }},
	{{ {616, 736, -1027}, 0, {-6888, 7448}, {128, 128, 128, 255} }},
	{{ {596, 836, -1027}, 0, {-7354, 4926}, {255, 255, 255, 255} }},
	{{ {596, 736, -1027}, 0, {-7354, 7448}, {166, 166, 166, 255} }},
	{{ {1291, 736, -967}, 0, {8265, 7448}, {127, 127, 127, 255} }},
	{{ {1291, 836, -967}, 0, {8265, 4926}, {120, 120, 120, 255} }},
	{{ {1311, 836, -967}, 0, {8731, 4926}, {120, 120, 120, 255} }},
	{{ {1311, 736, -967}, 0, {8731, 7448}, {127, 127, 127, 255} }},
	{{ {1291, 836, -1027}, 0, {8844, 4926}, {120, 120, 120, 255} }},
	{{ {1291, 736, -1027}, 0, {8844, 7448}, {127, 127, 127, 255} }},
	{{ {1311, 736, -1027}, 0, {9310, 7448}, {127, 127, 127, 255} }},
	{{ {1311, 836, -1027}, 0, {9310, 4926}, {120, 120, 120, 255} }},
	{{ {1291, 836, -967}, 0, {8265, 6103}, {120, 120, 120, 255} }},
	{{ {1291, 836, -1027}, 0, {8844, 4705}, {120, 120, 120, 255} }},
	{{ {1311, 836, -1027}, 0, {9310, 4898}, {120, 120, 120, 255} }},
	{{ {1311, 836, -967}, 0, {8731, 6296}, {120, 120, 120, 255} }},
};

Gfx hm_comp_dl_Circle_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(hm_comp_dl_Circle_mesh_layer_Opaque_vtx_0 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(0, 6, 5, 0, 4, 5, 7, 0),
	gsSP2Triangles(7, 8, 4, 0, 8, 9, 4, 0),
	gsSP2Triangles(10, 11, 12, 0, 10, 13, 11, 0),
	gsSP2Triangles(14, 13, 10, 0, 14, 10, 15, 0),
	gsSP2Triangles(10, 16, 15, 0, 15, 17, 14, 0),
	gsSP2Triangles(17, 18, 14, 0, 18, 19, 14, 0),
	gsSP2Triangles(18, 20, 19, 0, 19, 21, 14, 0),
	gsSP2Triangles(19, 22, 21, 0, 14, 21, 23, 0),
	gsSP2Triangles(14, 23, 13, 0, 13, 23, 24, 0),
	gsSP2Triangles(13, 24, 11, 0, 25, 26, 27, 0),
	gsSP2Triangles(25, 28, 26, 0, 29, 28, 25, 0),
	gsSP2Triangles(29, 30, 28, 0, 30, 31, 28, 0),
	gsSPVertex(hm_comp_dl_Circle_mesh_layer_Opaque_vtx_0 + 32, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 2, 4, 0),
	gsSP2Triangles(3, 4, 5, 0, 6, 7, 8, 0),
	gsSP2Triangles(6, 8, 9, 0, 9, 8, 10, 0),
	gsSP2Triangles(9, 10, 11, 0, 12, 13, 14, 0),
	gsSP2Triangles(12, 14, 15, 0, 15, 14, 16, 0),
	gsSP2Triangles(15, 16, 17, 0, 18, 15, 17, 0),
	gsSP2Triangles(18, 17, 19, 0, 20, 15, 18, 0),
	gsSP2Triangles(20, 12, 15, 0, 21, 22, 23, 0),
	gsSP2Triangles(21, 23, 24, 0, 25, 26, 27, 0),
	gsSP2Triangles(25, 27, 28, 0, 29, 30, 31, 0),
	gsSPVertex(hm_comp_dl_Circle_mesh_layer_Opaque_vtx_0 + 64, 15, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(3, 5, 6, 0, 7, 8, 9, 0),
	gsSP2Triangles(7, 9, 10, 0, 11, 12, 13, 0),
	gsSP1Triangle(11, 13, 14, 0),
	gsSPEndDisplayList(),
};

Vtx hm_comp_dl_Circle_mesh_layer_Opaque_vtx_1[16] = {
	{{ {616, 736, -967}, 0, {-3434, -2723}, {127, 127, 127, 255} }},
	{{ {596, 736, -1027}, 0, {-3118, -3355}, {166, 166, 166, 255} }},
	{{ {596, 736, -967}, 0, {-3592, -2881}, {253, 253, 253, 255} }},
	{{ {616, 736, -1027}, 0, {-2960, -3197}, {128, 128, 128, 255} }},
	{{ {616, 736, -1137}, 0, {-2092, -4065}, {127, 127, 127, 255} }},
	{{ {1093, 736, -659}, 0, {-2092, 3481}, {127, 127, 127, 255} }},
	{{ {616, 736, -857}, 0, {-4302, -1855}, {127, 127, 127, 255} }},
	{{ {814, 736, -659}, 0, {-4302, 1271}, {127, 127, 127, 255} }},
	{{ {1093, 736, -1335}, 0, {3244, -1855}, {127, 127, 127, 255} }},
	{{ {814, 736, -1335}, 0, {1034, -4065}, {127, 127, 127, 255} }},
	{{ {1291, 736, -1027}, 0, {2376, 2139}, {127, 127, 127, 255} }},
	{{ {1291, 736, -967}, 0, {1902, 2613}, {127, 127, 127, 255} }},
	{{ {1291, 736, -857}, 0, {1034, 3481}, {127, 127, 127, 255} }},
	{{ {1311, 736, -967}, 0, {2060, 2771}, {127, 127, 127, 255} }},
	{{ {1311, 736, -1027}, 0, {2534, 2297}, {127, 127, 127, 255} }},
	{{ {1291, 736, -1137}, 0, {3244, 1271}, {127, 127, 127, 255} }},
};

Gfx hm_comp_dl_Circle_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(hm_comp_dl_Circle_mesh_layer_Opaque_vtx_1 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(0, 6, 5, 0, 6, 7, 5, 0),
	gsSP2Triangles(8, 4, 5, 0, 8, 9, 4, 0),
	gsSP2Triangles(5, 10, 8, 0, 5, 11, 10, 0),
	gsSP2Triangles(5, 12, 11, 0, 10, 11, 13, 0),
	gsSP2Triangles(10, 13, 14, 0, 10, 15, 8, 0),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_dl_wall_mat_006_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 168, 168, 168, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_dl_jyasinboss_room_3Tex_009F00_ci4_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 14),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, hm_comp_dl_jyasinboss_room_3Tex_009F00_ci4_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 252),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_dl_floor_mat_004_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 170, 170, 170, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_dl_jyasinboss_room_3Tex_00AF00_rgba16_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 45),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_comp_dl_jyasinboss_room_3Tex_00AF00_rgba16_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx hm_comp_dl_Circle_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(hm_comp_dl_Circle_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_hm_comp_dl_wall_mat_006_layerOpaque),
	gsSPDisplayList(hm_comp_dl_Circle_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_hm_comp_dl_floor_mat_004_layerOpaque),
	gsSPDisplayList(hm_comp_dl_Circle_mesh_layer_Opaque_tri_1),
	gsSPEndDisplayList(),
};

