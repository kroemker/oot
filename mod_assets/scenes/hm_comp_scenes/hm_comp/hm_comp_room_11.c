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
#define LENGTH_HM_COMP_ROOM_11_HEADER00_OBJECTLIST 1
#define LENGTH_HM_COMP_ROOM_11_HEADER00_ACTORLIST 9
SceneCmd hm_comp_room_11_header00[] = {
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
    SCENE_CMD_SKYBOX_DISABLES(true, true),
    SCENE_CMD_TIME_SETTINGS(0xFF, 0xFF, 0),
    SCENE_CMD_ROOM_SHAPE(&hm_comp_room_11_shapeHeader),
    SCENE_CMD_OBJECT_LIST(LENGTH_HM_COMP_ROOM_11_HEADER00_OBJECTLIST, hm_comp_room_11_header00_objectList),
    SCENE_CMD_ACTOR_LIST(LENGTH_HM_COMP_ROOM_11_HEADER00_ACTORLIST, hm_comp_room_11_header00_actorList),
    SCENE_CMD_END(),
};

s16 hm_comp_room_11_header00_objectList[LENGTH_HM_COMP_ROOM_11_HEADER00_OBJECTLIST] = {
    OBJECT_BOX,
};

ActorEntry hm_comp_room_11_header00_actorList[LENGTH_HM_COMP_ROOM_11_HEADER00_ACTORLIST] = {
    // Treasure Chest
    {
        /* Actor ID   */ ACTOR_EN_BOX,
        /* Position   */ { 3669, -58, 670 },
        /* Rotation   */ { 0, 0, 19 },
        /* Parameters */ 0xBB22
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 3317, -58, 670 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x9300
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 3317, -58, 750 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x9300
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 3477, -58, 750 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x9300
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 3477, -58, 590 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x9300
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 3477, -58, 670 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x9300
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 3397, -58, 750 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x9300
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 3397, -58, 590 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x9300
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 3317, -58, 590 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x9300
    },
};

RoomShapeNormal hm_comp_room_11_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(hm_comp_room_11_shapeDListEntry),
    hm_comp_room_11_shapeDListEntry,
    hm_comp_room_11_shapeDListEntry + ARRAY_COUNT(hm_comp_room_11_shapeDListEntry)
};

RoomShapeDListsEntry hm_comp_room_11_shapeDListEntry[1] = {
    { hm_comp_room_11_entry_0_opaque, NULL },
};

Gfx hm_comp_room_11_entry_0_opaque[] = {
	gsSPDisplayList(hm_comp_dl_Plane_008_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

u64 hm_comp_dl_jyasinzou_room_25Tex_010798_ci8_ci8[] = {
	0x0001020103040506, 0x070708090a020b0c, 0x020d0b0c0c0b0e0b, 0x010f0f0d100d1112, 0x1302141514161602, 0x0217181716191515, 0x1a19161716161814, 0x1a1a1b09081c1d13, 
	0x0a1918191617170c, 0x1e16161f16191515, 0x2019161616160218, 0x021d212221232424, 0x11160f161a1a031a, 0x14190a171716161a, 0x1419191613182523, 0x262728292a2b292c, 
	0x0b16171619021919, 0x1a1a1a18160a1619, 0x171d2014202d2e2f, 0x303132333435362c, 0x371f1e1602180219, 0x181a1a1919141a1a, 0x1338393a3b3b3c3d, 0x3e2b28313f3f2838, 
	0x0c161e161918161e, 0x18171a2020151504, 0x3840304139424344, 0x45463f4727482124, 0x1d1919191a021949, 0x170a191503042423, 0x3b454a344b283b27, 0x3b4c4c2206242523, 
	0x381a1a1519171749, 0x1719151505244027, 0x4d464e4e2f282321, 0x2626264f50212251, 0x0b16171815191917, 0x191a080423524553, 0x545556273b574c57, 0x04044f2458514f59, 
	0x0f171e1f49155a15, 0x151521213f3d5b5c, 0x2754274c4c5d5e4c, 0x5821574f21064f4c, 0x031a181817191a15, 0x07064c3f283d5b2b, 0x275f2151504f5740, 0x435106585860615d, 
	0x110a021918171915, 0x05242943622e3227, 0x265e4f224f213963, 0x64265d4c4f4f6051, 0x651702181702044c, 0x04473d4a663b6722, 0x584f5068694f5145, 0x3557584f4f680623, 
	0x02181a141a191a1d, 0x243f2f666a282251, 0x696b615d684f0606, 0x6c4f4f4c61614c25, 0x100c16152020144c, 0x2430464256675861, 0x6060604f4f6d6d4c, 0x4f2321584f064c6e, 
	0x0116161618020e04, 0x296f3d312d5d4f50, 0x50584f58614f616c, 0x5870714c4c062572, 0x131a171618052473, 0x432f622d274f6061, 0x584c60584f4f604f, 0x24357458064c2864, 
	0x0f160a0b043f293d, 0x3d62272d584f504c, 0x2124572106064f4f, 0x4f585d5858214375, 0x1b16170b04243c5b, 0x4a3b274f065d684f, 0x5824767047246c06, 0x6c6c06066c454175, 
	0x19771a1423235278, 0x312d692258064c22, 0x604c29347973384c, 0x4f506850565c7a7b, 0x0c17141d47447c56, 0x3a674f5858512158, 0x5706067c337d7e7f, 0x7124478081797582, 
	0x16160b04666f3e28, 0x3f50585d43838021, 0x4c24222431798284, 0x7d857f3e8687757b, 0x0a1903243d4a3e38, 0x57614f2483883f4f, 0x066c4f4f473b8889, 0x847e85858275758a, 
	0x1819065640444457, 0x5e604f040e25068b, 0x4c4c4c4c0647318c, 0x82847d878d898e8f, 0x1a1a2121273b2422, 0x58504f57064f0658, 0x4c2357584c583a44, 0x87758475757b9091, 
	0x021a296a3e3a2458, 0x4f585d5821686c58, 0x9283394c23255192, 0x93758594827b8789, 0x1009954a96342450, 0x68224f4f68065d06, 0x1339472251060680, 0x647d7d7b7a8f757b, 
	0x161a977474975122, 0x4f4f4f4f60684f4c, 0x51065d4f064c3f71, 0x948d878d89878789, 0x0c1d3f4062982206, 0x584c50584c5d684f, 0x2258584c063f998e, 0x8d8d9a87907a7b87, 
	0x371b356a45285704, 0x605d4f4f4f6c6168, 0x686c4f5840799b8d, 0x8d8c7d877a877b7b, 0x651d704335970559, 0x044c254c214c044c, 0x240e472c347b7b75, 0x7a9c9d8f8f9e7a7a, 
	
};

u64 hm_comp_dl_jyasinzou_room_25Tex_010798_ci8_pal_rgba16[] = {
	0x83937b557315628f, 0x5a4d4a4d4189398b, 0x420d5acf62d78bd9, 0x83db945b6acf8397, 0x93db9c198bd37b13, 0x4a4f39cf6b5952d7, 0x5a95529542116ad1, 0x3a0d528f739d7bdf, 
	0x318d5149494761c9, 0x620b528b51876207, 0x7a898b0bac09b40d, 0x938f61c783479307, 0x938983098249ac0f, 0xb40f934d8a89b49b, 0x72cf830d720b6a07, 0x9b87c449bb8b7289, 
	0x824bab4982059b8f, 0xabcd934b8a876a8d, 0x5a874a97cc8bbbd1, 0x49cb4a03bc493947, 0x39054a496ac7928d, 0x518571c56a094a07, 0x418761cb2151cc89, 0xb34b410741054a05, 
	0x30c529057a49ccd1, 0xbc919c5bb3c94945, 0x31873145bccb28c3, 0x398921038351d4c7, 0xac118bcdac138b0f, 0xb411dd9393cf314b, 0x9b47cc4fbd95d5d5, 0x8a8bd4d1d40fbb8d, 
	0x6b0bab4be5d3c495, 0xe4d1d48fd451e615, 0xc453cd93bd533149, 0xd551ed93cc95b591, 0xd613de139bd3cc91, 0xccd39c0dd4cd7a8d, 0x69c9b3cddc93dc51, 0xac97b495b4d30000
};

u64 hm_comp_dl_jyasinzou_room_25Tex_010398_ci8_ci8[] = {
	0x0001000200030000, 0x0002000200000404, 0x0005060501070200, 0x0800070002080909, 0x0a0b0c0a080a0a0b, 0x0b0a0d0a0a070e00, 0x08000008070b010b, 0x0a070d0b0c0c0f09, 
	0x040a0c0c010b0101, 0x0c010a010c0c0b0a, 0x0a010a0a04070a0c, 0x0c0c100d0b0b1112, 0x03000a010a010b07, 0x00060d0b0a00060d, 0x0b0a0c0a0c0c010a, 0x010c0b010b040f09, 
	0x000b000202040b00, 0x08070a01070d000a, 0x010c010c0f0c0a02, 0x080a080600020111, 0x0a0c0b070204080a, 0x010b130b0c0a0110, 0x070e0a0c0c08000a, 0x0000000400081012, 
	0x080e010c0206000d, 0x0b100d0a0d0b100d, 0x010b0a0c0c000001, 0x070a0800070a0c09, 0x0b070a0c0b010101, 0x0b0a080a01010a08, 0x0a010f0914070e01, 0x0a0d07080a020c0c, 
	0x000a0a010b01100c, 0x0a00040a0b070802, 0x0c0c150c100d0b00, 0x08080008070a0f09, 0x000c0b00080c0c0c, 0x0c0c0c0f0c0c0c0c, 0x12160f0c0b0b0a0a, 0x070b08060d0c0f17, 
	0x0c0c010c0b100c09, 0x151516120f121819, 0x16090f0c01080b01, 0x0b0c0b0c10140c12, 0x0a07080a0b0c0c09, 0x0f12121209091215, 0x1a0f0c0c0c0b0a01, 0x130a0a0b0a081b0f, 
	0x02080b01010b0c0f, 0x1c12120918111212, 0x12121d180c0c0c0a, 0x0b0c0c0b0d070b11, 0x000b0c0c0c0c0f0b, 0x1212120c0b0b0a0a, 0x0b0a040a0a070a0d, 0x0f0f0c0c0c0b0c18, 
	0x0b010b010b0c0909, 0x1512120a04040808, 0x0d0d0a0a0d0b0c0f, 0x0f09090f0f0f1211, 0x010a0b0c0c0f0f09, 0x0915160c0b0c0c0c, 0x100c0909111e1215, 0x1f0918091c0f1715, 
	0x180b080b010c0f09, 0x091512121218121d, 0x0919161512121d11, 0x0f0c0c0c0f091217, 0x110f0b100c0f1c09, 0x100f180912090912, 0x1519150f070b070a, 0x0c0b0b0b0c200909, 
	0x0f1519120909090c, 0x0a080b0c0c0c0c0b, 0x0b0f110807010c1e, 0x160c010b0c0f0909, 0x0c0f091209181120, 0x0c0c0c0c0c0b0704, 0x00010c0202040c09, 0x1a010a0b1e091815, 
	0x010a0c0c1e0c120c, 0x0c0c0f0c180c0c0c, 0x0c0c0c00010b0c09, 0x0918111e111d1717, 0x0b010c0c0b0f150c, 0x09090f09110c0c09, 0x0f12120f110f0f0f, 0x210c0b0c0f11121a, 
	0x070c0b0d0b090901, 0x0b020a110f0c0c0c, 0x0c120c0a0c010f09, 0x0c07000c0c0b091e, 0x0c0c010b0c09090b, 0x0b070b0f0c0e070e, 0x0c120c0c0c0c1109, 0x18090f11200f090c, 
	0x0c0b0b0101091211, 0x0c0c0c0c0f100c0b, 0x0c150c0909091811, 0x010a111222090c0f, 0x030107070a0f120f, 0x090f0f0c090c0909, 0x09090b23000a120f, 0x00040e0a0f010c0f, 
	0x070b0e02080c110c, 0x0a0d0c09120c0c0b, 0x0b090202000c1211, 0x0b0c0b090c0c0c11, 0x0001070b0c0f0f0c, 0x020a0a18090f0a0c, 0x0909000b0a0c1212, 0x0b0c0c0f0f1d0c0b, 
	0x02000a110c0f090c, 0x0b080721180c0e0b, 0x0909070b0c090f0f, 0x11100f1d1d090f0f, 0x0002090f1811090f, 0x040a0c1211090a07, 0x12180d0c0c09200c, 0x1d1517090f0f1112, 
	0x07040b0d0f0b1114, 0x0c0b0f12120f0915, 0x1212150c0909090f, 0x0f111e0b0c010b0e, 0x0b07060311091811, 0x0c0c090c0c0c010c, 0x0a0c1e0f0c0c010c, 0x080b08000000070c, 
	
};

u64 hm_comp_dl_jyasinzou_room_25Tex_010398_ci8_pal_rgba16[] = {
	0x824b6a098a8b934b, 0x82498a898a4b7a0b, 0x7a494947720b620b, 0x61c972897a895149, 0x61cb5187410769c9, 0x4a49394731873905, 0x418930c549075947, 0x4a07418759492905, 
	0x49cb61c741058a4d, 
};

Vtx hm_comp_dl_Plane_008_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {3031, -58, 1016}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {3031, 281, 1016}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {3031, 281, 325}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {3031, -58, 325}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {3742, -58, 1016}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {3742, 281, 1016}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {3742, 281, 325}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {3742, -58, 325}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx hm_comp_dl_Plane_008_mesh_layer_Opaque_vtx_0[12] = {
	{{ {3205, -58, 862}, 0, {2032, 2032}, {255, 255, 255, 255} }},
	{{ {3589, -58, 862}, 0, {2032, -16}, {255, 255, 255, 255} }},
	{{ {3589, -58, 478}, 0, {-16, -16}, {255, 255, 255, 255} }},
	{{ {3205, -58, 478}, 0, {-16, 2032}, {255, 255, 255, 255} }},
	{{ {3051, -58, 641}, 0, {-16, 542}, {134, 134, 134, 255} }},
	{{ {3051, 42, 641}, 0, {-16, 542}, {134, 134, 134, 255} }},
	{{ {3031, 42, 641}, 0, {-16, 542}, {255, 255, 255, 255} }},
	{{ {3031, 42, 701}, 0, {-16, 631}, {255, 255, 255, 255} }},
	{{ {3051, 42, 701}, 0, {-16, 541}, {134, 134, 134, 255} }},
	{{ {3031, -58, 701}, 0, {-16, 631}, {164, 164, 164, 255} }},
	{{ {3051, -58, 701}, 0, {-16, 541}, {134, 134, 134, 255} }},
	{{ {3031, -58, 641}, 0, {-16, 542}, {252, 252, 252, 255} }},
};

Gfx hm_comp_dl_Plane_008_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(hm_comp_dl_Plane_008_mesh_layer_Opaque_vtx_0 + 0, 12, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
	gsSP2Triangles(5, 8, 7, 0, 8, 9, 7, 0),
	gsSP2Triangles(8, 10, 9, 0, 10, 11, 9, 0),
	gsSP2Triangles(10, 4, 11, 0, 4, 6, 11, 0),
	gsSPEndDisplayList(),
};

Vtx hm_comp_dl_Plane_008_mesh_layer_Opaque_vtx_1[20] = {
	{{ {3742, -58, 325}, 0, {8176, 4863}, {134, 134, 134, 255} }},
	{{ {3051, 281, 325}, 0, {-6160, -2174}, {7, 7, 7, 255} }},
	{{ {3051, -58, 325}, 0, {-6160, 4863}, {134, 134, 134, 255} }},
	{{ {3742, 281, 325}, 0, {8176, -2174}, {0, 0, 0, 255} }},
	{{ {3742, 281, 1016}, 0, {-6160, -2174}, {8, 8, 8, 255} }},
	{{ {3051, 281, 1016}, 0, {-6160, -2174}, {0, 0, 0, 255} }},
	{{ {3051, -58, 1016}, 0, {-6160, 4863}, {134, 134, 134, 255} }},
	{{ {3742, 281, 1016}, 0, {8176, -2174}, {8, 8, 8, 255} }},
	{{ {3742, -58, 1016}, 0, {8176, 4863}, {134, 134, 134, 255} }},
	{{ {3742, -58, 1016}, 0, {-6160, 4863}, {134, 134, 134, 255} }},
	{{ {3742, 281, 325}, 0, {8176, -2174}, {0, 0, 0, 255} }},
	{{ {3742, -58, 325}, 0, {8176, 4863}, {134, 134, 134, 255} }},
	{{ {3051, -58, 641}, 0, {1626, 4863}, {134, 134, 134, 255} }},
	{{ {3051, -58, 325}, 0, {8176, 4863}, {134, 134, 134, 255} }},
	{{ {3051, 281, 325}, 0, {8176, -2174}, {7, 7, 7, 255} }},
	{{ {3051, 42, 641}, 0, {1626, 2787}, {134, 134, 134, 255} }},
	{{ {3051, 42, 701}, 0, {380, 2787}, {134, 134, 134, 255} }},
	{{ {3051, -58, 1016}, 0, {-6160, 4863}, {134, 134, 134, 255} }},
	{{ {3051, 281, 1016}, 0, {-6160, -2174}, {0, 0, 0, 255} }},
	{{ {3051, -58, 701}, 0, {380, 4863}, {134, 134, 134, 255} }},
};

Gfx hm_comp_dl_Plane_008_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(hm_comp_dl_Plane_008_mesh_layer_Opaque_vtx_1 + 0, 20, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(1, 3, 4, 0, 1, 4, 5, 0),
	gsSP2Triangles(6, 5, 7, 0, 6, 7, 8, 0),
	gsSP2Triangles(9, 4, 10, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 15, 12, 14, 0),
	gsSP2Triangles(14, 16, 15, 0, 14, 17, 16, 0),
	gsSP2Triangles(14, 18, 17, 0, 17, 19, 16, 0),
	gsSPEndDisplayList(),
};

Vtx hm_comp_dl_Plane_008_mesh_layer_Opaque_vtx_2[10] = {
	{{ {3589, -58, 862}, 0, {1920, 2396}, {255, 255, 255, 255} }},
	{{ {3205, -58, 862}, 0, {-928, 2396}, {255, 255, 255, 255} }},
	{{ {3051, -58, 1016}, 0, {-2064, 3532}, {134, 134, 134, 255} }},
	{{ {3205, -58, 478}, 0, {-928, -452}, {255, 255, 255, 255} }},
	{{ {3051, -58, 701}, 0, {-2064, 1197}, {134, 134, 134, 255} }},
	{{ {3051, -58, 641}, 0, {-2064, 752}, {134, 134, 134, 255} }},
	{{ {3051, -58, 325}, 0, {-2064, -1588}, {134, 134, 134, 255} }},
	{{ {3742, -58, 325}, 0, {3056, -1588}, {134, 134, 134, 255} }},
	{{ {3589, -58, 478}, 0, {1920, -452}, {255, 255, 255, 255} }},
	{{ {3742, -58, 1016}, 0, {3056, 3532}, {134, 134, 134, 255} }},
};

Gfx hm_comp_dl_Plane_008_mesh_layer_Opaque_tri_2[] = {
	gsSPVertex(hm_comp_dl_Plane_008_mesh_layer_Opaque_vtx_2 + 0, 10, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
	gsSP2Triangles(4, 2, 3, 0, 3, 5, 4, 0),
	gsSP2Triangles(3, 6, 5, 0, 3, 7, 6, 0),
	gsSP2Triangles(3, 8, 7, 0, 8, 9, 7, 0),
	gsSP2Triangles(8, 0, 9, 0, 0, 2, 9, 0),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_dl_mosaic_mat_001_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_dl_jyasinzou_room_25Tex_010798_ci8_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 158),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_comp_dl_jyasinzou_room_25Tex_010798_ci8_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_dl_wall_mat_010_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
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

Gfx mat_hm_comp_dl_floor_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_dl_jyasinzou_room_25Tex_010398_ci8_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 35),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_comp_dl_jyasinzou_room_25Tex_010398_ci8_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx hm_comp_dl_Plane_008_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(hm_comp_dl_Plane_008_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_hm_comp_dl_mosaic_mat_001_layerOpaque),
	gsSPDisplayList(hm_comp_dl_Plane_008_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_hm_comp_dl_wall_mat_010_layerOpaque),
	gsSPDisplayList(hm_comp_dl_Plane_008_mesh_layer_Opaque_tri_1),
	gsSPDisplayList(mat_hm_comp_dl_floor_mat_layerOpaque),
	gsSPDisplayList(hm_comp_dl_Plane_008_mesh_layer_Opaque_tri_2),
	gsSPEndDisplayList(),
};

