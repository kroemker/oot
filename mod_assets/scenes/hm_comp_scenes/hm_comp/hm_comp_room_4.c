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
#define LENGTH_HM_COMP_ROOM_4_HEADER00_OBJECTLIST 5
#define LENGTH_HM_COMP_ROOM_4_HEADER00_ACTORLIST 10
SceneCmd hm_comp_room_4_header00[] = {
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
    SCENE_CMD_SKYBOX_DISABLES(true, true),
    SCENE_CMD_TIME_SETTINGS(0xFF, 0xFF, 0),
    SCENE_CMD_ROOM_SHAPE(&hm_comp_room_4_shapeHeader),
    SCENE_CMD_OBJECT_LIST(LENGTH_HM_COMP_ROOM_4_HEADER00_OBJECTLIST, hm_comp_room_4_header00_objectList),
    SCENE_CMD_ACTOR_LIST(LENGTH_HM_COMP_ROOM_4_HEADER00_ACTORLIST, hm_comp_room_4_header00_actorList),
    SCENE_CMD_END(),
};

s16 hm_comp_room_4_header00_objectList[LENGTH_HM_COMP_ROOM_4_HEADER00_OBJECTLIST] = {
    OBJECT_WIZ,
    OBJECT_MIZU_OBJECTS,
    OBJECT_BOX,
    OBJECT_HIDAN_OBJECTS,
    OBJECT_SYOKUDAI,
};

ActorEntry hm_comp_room_4_header00_actorList[LENGTH_HM_COMP_ROOM_4_HEADER00_ACTORLIST] = {
    // Breakable Pot
    {
        /* Actor ID   */ ACTOR_OBJ_TSUBO,
        /* Position   */ { -3842, -61, -1682 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x5E09
    },

    // Custom Actor
    {
        /* Actor ID   */ ACTOR_EN_WIZ,
        /* Position   */ { -4248, -61, -2086 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x8001
    },

    // Torch
    {
        /* Actor ID   */ ACTOR_OBJ_SYOKUDAI,
        /* Position   */ { -5461, 187, -2017 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0400
    },

    // Metal Gate
    {
        /* Actor ID   */ ACTOR_BG_HIDAN_KOUSI,
        /* Position   */ { -4722, -61, -2036 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(90.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x8001
    },

    // Breakable Pot
    {
        /* Actor ID   */ ACTOR_OBJ_TSUBO,
        /* Position   */ { -4653, -61, -1682 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x6009
    },

    // Breakable Pot
    {
        /* Actor ID   */ ACTOR_OBJ_TSUBO,
        /* Position   */ { -3842, -61, -2484 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x5C09
    },

    // Breakable Pot
    {
        /* Actor ID   */ ACTOR_OBJ_TSUBO,
        /* Position   */ { -4654, -61, -2484 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x5A09
    },

    // Treasure Chest
    {
        /* Actor ID   */ ACTOR_EN_BOX,
        /* Position   */ { -5528, 187, -2092 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0B00
    },

    // Metal Gate
    {
        /* Actor ID   */ ACTOR_BG_HIDAN_KOUSI,
        /* Position   */ { -4722, -61, -2148 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x8001
    },

    // Torch
    {
        /* Actor ID   */ ACTOR_OBJ_SYOKUDAI,
        /* Position   */ { -5461, 187, -2167 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0400
    },
};

RoomShapeNormal hm_comp_room_4_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(hm_comp_room_4_shapeDListEntry),
    hm_comp_room_4_shapeDListEntry,
    hm_comp_room_4_shapeDListEntry + ARRAY_COUNT(hm_comp_room_4_shapeDListEntry)
};

RoomShapeDListsEntry hm_comp_room_4_shapeDListEntry[1] = {
    { hm_comp_room_4_entry_0_opaque, NULL },
};

Gfx hm_comp_room_4_entry_0_opaque[] = {
	gsSPDisplayList(hm_comp_dl_Geometry_005_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

u64 hm_comp_dl_ganontika_room_19Tex_006D40_rgba16_ci8[] = {
	0x0001000203040506, 0x0708090a09020b0c, 0x0d0e070f10110212, 0x1314150614101602, 0x02170a0a020b0800, 0x0000021800010219, 0x0802011a061b0000, 0x1c1d1b011d1d0412, 
	0x01011e0f0b080b03, 0x1f20210022081b0e, 0x1310230f24250814, 0x2605270710282402, 0x0008252418241708, 0x24020b0e29180909, 0x101c1b0b0000001d, 0x0e1b1b1d1b29122a, 
	0x011b0e0c08020c16, 0x051b2b09241d0622, 0x222c131d00082d1c, 0x2713081322092525, 0x1b08002425250018, 0x0000002e292f1d09, 0x21301d0b0000071d, 0x1b1b031b1d000017, 
	0x1b071b1c2a0c1c21, 0x1b07131b060f1322, 0x0e3100000e27041b, 0x32320b2929000802, 0x3317000424253435, 0x071d1d2524130408, 0x0900121d080b281b, 0x261d0f040e121202, 
	0x1d130e0736303701, 0x2e08220303043807, 0x1d0017121427161c, 0x031c162425001306, 0x090a243102253904, 0x0e273a0000260b28, 0x2509013013100a08, 0x2a1b1b283b121709, 
	0x1316041d033c041d, 0x013100053d3e3030, 0x1d001b031d2d3f07, 0x0b160b001208400c, 0x1d4142170b1b0b1d, 0x0c0f431300171839, 0x441e0b130e04180f, 0x12083b1300241b12, 
	0x0713381b09012417, 0x184546053e471c04, 0x1d0c1c1a16020443, 0x102c350a1d07481b, 0x0e1c241d29041324, 0x1d0e494a10080000, 0x1b130b411d1b2604, 0x244b391008020b0c, 
	0x294c082928004d4e, 0x0208041b3e1d0707, 0x1308040404052428, 0x2c24012e0d4f1316, 0x430e0f501c160813, 0x16072a51280b0012, 0x0e0b412946040d05, 0x1844240b240e141d, 
	0x525202533a290033, 0x0a081326063e0e0f, 0x1954081204502428, 0x000201554756571a, 0x04014054071b1332, 0x12021d1028000813, 0x1b08290258013739, 0x2129181713100451, 
	0x0829000225080802, 0x351202081c570f1d, 0x41221700590e1617, 0x090a415a0e01290e, 0x1d1d08222905435b, 0x004e110808081310, 0x410202121b000039, 0x24061b121b0b4103, 
	0x3a5c29522502295d, 0x3e180a08041d5e5f, 0x1217441700123008, 0x17024156131b2222, 0x1d243900560e0c0b, 0x0c1717080808240a, 0x0000120f56290908, 0x4c001d22100f0304, 
	0x1c57130102602916, 0x05082917092c041b, 0x1d580c13291b1d04, 0x1c1b082428613e00, 0x292902130c133925, 0x0b17171762242525, 0x12121d021b16001b, 0x0f0b023b18064012, 
	0x261c4827223a2d29, 0x632c3e1d34293e0b, 0x640e323e1300000e, 0x3057182564410600, 0x2464306566021024, 0x2400331717351200, 0x011204040b120d04, 0x0000241867013010, 
	0x1c04040e0d272d2c, 0x1813141b29280200, 0x4643680e21001e1d, 0x30140b184b631869, 0x24240f2a0017511d, 0x2517171717173112, 0x1e0b1b1b0100141d, 0x1739085825254456, 
	0x0808410e6a6b0304, 0x2c1c4c4c132d2431, 0x074116071d1d4a1d, 0x39041418394e4410, 0x1d6c120b07241209, 0x1717442462123157, 0x1c03131d2a142c00, 0x1d293312563b4b07, 
	0x0b0b003e6d400e3d, 0x0e294e0257041d10, 0x1d176e0b26261610, 0x0139081d02024e00, 0x5142000b1b050917, 0x17072401012a0e56, 0x611b0f0e30072439, 0x121d28246f240002, 
	0x1d0b001b081b0e0e, 0x0e2112103c033d10, 0x1b247021061c7122, 0x570825071b020225, 0x2500022424521731, 0x310b1b120f720313, 0x1013734374080b18, 0x331b56114b1e0839, 
	0x0b1d2900240a1661, 0x074a74415816560b, 0x0a25024600225743, 0x130718242b071b00, 0x25250b4e52181d43, 0x13011b0f4316080c, 0x143e68063c351b12, 0x24222d081d0f2624, 
	0x1b00000824240210, 0x16301f0f17242928, 0x254275103b760230, 0x06051b421d131d1d, 0x002544000800421b, 0x01061b4800000b3e, 0x403d133b24700f07, 0x1011631e3e6f1712, 
	0x1229001e08295108, 0x560e737725180f18, 0x0b7701283728210b, 0x0541060d1217310c, 0x0829093b080c2e0b, 0x1b03320209081b0b, 0x160e0408250a0b30, 0x7817242157040166, 
	0x12311224130e1308, 0x1014272112102924, 0x2e13080101130044, 0x021d26060217310e, 0x770b101706790606, 0x031f02021209070c, 0x704e310039084c05, 0x1b7a3e240c071d01, 
	0x0c1e0e0f0e071641, 0x1f131128070b291e, 0x2b16161b2e170b24, 0x25010c2535267827, 0x01073e0c08410603, 0x0209020f0f12001b, 0x0044520b131c1c3b, 0x1830783e0b06261b, 
	0x0e270f2b1e005614, 0x1c0112143e127b07, 0x2d4013131b442413, 0x0034240b46060c13, 0x08004a7c13060e1d, 0x2509061c0e1d0000, 0x0029001d0348040b, 0x4204144f05312604, 
	0x2b0e032a651d0f2a, 0x080c3027101d0710, 0x2d303007110b0212, 0x0028391d04040a12, 0x130e2604080e1b52, 0x09091b04260e1b00, 0x001d1c6b0d1b001b, 0x48055d163213020d, 
	0x060e0708124a082e, 0x31134a06420d3e16, 0x1d143a5413131b01, 0x24101b08081e1241, 0x1c681667121d0a09, 0x09631e1d08002e1d, 0x35002a7d7e06120c, 0x7250160857721c51, 
	0x3b281113270c0800, 0x09123a070f371c0e, 0x2d08297f320f1b24, 0x39081308181d7803, 0x1b0b1824420a241d, 0x1b08081612241113, 0x04262e01013c0e1b, 0x282c1d10240f3241, 
	0x0b3b393577171d1d, 0x0a2413071d410b80, 0x100b08040e2e1d28, 0x1b2408131d0b4343, 0x0a4b3914290a0230, 0x260b0b0017351214, 0x1d0e1625422b5722, 0x00120b2821410f1b, 
	0x2228112524022112, 0x1039120122273e05, 0x100f43400c28050f, 0x040802040e30071d, 0x2400050802411c1c, 0x0b0b005228001d29, 0x29070f1d1e010510, 0x0c002924010c000b, 
	0x16080025341b0c18, 0x01081808133e080b, 0x081343511b16410b, 0x08131b1c30301d1b, 0x3d57104105711a0b, 0x0b002e0008392508, 0x0808002e1d241d41, 0x1624090000020b06, 
	0x0000240024180808, 0x29410b244129081d, 0x06081d04032e1b16, 0x21131c0443071327, 0x8113411c05050b0b, 0x0b101b120202391d, 0x0100001b08121224, 0x18020000170b010b, 
	0x020000080029241d, 0x0b24292228290810, 0x1b06081d1c2a0828, 0x411b1a571b063082, 0x130f1c618316020b, 0x2d101d02080b2929, 0x12121b080b0c1d1d, 0x0200002501004228, 
	0x000017011d24001b, 0x02000b2918241d07, 0x101b1310032a1d41, 0x1b460505061f1404, 0x0b0b0b4c05020b08, 0x101d020200292200, 0x12120808011b1d02, 0x1d0029014d662401, 
	
};

u64 hm_comp_dl_ganontika_room_19Tex_006D40_rgba16_pal_rgba16[] = {
	0x4805484748455889, 0x5847588550875809, 0x5005404540435045, 0x5009588b58495049, 0x5805500148075807, 0x6047610758454005, 0x484358c360c75047, 0x588750074809608b, 
	0x50c548855803680d, 0x4803400350896009, 0x50435003504b508b, 0x5843600548496001, 0x60494007600b3805, 0x40414883684b5883, 0x6807480160035041, 0x50c7688960077005, 
	0x584b508540476089, 0x400148c7488758cb, 0x58c9588f580b3801, 0x508338453803688b, 0x58c7488938435881, 0x604360cd60456087, 0x4009404968c960c9, 0x6843608359056885, 
	0x5081608538074083, 0x4841480b40873885, 0x680948c3688f60cb, 0x488b680b38835801, 0x408558c56887580d, 0x60c5504d4881500b, 0x604b6845500d480d, 0x704b590968c56805, 
	0x684768cb604d6105, 
};

Vtx hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-5579, -61, -1630}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-5579, 469, -1630}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-5579, 469, -2530}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-5579, -61, -2530}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-3595, -61, -1630}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-3595, 469, -1630}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-3595, 469, -2530}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-3595, -61, -2530}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_0[18] = {
	{{ {-4698, -61, -1980}, 0, {-6037, 2122}, {160, 160, 160, 255} }},
	{{ {-4698, -61, -1630}, 0, {-6037, 5358}, {167, 167, 167, 255} }},
	{{ {-3798, -61, -1630}, 0, {2284, 5358}, {177, 177, 177, 255} }},
	{{ {-3798, -61, -1980}, 0, {2284, 2122}, {180, 180, 180, 255} }},
	{{ {-4698, -61, -2205}, 0, {-6037, 43}, {177, 177, 177, 255} }},
	{{ {-3798, -61, -2205}, 0, {2284, 43}, {109, 109, 109, 255} }},
	{{ {-3615, -61, -2205}, 0, {3977, 43}, {77, 77, 77, 255} }},
	{{ {-3615, -61, -2125}, 0, {3977, 782}, {88, 88, 88, 255} }},
	{{ {-3615, -61, -2065}, 0, {3977, 1337}, {95, 95, 95, 255} }},
	{{ {-3615, -61, -1980}, 0, {3977, 2122}, {104, 104, 104, 255} }},
	{{ {-3595, -61, -2065}, 0, {4162, 1337}, {95, 95, 95, 255} }},
	{{ {-3595, -61, -2125}, 0, {4162, 782}, {88, 88, 88, 255} }},
	{{ {-3798, -61, -2530}, 0, {2284, -2961}, {122, 122, 122, 255} }},
	{{ {-4698, -61, -2530}, 0, {-6037, -2961}, {149, 149, 149, 255} }},
	{{ {-4879, -61, -1980}, 0, {-7710, 2122}, {46, 46, 46, 255} }},
	{{ {-4879, -61, -2017}, 0, {-7710, 1776}, {88, 88, 88, 255} }},
	{{ {-4879, -61, -2167}, 0, {-7710, 389}, {104, 104, 104, 255} }},
	{{ {-4879, -61, -2205}, 0, {-7710, 43}, {46, 46, 46, 255} }},
};

Gfx hm_comp_dl_Geometry_005_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_0 + 0, 18, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 0, 3, 0, 3, 5, 4, 0),
	gsSP2Triangles(6, 5, 3, 0, 7, 6, 3, 0),
	gsSP2Triangles(3, 8, 7, 0, 3, 9, 8, 0),
	gsSP2Triangles(7, 8, 10, 0, 7, 10, 11, 0),
	gsSP2Triangles(12, 13, 4, 0, 5, 12, 4, 0),
	gsSP2Triangles(14, 0, 4, 0, 15, 14, 4, 0),
	gsSP2Triangles(4, 16, 15, 0, 4, 17, 16, 0),
	gsSPEndDisplayList(),
};

Vtx hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_1[119] = {
	{{ {-4698, -61, -2205}, 0, {-499, 3064}, {177, 177, 177, 255} }},
	{{ {-4698, -61, -2530}, 0, {3235, 3064}, {149, 149, 149, 255} }},
	{{ {-4698, 469, -2530}, 0, {3235, -3025}, {0, 0, 0, 255} }},
	{{ {-4698, 139, -2205}, 0, {-499, 767}, {175, 175, 175, 255} }},
	{{ {-4698, 139, -1980}, 0, {-3084, 767}, {149, 149, 149, 255} }},
	{{ {-4698, -61, -1630}, 0, {-7105, 3064}, {167, 167, 167, 255} }},
	{{ {-4698, 469, -1630}, 0, {-7105, -3025}, {0, 0, 0, 255} }},
	{{ {-4698, -61, -1980}, 0, {-3084, 3064}, {160, 160, 160, 255} }},
	{{ {-3798, -61, -2530}, 0, {9785, 3064}, {122, 122, 122, 255} }},
	{{ {-3798, 469, -2530}, 0, {9785, -3025}, {0, 0, 0, 255} }},
	{{ {-4698, 469, -2530}, 0, {-558, -3025}, {0, 0, 0, 255} }},
	{{ {-4698, -61, -2530}, 0, {-558, 3064}, {149, 149, 149, 255} }},
	{{ {-4698, -61, -1630}, 0, {-558, 3064}, {167, 167, 167, 255} }},
	{{ {-4698, 469, -1630}, 0, {-558, -3025}, {0, 0, 0, 255} }},
	{{ {-3798, 469, -1630}, 0, {9785, -3025}, {1, 1, 1, 255} }},
	{{ {-3798, -61, -1630}, 0, {9785, 3064}, {177, 177, 177, 255} }},
	{{ {-3798, -61, -1980}, 0, {9785, 3064}, {180, 180, 180, 255} }},
	{{ {-3798, 139, -1980}, 0, {9785, 767}, {159, 159, 159, 255} }},
	{{ {-3615, 139, -1980}, 0, {11889, 767}, {76, 76, 76, 255} }},
	{{ {-3615, -61, -1980}, 0, {11889, 3064}, {104, 104, 104, 255} }},
	{{ {-3798, 469, -2530}, 0, {3235, -3025}, {0, 0, 0, 255} }},
	{{ {-3798, -61, -2530}, 0, {3235, 3064}, {122, 122, 122, 255} }},
	{{ {-3798, -61, -2205}, 0, {-499, 3064}, {109, 109, 109, 255} }},
	{{ {-3798, 139, -2205}, 0, {-499, 767}, {125, 125, 125, 255} }},
	{{ {-3798, 139, -1980}, 0, {-3084, 767}, {159, 159, 159, 255} }},
	{{ {-3798, -61, -1630}, 0, {-7105, 3064}, {177, 177, 177, 255} }},
	{{ {-3798, -61, -1980}, 0, {-3084, 3064}, {180, 180, 180, 255} }},
	{{ {-3798, 469, -1630}, 0, {-7105, -3025}, {1, 1, 1, 255} }},
	{{ {-3615, -61, -2065}, 0, {-2107, 3064}, {95, 95, 95, 255} }},
	{{ {-3615, -61, -1980}, 0, {-3084, 3064}, {104, 104, 104, 255} }},
	{{ {-3615, 139, -1980}, 0, {-3084, 767}, {76, 76, 76, 255} }},
	{{ {-3615, 39, -2065}, 0, {-2107, 1915}, {86, 86, 86, 255} }},
	{{ {-3615, 139, -1980}, 0, {-3084, 767}, {76, 76, 76, 255} }},
	{{ {-3615, 139, -2205}, 0, {-499, 767}, {76, 76, 76, 254} }},
	{{ {-3615, 39, -2065}, 0, {-2107, 1915}, {86, 86, 86, 255} }},
	{{ {-3615, 39, -2125}, 0, {-1418, 1915}, {82, 82, 82, 255} }},
	{{ {-3615, -61, -2125}, 0, {-1418, 3064}, {88, 88, 88, 255} }},
	{{ {-3615, -61, -2205}, 0, {-499, 3064}, {77, 77, 77, 255} }},
	{{ {-3595, -61, -2125}, 0, {-1418, 3064}, {88, 88, 88, 255} }},
	{{ {-3595, 39, -2125}, 0, {-1418, 1915}, {82, 82, 82, 255} }},
	{{ {-3595, 39, -2065}, 0, {-2107, 1915}, {86, 86, 86, 255} }},
	{{ {-3615, -61, -2065}, 0, {-2107, 3064}, {95, 95, 95, 255} }},
	{{ {-3595, -61, -2065}, 0, {-2107, 3064}, {95, 95, 95, 255} }},
	{{ {-3798, 139, -2205}, 0, {9785, 767}, {125, 125, 125, 255} }},
	{{ {-3798, -61, -2205}, 0, {9785, 3064}, {109, 109, 109, 255} }},
	{{ {-3615, -61, -2205}, 0, {11889, 3064}, {77, 77, 77, 255} }},
	{{ {-3615, 139, -2205}, 0, {11889, 767}, {76, 76, 76, 254} }},
	{{ {-3798, 139, -1980}, 0, {9785, 1650}, {159, 159, 159, 255} }},
	{{ {-3798, 139, -2205}, 0, {9785, -934}, {125, 125, 125, 255} }},
	{{ {-3615, 139, -2205}, 0, {11889, -934}, {76, 76, 76, 254} }},
	{{ {-3615, 139, -1980}, 0, {11889, 1650}, {76, 76, 76, 255} }},
	{{ {-4879, -61, -2167}, 0, {-930, 3064}, {104, 104, 104, 255} }},
	{{ {-4879, -61, -2205}, 0, {-499, 3064}, {46, 46, 46, 255} }},
	{{ {-4879, 139, -2205}, 0, {-499, 767}, {48, 48, 48, 255} }},
	{{ {-4879, 98, -2167}, 0, {-930, 1237}, {54, 54, 54, 255} }},
	{{ {-4879, 139, -1980}, 0, {-3084, 767}, {46, 46, 46, 255} }},
	{{ {-4879, 98, -2017}, 0, {-2653, 1237}, {55, 55, 55, 255} }},
	{{ {-4879, -61, -2017}, 0, {-2653, 3064}, {88, 88, 88, 255} }},
	{{ {-4879, -61, -1980}, 0, {-3084, 3064}, {46, 46, 46, 255} }},
	{{ {-4698, -61, -2205}, 0, {-558, 3064}, {177, 177, 177, 255} }},
	{{ {-4698, 139, -2205}, 0, {-558, 767}, {175, 175, 175, 255} }},
	{{ {-4879, 139, -2205}, 0, {-2637, 767}, {48, 48, 48, 255} }},
	{{ {-4879, -61, -2205}, 0, {-2637, 3064}, {46, 46, 46, 255} }},
	{{ {-4698, 139, -1980}, 0, {-558, 767}, {149, 149, 149, 255} }},
	{{ {-4698, -61, -1980}, 0, {-558, 3064}, {160, 160, 160, 255} }},
	{{ {-4879, -61, -1980}, 0, {-2637, 3064}, {46, 46, 46, 255} }},
	{{ {-4879, 139, -1980}, 0, {-2637, 767}, {46, 46, 46, 255} }},
	{{ {-4698, 139, -2205}, 0, {-558, -934}, {175, 175, 175, 255} }},
	{{ {-4879, 139, -1980}, 0, {-2637, 1650}, {46, 46, 46, 255} }},
	{{ {-4879, 139, -2205}, 0, {-2637, -934}, {48, 48, 48, 255} }},
	{{ {-4698, 139, -1980}, 0, {-558, 1650}, {149, 149, 149, 255} }},
	{{ {-4698, -61, -2205}, 0, {-558, -934}, {177, 177, 177, 255} }},
	{{ {-4698, -61, -1980}, 0, {-558, 1650}, {160, 160, 160, 255} }},
	{{ {-4879, 98, -2167}, 0, {-2637, -504}, {54, 54, 54, 255} }},
	{{ {-4879, 98, -2017}, 0, {-2637, 1220}, {55, 55, 55, 255} }},
	{{ {-5379, 346, -2017}, 0, {-8377, 1220}, {62, 62, 62, 255} }},
	{{ {-5379, 346, -2167}, 0, {-8377, -504}, {57, 57, 57, 255} }},
	{{ {-5579, 346, -2017}, 0, {-10678, 1220}, {52, 52, 52, 255} }},
	{{ {-5379, 346, -1967}, 0, {-8377, 1794}, {48, 48, 48, 255} }},
	{{ {-5550, 346, -1967}, 0, {-10350, 1794}, {76, 76, 76, 255} }},
	{{ {-5579, 346, -2167}, 0, {-10678, -504}, {46, 46, 46, 255} }},
	{{ {-5550, 346, -2217}, 0, {-10350, -1078}, {61, 61, 61, 255} }},
	{{ {-5379, 346, -2217}, 0, {-8377, -1078}, {46, 46, 46, 255} }},
	{{ {-4879, -61, -2167}, 0, {-2637, 3064}, {104, 104, 104, 255} }},
	{{ {-4879, 98, -2167}, 0, {-2637, 1237}, {54, 54, 54, 255} }},
	{{ {-5379, 346, -2167}, 0, {-8377, -1610}, {57, 57, 57, 255} }},
	{{ {-5379, 187, -2167}, 0, {-8377, 217}, {138, 138, 138, 255} }},
	{{ {-4879, 98, -2017}, 0, {-2637, 1237}, {55, 55, 55, 255} }},
	{{ {-4879, -61, -2017}, 0, {-2637, 3064}, {88, 88, 88, 255} }},
	{{ {-5379, 187, -2017}, 0, {-8377, 217}, {128, 128, 128, 255} }},
	{{ {-5379, 346, -2017}, 0, {-8377, -1610}, {62, 62, 62, 255} }},
	{{ {-5379, 346, -1967}, 0, {-8377, -1610}, {48, 48, 48, 255} }},
	{{ {-5379, 187, -1967}, 0, {-8377, 217}, {47, 47, 47, 255} }},
	{{ {-5550, 187, -1967}, 0, {-10350, 217}, {47, 47, 47, 255} }},
	{{ {-5550, 346, -1967}, 0, {-10350, -1610}, {76, 76, 76, 255} }},
	{{ {-5579, 187, -2017}, 0, {-2653, 217}, {85, 85, 85, 255} }},
	{{ {-5550, 346, -1967}, 0, {-3228, -1610}, {76, 76, 76, 255} }},
	{{ {-5550, 187, -1967}, 0, {-3228, 217}, {47, 47, 47, 255} }},
	{{ {-5579, 346, -2017}, 0, {-2653, -1610}, {52, 52, 52, 255} }},
	{{ {-5579, 187, -2167}, 0, {-930, 217}, {85, 85, 85, 255} }},
	{{ {-5579, 346, -2167}, 0, {-930, -1610}, {46, 46, 46, 255} }},
	{{ {-5550, 187, -2217}, 0, {-355, 217}, {70, 70, 70, 255} }},
	{{ {-5550, 346, -2217}, 0, {-355, -1610}, {61, 61, 61, 255} }},
	{{ {-5379, 346, -2017}, 0, {-2653, -1610}, {62, 62, 62, 255} }},
	{{ {-5379, 187, -2017}, 0, {-2653, 217}, {128, 128, 128, 255} }},
	{{ {-5379, 187, -1967}, 0, {-3228, 217}, {47, 47, 47, 255} }},
	{{ {-5379, 346, -1967}, 0, {-3228, -1610}, {48, 48, 48, 255} }},
	{{ {-5379, 187, -2217}, 0, {-8377, 217}, {46, 46, 46, 255} }},
	{{ {-5379, 346, -2217}, 0, {-8377, -1610}, {46, 46, 46, 255} }},
	{{ {-5550, 346, -2217}, 0, {-10350, -1610}, {61, 61, 61, 255} }},
	{{ {-5550, 187, -2217}, 0, {-10350, 217}, {70, 70, 70, 255} }},
	{{ {-5379, 187, -2167}, 0, {-930, 217}, {138, 138, 138, 255} }},
	{{ {-5379, 346, -2167}, 0, {-930, -1610}, {57, 57, 57, 255} }},
	{{ {-5379, 346, -2217}, 0, {-355, -1610}, {46, 46, 46, 255} }},
	{{ {-5379, 187, -2217}, 0, {-355, 217}, {46, 46, 46, 255} }},
	{{ {-4698, 469, -2530}, 0, {-558, -4668}, {0, 0, 0, 255} }},
	{{ {-3798, 469, -2530}, 0, {9785, -4668}, {0, 0, 0, 255} }},
	{{ {-3798, 469, -1630}, 0, {9785, 5671}, {1, 1, 1, 255} }},
	{{ {-4698, 469, -1630}, 0, {-558, 5671}, {0, 0, 0, 255} }},
};

Gfx hm_comp_dl_Geometry_005_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_1 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
	gsSP2Triangles(2, 4, 3, 0, 2, 5, 4, 0),
	gsSP2Triangles(2, 6, 5, 0, 5, 7, 4, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSP2Triangles(20, 23, 24, 0, 20, 24, 25, 0),
	gsSP2Triangles(24, 26, 25, 0, 25, 27, 20, 0),
	gsSP2Triangles(28, 29, 30, 0, 31, 28, 30, 0),
	gsSPVertex(hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_1 + 32, 31, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(1, 4, 3, 0, 1, 5, 4, 0),
	gsSP2Triangles(3, 4, 6, 0, 3, 6, 7, 0),
	gsSP2Triangles(2, 3, 7, 0, 2, 7, 8, 0),
	gsSP2Triangles(9, 2, 8, 0, 9, 8, 10, 0),
	gsSP2Triangles(11, 12, 13, 0, 11, 13, 14, 0),
	gsSP2Triangles(15, 16, 17, 0, 15, 17, 18, 0),
	gsSP2Triangles(19, 20, 21, 0, 22, 19, 21, 0),
	gsSP2Triangles(21, 23, 22, 0, 23, 24, 22, 0),
	gsSP2Triangles(23, 25, 24, 0, 23, 26, 25, 0),
	gsSP2Triangles(27, 28, 29, 0, 27, 29, 30, 0),
	gsSPVertex(hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_1 + 63, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
	gsSP2Triangles(4, 7, 4, 0, 8, 4, 4, 0),
	gsSP2Triangles(8, 4, 8, 0, 9, 8, 8, 0),
	gsSP2Triangles(9, 8, 9, 0, 7, 9, 9, 0),
	gsSP2Triangles(7, 9, 7, 0, 4, 7, 7, 0),
	gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
	gsSP2Triangles(13, 12, 14, 0, 14, 12, 15, 0),
	gsSP2Triangles(14, 15, 16, 0, 13, 14, 17, 0),
	gsSP2Triangles(13, 17, 18, 0, 13, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
	gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
	gsSPVertex(hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_1 + 95, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 5, 3, 0),
	gsSP2Triangles(5, 4, 6, 0, 5, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Vtx hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_2[4] = {
	{{ {-4879, -61, -2017}, 0, {2028, -5648}, {88, 88, 88, 255} }},
	{{ {-4879, -61, -2167}, 0, {-16, -5648}, {104, 104, 104, 255} }},
	{{ {-5379, 187, -2167}, 0, {-16, 6640}, {138, 138, 138, 255} }},
	{{ {-5379, 187, -2017}, 0, {2028, 6640}, {128, 128, 128, 255} }},
};

Gfx hm_comp_dl_Geometry_005_mesh_layer_Opaque_tri_2[] = {
	gsSPVertex(hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_2 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Vtx hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_3[8] = {
	{{ {-5379, 187, -2167}, 0, {2271, 23}, {138, 138, 138, 255} }},
	{{ {-5379, 187, -2217}, 0, {2271, -292}, {46, 46, 46, 255} }},
	{{ {-5550, 187, -2217}, 0, {105, -292}, {70, 70, 70, 255} }},
	{{ {-5379, 187, -2017}, 0, {2271, 969}, {128, 128, 128, 255} }},
	{{ {-5579, 187, -2017}, 0, {-255, 969}, {85, 85, 85, 255} }},
	{{ {-5579, 187, -2167}, 0, {-255, 23}, {85, 85, 85, 255} }},
	{{ {-5379, 187, -1967}, 0, {2271, 1284}, {47, 47, 47, 255} }},
	{{ {-5550, 187, -1967}, 0, {105, 1284}, {47, 47, 47, 255} }},
};

Gfx hm_comp_dl_Geometry_005_mesh_layer_Opaque_tri_3[] = {
	gsSPVertex(hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_3 + 0, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
	gsSP2Triangles(3, 2, 4, 0, 2, 5, 4, 0),
	gsSP2Triangles(4, 6, 3, 0, 4, 7, 6, 0),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_dl_ground_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 138, 219, 41, 255),
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

Gfx mat_hm_comp_dl_wall_mat_004_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_dl_Bmori1_sceneTex_015690_ci8_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 88),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_comp_dl_Bmori1_sceneTex_015690_ci8_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_dl_stairs_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_dl_Bmori1_room_22Tex_0015E0_ci8_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 83),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_comp_dl_Bmori1_room_22Tex_0015E0_ci8_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 8, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 124),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_dl_carpet_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_dl_ganontika_room_19Tex_006D40_rgba16_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 131),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_comp_dl_ganontika_room_19Tex_006D40_rgba16_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 8, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0),
	gsDPSetTileSize(0, 0, 0, 252, 124),
	gsSPEndDisplayList(),
};

Gfx hm_comp_dl_Geometry_005_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(hm_comp_dl_Geometry_005_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_hm_comp_dl_ground_mat_layerOpaque),
	gsSPDisplayList(hm_comp_dl_Geometry_005_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_hm_comp_dl_wall_mat_004_layerOpaque),
	gsSPDisplayList(hm_comp_dl_Geometry_005_mesh_layer_Opaque_tri_1),
	gsSPDisplayList(mat_hm_comp_dl_stairs_layerOpaque),
	gsSPDisplayList(hm_comp_dl_Geometry_005_mesh_layer_Opaque_tri_2),
	gsSPDisplayList(mat_hm_comp_dl_carpet_mat_layerOpaque),
	gsSPDisplayList(hm_comp_dl_Geometry_005_mesh_layer_Opaque_tri_3),
	gsSPEndDisplayList(),
};

