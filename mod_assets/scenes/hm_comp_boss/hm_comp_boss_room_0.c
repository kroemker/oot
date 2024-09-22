#include "hm_comp_boss_scene.h"


/**
 * Header Child Day (Default)
*/
#define LENGTH_HM_COMP_BOSS_ROOM_0_HEADER00_OBJECTLIST 1
SceneCmd hm_comp_boss_room_0_header00[] = {
    SCENE_CMD_ROOM_SHAPE(&hm_comp_boss_room_0_shapeHeader),
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
    SCENE_CMD_SKYBOX_DISABLES(false, false),
    SCENE_CMD_TIME_SETTINGS(255, 255, 10),
    SCENE_CMD_OBJECT_LIST(LENGTH_HM_COMP_BOSS_ROOM_0_HEADER00_OBJECTLIST, hm_comp_boss_room_0_header00_objectList),
    SCENE_CMD_END(),
};

s16 hm_comp_boss_room_0_header00_objectList[LENGTH_HM_COMP_BOSS_ROOM_0_HEADER00_OBJECTLIST] = {
    OBJECT_BDOOR,
};

RoomShapeNormal hm_comp_boss_room_0_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(hm_comp_boss_room_0_shapeDListsEntry),
    hm_comp_boss_room_0_shapeDListsEntry,
    hm_comp_boss_room_0_shapeDListsEntry + ARRAY_COUNT(hm_comp_boss_room_0_shapeDListsEntry)
};

RoomShapeDListsEntry hm_comp_boss_room_0_shapeDListsEntry[1] = {
    { hm_comp_boss_room_0_shapeHeader_entry_0_opaque, NULL }
};

Gfx hm_comp_boss_room_0_shapeHeader_entry_0_opaque[] = {
	gsSPDisplayList(hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

u64 hm_comp_boss_room_0_dl_HAKAdanCH_sceneTex_00B590_rgba16_ci8[] = {
	0x0001020304050406, 0x07080502090a0b0c, 0x0d0a0e0f02101108, 0x0400121301000014, 0x15160e171812191a, 0x1b1c0a0e161a1d1e, 0x1f20210c18222301, 0x1300021a24001a25, 
	0x0120241d0100021a, 0x261600201a1a1621, 0x16241d2016001127, 0x28161a141d1d2920, 0x2020200116001106, 0x1320000c0129001e, 0x251f1d0014010411, 0x2a0e000c202b1414, 
	0x211a201f14100516, 0x2c2914010c0c251e, 0x1420011614152d2e, 0x0e2b1401001a2920, 0x2f011a1d0208300e, 0x181d2f14000c2125, 0x18011d2002110431, 0x161f1d141a1f002f, 
	0x1d0120150f323307, 0x05291a001a140024, 0x1f1615200107112e, 0x3415000129010c20, 0x1607063232102213, 0x2535361c30340404, 0x11370201010f3216, 0x0f383906112b2023, 
	0x042a3a181a07131b, 0x0e141a021d1a0125, 0x13123b110f003c3d, 0x3b3e340805040505, 0x181a191a00160512, 0x020e161a1a1a0014, 0x2218200f3f181d16, 0x00020102070f1240, 
	0x022b100216010f07, 0x0312072b00041500, 0x1a0f0f401a1a0201, 0x1d16160f0e071c16, 0x02021a1a341f0101, 0x413119342a021a1a, 0x31370d0016420201, 0x001a1616082e0c25, 
	0x160e0f0200001416, 0x434116150533101d, 0x0d1013241d161a21, 0x16011a0e050a0f02, 0x001b140f000e1a29, 0x1a230144121f291d, 0x1f110518021a021a, 0x160f0206322e0102, 
	0x16142a1a430e0100, 0x2000073518161a2f, 0x1a0115410b160604, 0x080145123d023116, 0x2e1616020e161800, 0x0e180f26180e1825, 0x25000713461d1f0c, 0x1429244318141031, 
	0x430b310711021a0e, 0x0e0f2d411800141a, 0x0e042600021a1400, 0x012316141a140e0e, 0x1f0f1b330704042a, 0x1228183d02160116, 0x162c1d1e2947201d, 0x00001a2001200000, 
	0x024348491b00161a, 0x0101011d004a0013, 0x013d29201421210c, 0x291f4b2000162100, 0x110f490f43021a02, 0x02021d17000c211a, 0x2e1600021102230e, 0x21214b2114012900, 
	0x05490002011a1131, 0x000016001d131a1a, 0x0c0f4c1c3e173c14, 0x4d20202114151a16, 0x393d00101019001a, 0x0f1d001801131a1f, 0x0c233d0c20211d1d, 0x11234e0739081105, 
	0x084a1a194311231a, 0x1b31160c17161d00, 0x01344a0c212f4b2f, 0x002c2c281f1d1401, 0x4141180711160214, 0x021d251a16164311, 0x281d1a1d0f2f4f02, 0x084a21152b21201a, 
	0x1616110f08054107, 0x084e410208160b0c, 0x0e200c2902502d1a, 0x0c2e43061602292b, 0x07390f3a0b3b2627, 0x092e49101643181a, 0x114119122851461e, 0x01211a1f02230404, 
	0x1c18290e02001d1d, 0x001a011a28131602, 0x16520c2924212121, 0x1d0224532300522e, 0x1a150100000c2901, 0x0e161a0214143154, 0x4323282f1d214b14, 0x421e4b5520030342, 
	0x010214161d1d010e, 0x191a290014021918, 0x16130c1e471a201d, 0x4b252f4b2b0f0f19, 0x151b1a1e21140116, 0x1a1a20021a291d28, 0x02342c2915141f0c, 0x204b0c1e25110e0f, 
	0x0434151616181801, 0x1d161a2b16151a00, 0x1107181a1521201d, 0x011d1a0016184907, 0x41023707110f160e, 0x1923145604330508, 0x0001161a161a0002, 0x1601420743361354, 
	
};

u64 hm_comp_boss_room_0_dl_HAKAdanCH_sceneTex_00B590_rgba16_pal_rgba16[] = {
	0x5311428d320b3a8d, 0x114700c511071989, 0x09058d617c997459, 0x63935b95428f29cb, 0x2a0b218963d55b93, 0x424d3a0b3a4d5351, 0x5b5342cf4acf4ad1, 0x84db5b516bd34a8f, 
	0x4a8d52cf639529c9, 0x6353530f8d1f7cdb, 0x6bd55b11324d3a4b, 0x8d1d08c56c176351, 0x3a8f4b1100830907, 0x324b6c15956321cb, 0x214919496c198d21, 0x63d37c9b7417a5e9, 
	0x7499194731cb21c9, 0x8d5f63d784995b0f, 0x42d1535374576b93, 0x6bd729891987424b, 0x11058cdd851f6391, 0x320d73d531c90000
};

u64 hm_comp_boss_room_0_dl_HAKAdanCH_room_5Tex_002190_rgba16_ci8[] = {
	0x0001020103040506, 0x0701000809000500, 0x0a0b010c0d0d010a, 0x0e0f020108101112, 0x1314151616171307, 0x1813131319131a1b, 0x1c1a1d1e1f131304, 0x0f20212214171523, 
	0x00242501261c1d07, 0x0d141417271d271c, 0x251c251c1827280d, 0x0f292a1c250d0101, 0x1c0c25091c221406, 0x0f1913141c172713, 0x27171c1c2b271703, 0x012b170d17171c1c, 
	0x2c1c261b25171307, 0x1c0c252c27131a25, 0x1c0c1c1d2d1a170d, 0x101a142e1a2f252e, 0x14251c1417301507, 0x2f1a2b1313171c1a, 0x14171a1317171405, 0x0a170c2e0c051c27, 
	0x23151c14151c260a, 0x2a1327272817131a, 0x141427312727170d, 0x1017001715151713, 0x251c1c2505171a08, 0x322c251c2233172f, 0x3333310c012f2717, 0x101d0c0d00181727, 
	0x14171c2513272c01, 0x2d2b1418172f1c31, 0x2b192f172f181c1a, 0x152d010a0813130c, 0x2c231c172b302415, 0x0d192f000c1c3321, 0x2b1a2b2b171c041c, 0x00132e150c1c282f, 
	0x1c251723251c1715, 0x0d040d1d27313317, 0x33272d2a1a2d1a0c, 0x08190c1817012517, 0x0c1b141c17171d0d, 0x01272e1c272b2721, 0x1f2d2f0404170413, 0x151c232f3431271c, 
	0x1a2e131a142f311c, 0x0c19171a352f2721, 0x042e2f2f2f173113, 0x0d1417312b362b1d, 0x2b1c1c0c2f2b332c, 0x1837311f3331172a, 0x31170c171d2b3120, 0x0017312937382b31, 
	0x393a3b143c1f3d3e, 0x3f40414220202f43, 0x352b361f35423d3d, 0x101f3d1f44454443, 0x0b0a05080d001802, 0x0a000d0446474848, 0x0000180f0f020417, 0x0605080a080b1006, 
	0x490e0b000b0b260a, 0x4a0a0710094b4a49, 0x490a0509010f050d, 0x1832030c01010d0b, 0x0a2c4c0c14141d1c, 0x0d1c1330251c234a, 0x081933272b1d2825, 0x3317181a2d251b1a, 
	0x4b2d1c1c172e0118, 0x17041c271704170c, 0x012f131d272a0017, 0x2d1818171c250c15, 0x0b171c141c172318, 0x17141c142f181c25, 0x012717273104172f, 0x2e010c25171a1426, 
	0x002d0c0117171c17, 0x2f1d2f1c0d0c1b25, 0x02312f3314252704, 0x0c0d2f1a1c14010c, 0x00271815251c0127, 0x2f172f2b0c17270c, 0x0f2b2f2d04040418, 0x2f2f2d2f2f180d1c, 
	0x0a1725041417041d, 0x142f31041c2d1325, 0x0d1a2727172f2d2f, 0x2f2f2a171725182f, 0x06041c17171a272f, 0x1c1d041c342d2f0f, 0x082f1727042f1c17, 0x0417041818181727, 
	0x071327331404272b, 0x171815181c2b2117, 0x091304042f2a2731, 0x2b2a2f2f1c1c1c01, 0x10312f27172f1404, 0x2d2f13171c173117, 0x0d2d271d2d272f27, 0x2d041c1804041723, 
	0x0b131c142d31142d, 0x182e2b272b312f0c, 0x0a272d1c1c1c2f33, 0x040d251c1727171a, 0x09171c272b132733, 0x041d2719312a1c0c, 0x0a1f172f171a1717, 0x010c173327172f13, 
	0x001f1d14312b274d, 0x19132b272f172713, 0x0b33312a171a182d, 0x2f172d31272d311d, 0x08191727192b3135, 0x2a33332d2b2b4e27, 0x071f2b211f1d0c2d, 0x17174f2d2b1f2717, 
	0x05202b4244351f36, 0x352135212b384550, 0x0a39363535513536, 0x2d33203135311f35, 0x06010102473b2a35, 0x21312d2b3152210d, 0x49010f0d0f020905, 0x0d0d0009010f0205, 
	
};

u64 hm_comp_boss_room_0_dl_HAKAdanCH_room_5Tex_002190_rgba16_pal_rgba16[] = {
	0x2951421552994a99, 0x529b319108471089, 0x210f294f18cb210d, 0x421739d300054a57, 0x18cd084900035b63, 0x52df39d55ba552dd, 0x4a5963e7531f4a9d, 0x4a9b5b2163e96be9, 
	0x6c6f6c295ba33a15, 0x3a17425931935b61, 0x529d6c6b636163a5, 0x5321636342575b1f, 0x425b6be75add63a3, 0x63e56c2b6c6d74af, 0x746d6cb3642d63a7, 0x6cf76c716c2d6ba3, 
	0x75bb642b6cb16d39, 0x74f3757b5b1d631f, 0x5adb00010007108b, 0x4add746b746f6ba5, 0x635f74b16be50000
};

Vtx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-1973, -2811, 1984}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1973, 1546, 1984}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1973, 1546, -2407}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1973, -2811, -2407}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1973, -2811, 1984}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1973, 1546, 1984}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1973, 1546, -2407}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1973, -2811, -2407}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_0[35] = {
	{{ {1357, -120, -1367}, 0, {5112, -2570}, {133, 133, 133, 255} }},
	{{ {-1357, -120, -1367}, 0, {-4120, -2570}, {133, 133, 133, 255} }},
	{{ {-1357, -2811, -1367}, 0, {-4120, 6580}, {0, 0, 0, 255} }},
	{{ {1357, -2811, -1367}, 0, {5112, 6580}, {0, 0, 0, 255} }},
	{{ {1357, -120, 1367}, 0, {5112, 5904}, {133, 133, 133, 255} }},
	{{ {-1973, -120, 1984}, 0, {-6215, 8004}, {138, 138, 138, 255} }},
	{{ {1973, -120, 1984}, 0, {7206, 8004}, {133, 133, 133, 255} }},
	{{ {-1357, -120, 1367}, 0, {-4120, 5904}, {133, 133, 133, 255} }},
	{{ {-1973, -120, -1984}, 0, {-6215, -5493}, {133, 133, 133, 255} }},
	{{ {-1357, -120, -1367}, 0, {-4120, -3393}, {133, 133, 133, 255} }},
	{{ {1357, -120, -1367}, 0, {5112, -3393}, {133, 133, 133, 255} }},
	{{ {-56, -120, -1984}, 0, {306, -5493}, {201, 201, 201, 255} }},
	{{ {64, -120, -1984}, 0, {714, -5493}, {201, 201, 201, 255} }},
	{{ {1973, -120, -1984}, 0, {7206, -5493}, {133, 133, 133, 255} }},
	{{ {1357, -120, 1367}, 0, {5112, 5904}, {133, 133, 133, 255} }},
	{{ {64, -120, -2004}, 0, {714, -5561}, {201, 201, 201, 255} }},
	{{ {-56, -120, -2004}, 0, {306, -5561}, {201, 201, 201, 255} }},
	{{ {64, -120, -2407}, 0, {714, -6928}, {38, 38, 38, 255} }},
	{{ {-56, -120, -2407}, 0, {306, -6928}, {0, 0, 0, 255} }},
	{{ {-1357, -2811, 1367}, 0, {-4120, 5904}, {0, 0, 0, 255} }},
	{{ {1357, -2811, 1367}, 0, {5112, 5904}, {4, 4, 4, 255} }},
	{{ {1357, -2811, -1367}, 0, {5112, -3393}, {0, 0, 0, 255} }},
	{{ {-1357, -2811, -1367}, 0, {-4120, -3393}, {0, 0, 0, 255} }},
	{{ {-1357, -120, 1367}, 0, {-4120, -2570}, {133, 133, 133, 255} }},
	{{ {1357, -120, 1367}, 0, {5112, -2570}, {133, 133, 133, 255} }},
	{{ {1357, -2811, 1367}, 0, {5112, 6580}, {4, 4, 4, 255} }},
	{{ {-1357, -2811, 1367}, 0, {-4120, 6580}, {0, 0, 0, 255} }},
	{{ {1357, -120, 1367}, 0, {-5480, -2570}, {133, 133, 133, 255} }},
	{{ {1357, -120, -1367}, 0, {3817, -2570}, {133, 133, 133, 255} }},
	{{ {1357, -2811, -1367}, 0, {3817, 6580}, {0, 0, 0, 255} }},
	{{ {1357, -2811, 1367}, 0, {-5480, 6580}, {4, 4, 4, 255} }},
	{{ {-1357, -120, -1367}, 0, {3817, -2570}, {133, 133, 133, 255} }},
	{{ {-1357, -120, 1367}, 0, {-5480, -2570}, {133, 133, 133, 255} }},
	{{ {-1357, -2811, 1367}, 0, {-5480, 6580}, {0, 0, 0, 255} }},
	{{ {-1357, -2811, -1367}, 0, {3817, 6580}, {0, 0, 0, 255} }},
};

Gfx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_0 + 0, 31, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
	gsSP2Triangles(7, 8, 5, 0, 7, 9, 8, 0),
	gsSP2Triangles(8, 9, 10, 0, 11, 8, 10, 0),
	gsSP2Triangles(10, 12, 11, 0, 10, 13, 12, 0),
	gsSP2Triangles(10, 6, 13, 0, 10, 14, 6, 0),
	gsSP2Triangles(11, 12, 15, 0, 11, 15, 16, 0),
	gsSP2Triangles(16, 15, 17, 0, 16, 17, 18, 0),
	gsSP2Triangles(19, 20, 21, 0, 19, 21, 22, 0),
	gsSP2Triangles(23, 24, 25, 0, 23, 25, 26, 0),
	gsSP2Triangles(27, 28, 29, 0, 27, 29, 30, 0),
	gsSPVertex(hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_0 + 31, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Vtx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_1[42] = {
	{{ {-1973, -120, 1984}, 0, {-7729, 5599}, {138, 138, 138, 255} }},
	{{ {-1973, 1546, 1984}, 0, {-7729, -4839}, {133, 133, 133, 255} }},
	{{ {1973, 1546, 1984}, 0, {17000, -4839}, {133, 133, 133, 255} }},
	{{ {1973, -120, 1984}, 0, {17000, 5599}, {133, 133, 133, 255} }},
	{{ {1973, -120, 1984}, 0, {-16329, 5599}, {133, 133, 133, 255} }},
	{{ {1973, 1546, 1984}, 0, {-16329, -4839}, {133, 133, 133, 255} }},
	{{ {1973, 1546, -1984}, 0, {8539, -4839}, {134, 134, 134, 255} }},
	{{ {1973, -120, -1984}, 0, {8539, 5599}, {133, 133, 133, 255} }},
	{{ {-1973, -120, -1984}, 0, {8539, 5599}, {133, 133, 133, 255} }},
	{{ {-1973, 1546, -1984}, 0, {8539, -4839}, {133, 133, 133, 255} }},
	{{ {-1973, 1546, 1984}, 0, {-16329, -4839}, {133, 133, 133, 255} }},
	{{ {-1973, -120, 1984}, 0, {-16329, 5599}, {138, 138, 138, 255} }},
	{{ {64, -120, -1984}, 0, {5038, 5599}, {201, 201, 201, 255} }},
	{{ {1973, -120, -1984}, 0, {17000, 5599}, {133, 133, 133, 255} }},
	{{ {1973, 1546, -1984}, 0, {17000, -4839}, {134, 134, 134, 255} }},
	{{ {64, 40, -1984}, 0, {5038, 4596}, {201, 201, 201, 255} }},
	{{ {-57, 40, -1984}, 0, {4281, 4596}, {201, 201, 201, 255} }},
	{{ {-1973, -120, -1984}, 0, {-7729, 5599}, {133, 133, 133, 255} }},
	{{ {-1973, 1546, -1984}, 0, {-7729, -4839}, {133, 133, 133, 255} }},
	{{ {-56, -120, -1984}, 0, {4286, 5599}, {201, 201, 201, 255} }},
	{{ {64, -120, -2004}, 0, {8664, 5599}, {201, 201, 201, 255} }},
	{{ {64, 40, -2407}, 0, {11183, 4596}, {0, 0, 0, 255} }},
	{{ {64, -120, -2407}, 0, {11183, 5599}, {38, 38, 38, 255} }},
	{{ {64, 40, -2004}, 0, {8664, 4596}, {201, 201, 201, 255} }},
	{{ {64, -120, -1984}, 0, {8539, 5599}, {201, 201, 201, 255} }},
	{{ {64, 40, -1984}, 0, {8539, 4596}, {201, 201, 201, 255} }},
	{{ {-57, 40, -1984}, 0, {8539, 4596}, {201, 201, 201, 255} }},
	{{ {-56, -120, -1984}, 0, {8539, 5599}, {201, 201, 201, 255} }},
	{{ {-56, -120, -2004}, 0, {8664, 5599}, {201, 201, 201, 255} }},
	{{ {-57, 40, -2004}, 0, {8664, 4596}, {202, 202, 202, 255} }},
	{{ {-56, -120, -2407}, 0, {11183, 5599}, {0, 0, 0, 255} }},
	{{ {-57, 40, -2407}, 0, {11183, 4596}, {0, 0, 0, 255} }},
	{{ {64, 40, -1984}, 0, {5038, -381}, {201, 201, 201, 255} }},
	{{ {-57, 40, -1984}, 0, {4281, -381}, {201, 201, 201, 255} }},
	{{ {-57, 40, -2004}, 0, {4281, -506}, {202, 202, 202, 255} }},
	{{ {64, 40, -2004}, 0, {5038, -506}, {201, 201, 201, 255} }},
	{{ {-57, 40, -2407}, 0, {4281, -3026}, {0, 0, 0, 255} }},
	{{ {64, 40, -2407}, 0, {5038, -3026}, {0, 0, 0, 255} }},
	{{ {64, -120, -2407}, 0, {5038, 5599}, {38, 38, 38, 255} }},
	{{ {64, 40, -2407}, 0, {5038, 4596}, {0, 0, 0, 255} }},
	{{ {-57, 40, -2407}, 0, {4281, 4596}, {0, 0, 0, 255} }},
	{{ {-56, -120, -2407}, 0, {4286, 5599}, {0, 0, 0, 255} }},
};

Gfx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_1 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 15, 12, 14, 0),
	gsSP2Triangles(14, 16, 15, 0, 14, 17, 16, 0),
	gsSP2Triangles(14, 18, 17, 0, 17, 19, 16, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 23, 21, 0),
	gsSP2Triangles(24, 23, 20, 0, 24, 25, 23, 0),
	gsSP2Triangles(26, 27, 28, 0, 26, 28, 29, 0),
	gsSP2Triangles(29, 28, 30, 0, 29, 30, 31, 0),
	gsSPVertex(hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_1 + 32, 10, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_boss_room_0_dl_floor_mat_layerOpaque[] = {
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_boss_room_0_dl_HAKAdanCH_sceneTex_00B590_rgba16_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 86),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_comp_boss_room_0_dl_HAKAdanCH_sceneTex_00B590_rgba16_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_boss_room_0_dl_wall_mat_layerOpaque[] = {
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_boss_room_0_dl_HAKAdanCH_room_5Tex_002190_rgba16_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 82),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_comp_boss_room_0_dl_HAKAdanCH_room_5Tex_002190_rgba16_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_hm_comp_boss_room_0_dl_floor_mat_layerOpaque),
	gsSPDisplayList(hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_hm_comp_boss_room_0_dl_wall_mat_layerOpaque),
	gsSPDisplayList(hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_tri_1),
	gsSPEndDisplayList(),
};

