#include <ultra64.h>
#include <z64.h>
#include "jyasinboss_room_0.h"
#include <z64.h>
#include <segment_symbols.h>
#include <command_macros_base.h>
#include <z64cutscene_commands.h>
#include <variables.h>
#include "jyasinboss_scene.h"



SCmdAltHeaders _jyasinboss_room_0_set0000_cmd00 = { 0x18, 0, (u32)&_jyasinboss_room_0_alternateHeaders_00000040}; // 0x0000
SCmdEchoSettings _jyasinboss_room_0_set0000_cmd01 = { 0x16, 0, { 0 }, 0x00 }; // 0x0008
SCmdRoomBehavior _jyasinboss_room_0_set0000_cmd02 = { 0x08, 0x01, 0x00000000 }; // 0x0010
SCmdSkyboxDisables _jyasinboss_room_0_set0000_cmd03 = { 0x12, 0, 0, 0, 0x01, 0x01 }; // 0x0018
SCmdTimeSettings _jyasinboss_room_0_set0000_cmd04 = { 0x10, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00 }; // 0x0020
SCmdMesh _jyasinboss_room_0_set0000_cmd05 = { 0x0A, 0, (u32)&_jyasinboss_room_0_meshHeader_00000060 }; // 0x0028
SCmdObjectList _jyasinboss_room_0_set0000_cmd06 = { 0x0B, 0x02, (u32)_jyasinboss_room_0_objectList_00000058 }; // 0x0030
SCmdEndMarker _jyasinboss_room_0_set0000_cmd07 = { 0x14, 0x00, 0x00 }; // 0x0038
u32 _jyasinboss_room_0_alternateHeaders_00000040[] = 
{
	0,
	0,
	0,
	(u32)&_jyasinboss_room_0_set0080_cmd00,
	(u32)&_jyasinboss_room_0_set00C0_cmd00,
	(u32)&_jyasinboss_room_0_set0100_cmd00,
};

s16 _jyasinboss_room_0_objectList_00000058[] = 
{
	OBJECT_JYA_DOOR,
	OBJECT_BDOOR,
};

static u8 unaccounted005C[] = 
{
	0x00, 0x00, 0x00, 0x00, 
};

MeshHeader0 _jyasinboss_room_0_meshHeader_00000060 = { { 0 }, 0x01, (u32)&_jyasinboss_room_0_meshDListEntry_0000006C, (u32)&(_jyasinboss_room_0_meshDListEntry_0000006C) + sizeof(_jyasinboss_room_0_meshDListEntry_0000006C) };

MeshEntry0 _jyasinboss_room_0_meshDListEntry_0000006C[1] = 
{
	{ (u32)_jyasinboss_room_0_dlist_000007B0, 0 },
};

static u32 terminatorMaybe = 0x01000000; // This always appears after the mesh entries. Its purpose is not clear.
static u32 pad78 = 0;
static u32 pad7C = 0;

SCmdEchoSettings _jyasinboss_room_0_set0080_cmd00 = { 0x16, 0, { 0 }, 0x00 }; // 0x0080
SCmdRoomBehavior _jyasinboss_room_0_set0080_cmd01 = { 0x08, 0x01, 0x00000000 }; // 0x0088
SCmdSkyboxDisables _jyasinboss_room_0_set0080_cmd02 = { 0x12, 0, 0, 0, 0x01, 0x01 }; // 0x0090
SCmdTimeSettings _jyasinboss_room_0_set0080_cmd03 = { 0x10, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00 }; // 0x0098
SCmdMesh _jyasinboss_room_0_set0080_cmd04 = { 0x0A, 0, (u32)&_jyasinboss_room_0_meshHeader_00000060 }; // 0x00A0
SCmdObjectList _jyasinboss_room_0_set0080_cmd05 = { 0x0B, 0x01, (u32)_jyasinboss_room_0_objectList_000000B8 }; // 0x00A8
SCmdEndMarker _jyasinboss_room_0_set0080_cmd06 = { 0x14, 0x00, 0x00 }; // 0x00B0
s16 _jyasinboss_room_0_objectList_000000B8[] = 
{
	OBJECT_JYA_DOOR,
};

static u8 unaccounted00BC[] = 
{
	0x00, 0x00, 0x00, 0x00, 
};

SCmdEchoSettings _jyasinboss_room_0_set00C0_cmd00 = { 0x16, 0, { 0 }, 0x00 }; // 0x00C0
SCmdRoomBehavior _jyasinboss_room_0_set00C0_cmd01 = { 0x08, 0x01, 0x00000000 }; // 0x00C8
SCmdSkyboxDisables _jyasinboss_room_0_set00C0_cmd02 = { 0x12, 0, 0, 0, 0x01, 0x01 }; // 0x00D0
SCmdTimeSettings _jyasinboss_room_0_set00C0_cmd03 = { 0x10, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00 }; // 0x00D8
SCmdMesh _jyasinboss_room_0_set00C0_cmd04 = { 0x0A, 0, (u32)&_jyasinboss_room_0_meshHeader_00000060 }; // 0x00E0
SCmdObjectList _jyasinboss_room_0_set00C0_cmd05 = { 0x0B, 0x01, (u32)_jyasinboss_room_0_objectList_000000F8 }; // 0x00E8
SCmdEndMarker _jyasinboss_room_0_set00C0_cmd06 = { 0x14, 0x00, 0x00 }; // 0x00F0
s16 _jyasinboss_room_0_objectList_000000F8[] = 
{
	OBJECT_JYA_DOOR,
};

static u8 unaccounted00FC[] = 
{
	0x00, 0x00, 0x00, 0x00, 
};

SCmdEchoSettings _jyasinboss_room_0_set0100_cmd00 = { 0x16, 0, { 0 }, 0x00 }; // 0x0100
SCmdRoomBehavior _jyasinboss_room_0_set0100_cmd01 = { 0x08, 0x00, 0x00000000 }; // 0x0108
SCmdSkyboxDisables _jyasinboss_room_0_set0100_cmd02 = { 0x12, 0, 0, 0, 0x01, 0x01 }; // 0x0110
SCmdTimeSettings _jyasinboss_room_0_set0100_cmd03 = { 0x10, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00 }; // 0x0118
SCmdMesh _jyasinboss_room_0_set0100_cmd04 = { 0x0A, 0, (u32)&_jyasinboss_room_0_meshHeader_00000060 }; // 0x0120
SCmdObjectList _jyasinboss_room_0_set0100_cmd05 = { 0x0B, 0x02, (u32)_jyasinboss_room_0_objectList_00000138 }; // 0x0128
SCmdEndMarker _jyasinboss_room_0_set0100_cmd06 = { 0x14, 0x00, 0x00 }; // 0x0130
s16 _jyasinboss_room_0_objectList_00000138[] = 
{
	OBJECT_JYA_DOOR,
	OBJECT_BDOOR,
};

static u32 align13C = 0;
Vtx_t _jyasinboss_room_0_vertices_00000140[28] = 
{
	 { -1914, 72, 1954, 0, 2687, 998, 69, 62, 48, 255 }, // 0x00000140
	 { -1864, 72, 1904, 0, 2595, -113, 134, 119, 89, 255 }, // 0x00000150
	 { -1884, 60, 1884, 0, 3584, -124, 134, 119, 89, 255 }, // 0x00000160
	 { -1934, 60, 1934, 0, 3584, 988, 69, 62, 48, 255 }, // 0x00000170
	 { -1904, 72, 1864, 0, 4573, -113, 134, 119, 89, 255 }, // 0x00000180
	 { -1954, 72, 1914, 0, 4481, 998, 69, 62, 48, 255 }, // 0x00000190
	 { -1861, 34, 1787, 0, 4436, -1452, 81, 72, 55, 255 }, // 0x000001A0
	 { -1843, 14, 1805, 0, 3962, -1470, 134, 119, 89, 255 }, // 0x000001B0
	 { -1901, 100, 1845, 0, 5521, -320, 100, 89, 67, 255 }, // 0x000001C0
	 { -1866, 136, 1782, 0, 6108, -1360, 55, 37, 18, 255 }, // 0x000001D0
	 { -1861, 34, 1787, 0, 4436, -1452, 100, 89, 67, 255 }, // 0x000001E0
	 { -1882, 128, 1842, 0, 6381, -540, 55, 37, 18, 255 }, // 0x000001F0
	 { -1835, 160, 1807, 0, 6847, -1397, 55, 37, 18, 255 }, // 0x00000200
	 { -1849, 140, 1849, 0, 7168, -796, 55, 37, 18, 255 }, // 0x00000210
	 { -1842, 128, 1882, 0, 787, -540, 55, 37, 18, 255 }, // 0x00000220
	 { -1807, 160, 1835, 0, 321, -1397, 55, 37, 18, 255 }, // 0x00000230
	 { -1782, 136, 1866, 0, 1060, -1360, 55, 37, 18, 255 }, // 0x00000240
	 { -1849, 140, 1849, 0, 0, -796, 55, 37, 18, 255 }, // 0x00000250
	 { -1845, 100, 1901, 0, 1647, -320, 100, 89, 67, 255 }, // 0x00000260
	 { -1787, 34, 1861, 0, 2732, -1452, 81, 72, 55, 255 }, // 0x00000270
	 { -1787, 34, 1861, 0, 2732, -1452, 100, 89, 67, 255 }, // 0x00000280
	 { -1805, 14, 1843, 0, 3206, -1470, 134, 119, 89, 255 }, // 0x00000290
	 { -1954, 128, 1914, 0, 6271, 1050, 69, 62, 48, 255 }, // 0x000002A0
	 { -1963, 100, 1906, 0, 5376, 1024, 69, 62, 48, 255 }, // 0x000002B0
	 { -1914, 128, 1954, 0, 897, 1050, 69, 62, 48, 255 }, // 0x000002C0
	 { -1934, 140, 1934, 0, 0, 1060, 69, 62, 48, 255 }, // 0x000002D0
	 { -1934, 140, 1934, 0, 7168, 1060, 69, 62, 48, 255 }, // 0x000002E0
	 { -1906, 100, 1963, 0, 1792, 1024, 69, 62, 48, 255 }, // 0x000002F0
};

Vtx_t _jyasinboss_room_0_vertices_00000300[8] = 
{
	 { -1866, 14, 1781, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000300
	 { -1775, 14, 1858, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000310
	 { -1866, 160, 1781, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000320
	 { -1775, 160, 1858, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000330
	 { -1972, 14, 1907, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000340
	 { -1880, 14, 1984, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000350
	 { -1972, 160, 1907, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000360
	 { -1880, 160, 1984, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000370
};

Gfx _jyasinboss_room_0_dlist_00000380[] =
{
	gsDPPipeSync(), // 0x00000380
	gsSPGeometryMode(0xFF030000, 0x00000000), // 0x00000388
	gsSPVertex(_jyasinboss_room_0_vertices_00000300, 8, 0), // 0x00000390
	gsSPCullDisplayList(0, 7), // 0x00000398
	gsDPPipeSync(), // 0x000003A0
	gsSPGeometryMode(0xFF000000, 0x00030000), // 0x000003A8
	gsSPSetOtherMode(0xE3, 14, 2, 0x00000000), // 0x000003B0
	gsSPTexture(65535, 65535, 0, 0, 1), // 0x000003B8
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, _jyasinboss_room_0_tex_000007C8), // 0x000003C0
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 5, 0, 0, 5, 0), // 0x000003C8
	gsDPLoadSync(), // 0x000003D0
	gsDPLoadBlock(7, 0, 0, 1023, 256), // 0x000003D8
	gsDPPipeSync(), // 0x000003E0
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0), // 0x000003E8
	gsDPSetTileSize(0, 0, 0, 124, 124), // 0x000003F0
	gsDPSetCombineLERP(TEXEL0, K5, SHADE, COMBINED_ALPHA, 0, 0, 0, 1, COMBINED, K5, PRIMITIVE, COMBINED_ALPHA, 0, 0, 0, COMBINED), // 0x000003F8
	gsSPSetOtherMode(0xE2, 3, 29, 0xC8112078), // 0x00000400
	gsSPGeometryMode(0xFF0E0000, 0x00000000), // 0x00000408
	gsSPGeometryMode(0xFF000000, 0x00010400), // 0x00000410
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255), // 0x00000418
	gsSPVertex(_jyasinboss_room_0_vertices_00000140, 28, 0), // 0x00000420
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0), // 0x00000428
	gsSP2Triangles(2, 4, 5, 0, 2, 5, 3, 0), // 0x00000430
	gsSP2Triangles(6, 4, 7, 0, 4, 2, 7, 0), // 0x00000438
	gsSP2Triangles(6, 8, 4, 0, 9, 8, 10, 0), // 0x00000440
	gsSP2Triangles(9, 11, 8, 0, 9, 12, 11, 0), // 0x00000448
	gsSP2Triangles(13, 11, 12, 0, 14, 15, 16, 0), // 0x00000450
	gsSP2Triangles(14, 17, 15, 0, 16, 18, 14, 0), // 0x00000458
	gsSP2Triangles(16, 19, 18, 0, 18, 20, 1, 0), // 0x00000460
	gsSP2Triangles(20, 21, 1, 0, 2, 1, 21, 0), // 0x00000468
	gsSP2Triangles(8, 11, 22, 0, 8, 22, 23, 0), // 0x00000470
	gsSP2Triangles(17, 14, 24, 0, 17, 24, 25, 0), // 0x00000478
	gsSP2Triangles(22, 11, 13, 0, 22, 13, 26, 0), // 0x00000480
	gsSP2Triangles(24, 14, 18, 0, 24, 18, 27, 0), // 0x00000488
	gsSP2Triangles(5, 4, 8, 0, 5, 8, 23, 0), // 0x00000490
	gsSP2Triangles(18, 1, 0, 0, 18, 0, 27, 0), // 0x00000498
	gsSP1Triangle(2, 21, 7, 0), // 0x000004A0
	gsSPEndDisplayList(), // 0x000004A8
};

Vtx_t _jyasinboss_room_0_vertices_000004B0[23] = 
{
	 { -1821, 0, 1736, 0, 4273, -2471, 81, 72, 55, 255 }, // 0x000004B0
	 { -1861, 34, 1787, 0, 4436, -1452, 81, 72, 55, 255 }, // 0x000004C0
	 { -1843, 14, 1805, 0, 3962, -1470, 134, 119, 89, 255 }, // 0x000004D0
	 { -1866, 136, 1782, 0, 6108, -1360, 55, 37, 18, 255 }, // 0x000004E0
	 { -1861, 34, 1787, 0, 4436, -1452, 100, 89, 67, 255 }, // 0x000004F0
	 { -1807, 160, 1722, 0, 6391, -2635, 55, 37, 18, 255 }, // 0x00000500
	 { -1835, 160, 1807, 0, 6847, -1397, 55, 37, 18, 255 }, // 0x00000510
	 { -1722, 160, 1807, 0, 7945, -2635, 55, 37, 18, 255 }, // 0x00000520
	 { -1807, 160, 1835, 0, 321, -1397, 55, 37, 18, 255 }, // 0x00000530
	 { -1722, 160, 1807, 0, 777, -2635, 55, 37, 18, 255 }, // 0x00000540
	 { -1782, 136, 1866, 0, 1060, -1360, 55, 37, 18, 255 }, // 0x00000550
	 { -1849, 140, 1849, 0, 7168, -796, 55, 37, 18, 255 }, // 0x00000560
	 { -1807, 160, 1835, 0, 7489, -1397, 55, 37, 18, 255 }, // 0x00000570
	 { -1736, 0, 1821, 0, 2895, -2471, 81, 72, 55, 255 }, // 0x00000580
	 { -1787, 34, 1861, 0, 2732, -1452, 81, 72, 55, 255 }, // 0x00000590
	 { -1787, 34, 1861, 0, 2732, -1452, 100, 89, 67, 255 }, // 0x000005A0
	 { -1805, 14, 1843, 0, 3206, -1470, 134, 119, 89, 255 }, // 0x000005B0
	 { -1652, 160, 1736, 0, 735, -4182, 55, 37, 18, 255 }, // 0x000005C0
	 { -1736, 160, 1652, 0, 6433, -4182, 55, 37, 18, 255 }, // 0x000005D0
	 { -1652, 160, 1736, 0, 7903, -4182, 55, 37, 18, 255 }, // 0x000005E0
	 { -1652, 0, 1736, 0, 2849, -4328, 52, 49, 38, 255 }, // 0x000005F0
	 { -1736, 0, 1652, 0, 4319, -4328, 52, 49, 38, 255 }, // 0x00000600
	 { -1779, 0, 1779, 0, 3584, -2471, 132, 88, 43, 255 }, // 0x00000610
};

Vtx_t _jyasinboss_room_0_vertices_00000620[8] = 
{
	 { -1749, 0, 1641, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000620
	 { -1645, 0, 1728, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000630
	 { -1749, 160, 1641, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000640
	 { -1645, 160, 1728, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000650
	 { -1893, 0, 1813, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000660
	 { -1789, 0, 1900, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000670
	 { -1893, 160, 1813, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000680
	 { -1789, 160, 1900, 0, 0, 0, 0, 0, 0, 0 }, // 0x00000690
};

Gfx _jyasinboss_room_0_dlist_000006A0[] =
{
	gsDPPipeSync(), // 0x000006A0
	gsSPGeometryMode(0xFF030000, 0x00000000), // 0x000006A8
	gsSPVertex(_jyasinboss_room_0_vertices_00000620, 8, 0), // 0x000006B0
	gsSPCullDisplayList(0, 7), // 0x000006B8
	gsDPPipeSync(), // 0x000006C0
	gsSPGeometryMode(0xFF000000, 0x00030000), // 0x000006C8
	gsSPSetOtherMode(0xE3, 14, 2, 0x00000000), // 0x000006D0
	gsSPTexture(65535, 65535, 0, 0, 1), // 0x000006D8
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, _jyasinboss_room_0_tex_000007C8), // 0x000006E0
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 0, 5, 0, 0, 5, 0), // 0x000006E8
	gsDPLoadSync(), // 0x000006F0
	gsDPLoadBlock(7, 0, 0, 1023, 256), // 0x000006F8
	gsDPPipeSync(), // 0x00000700
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, 0, 5, 0, 0, 5, 0), // 0x00000708
	gsDPSetTileSize(0, 0, 0, 124, 124), // 0x00000710
	gsDPSetCombineLERP(TEXEL0, K5, SHADE, COMBINED_ALPHA, 0, 0, 0, 1, COMBINED, K5, PRIMITIVE, COMBINED_ALPHA, 0, 0, 0, COMBINED), // 0x00000718
	gsSPSetOtherMode(0xE2, 3, 29, 0xC8112078), // 0x00000720
	gsSPGeometryMode(0xFF0E0000, 0x00000000), // 0x00000728
	gsSPGeometryMode(0xFF000000, 0x00010400), // 0x00000730
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255), // 0x00000738
	gsSPVertex(_jyasinboss_room_0_vertices_000004B0, 23, 0), // 0x00000740
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 4, 0), // 0x00000748
	gsSP2Triangles(3, 5, 6, 0, 5, 7, 6, 0), // 0x00000750
	gsSP2Triangles(8, 9, 10, 0, 11, 6, 12, 0), // 0x00000758
	gsSP2Triangles(6, 7, 12, 0, 10, 13, 14, 0), // 0x00000760
	gsSP2Triangles(15, 13, 16, 0, 10, 9, 17, 0), // 0x00000768
	gsSP2Triangles(7, 5, 18, 0, 7, 18, 19, 0), // 0x00000770
	gsSP2Triangles(5, 3, 18, 0, 17, 20, 13, 0), // 0x00000778
	gsSP2Triangles(17, 13, 10, 0, 21, 18, 3, 0), // 0x00000780
	gsSP2Triangles(21, 3, 0, 0, 16, 22, 2, 0), // 0x00000788
	gsSP2Triangles(22, 0, 2, 0, 16, 13, 22, 0), // 0x00000790
	gsSP2Triangles(13, 20, 22, 0, 20, 21, 22, 0), // 0x00000798
	gsSP1Triangle(21, 0, 22, 0), // 0x000007A0
	gsSPEndDisplayList(), // 0x000007A8
};

Gfx _jyasinboss_room_0_dlist_000007B0[] =
{
	gsSPDisplayList(_jyasinboss_room_0_dlist_00000380), // 0x000007B0
	gsSPDisplayList(_jyasinboss_room_0_dlist_000006A0), // 0x000007B8
	gsSPEndDisplayList(), // 0x000007C0
};

u64 _jyasinboss_room_0_tex_000007C8[] = 
{
	0x824D720B720B69C9, 0x71CB824B7A4D6989, 0x824B510359856187, 0x4903618771CB720B,  // 0x000007C8 
	0x69C969C969C969C9, 0x6189720B720B720B, 0x720B720B7A0B7A4B, 0x5145720B69C961C9,  // 0x000007E8 
	0x71C9720B69C971C9, 0x69C97A0B7A4B7A4B, 0x8A8B40C351455145, 0x490561877A4D71CB,  // 0x00000808 
	0x720B69C9618961C9, 0x618961C9720B720B, 0x720B720B720B720B, 0x6189618771C971CB,  // 0x00000828 
	0x720B71CB720B7A4B, 0x69C9720B824B720B, 0x828D720B51454905, 0x6189618969C971C9,  // 0x00000848 
	0x720B618969C969C9, 0x720B61896189720B, 0x720B720B7A4B720B, 0x69C9720B71C971C9,  // 0x00000868 
	0x720B6187720B7A4B, 0x7A4B8A8B7A0B71C9, 0x7A4B618748C33881, 0x5985720B7A4B720B,  // 0x00000888 
	0x720B7A4B720B61C9, 0x61897A4D720B7A4B, 0x7A0D720B824B720B, 0x720B69C9720B824B,  // 0x000008A8 
	0x7A4B824B720B7A4B, 0x71CB7A4B828D69C9, 0x594569C969C95945, 0x48C37A0B71C9720B,  // 0x000008C8 
	0x720B720B69C9720B, 0x720B7A4B8A4B69C9, 0x824B828D7A4B824B, 0x7A4B7A4B6A0B7A4D,  // 0x000008E8 
	0x69C97A0B720B69C9, 0x7A4B69C9594569C9, 0x720B720B720B71C9, 0x514561896189720B,  // 0x00000908 
	0x69C971C969C969C9, 0x69C96A0B820B7A09, 0x720B720B720B720B, 0x720B7A4B7A4B720B,  // 0x00000928 
	0x5945514571C95145, 0x6187720B7A096189, 0x71CB720B71C971CB, 0x69C95145618971C9,  // 0x00000948 
	0x7A4D69C961896189, 0x6A0B69C961C9720B, 0x7A0B7A0B71C9720B, 0x618969C961896147,  // 0x00000968 
	0x618761876187720B, 0x69C961C96189720B, 0x71C97A4D720B720B, 0x71C94905720B6189,  // 0x00000988 
	0x69C969C9720B720B, 0x720B6A0B7A4D720B, 0x720B720B7A4B69C9, 0x720B69C969C95945,  // 0x000009A8 
	0x61C95985720B720B, 0x824B720B69C969C9, 0x7A4B720B69C969C9, 0x7A4B69C97A09720B,  // 0x000009C8 
	0x824B69C9720B7A4B, 0x69C9824B720B8A8B, 0x720B7A0B720B7A4B, 0x720B720B61477A4D,  // 0x000009E8 
	0x7A0B720B61477A4B, 0x824B720B7A4B71C9, 0x6A0B7A0B824B824B, 0x824B71CB720B7A4B,  // 0x00000A08 
	0x824B7A0B7A4B69C9, 0x7A4D720B824B928B, 0x8A8B720B720B71C9, 0x720B6147824B7A49,  // 0x00000A28 
	0x69C97A4B618969C9, 0x61897A0D720B6187, 0x7A0B720B720B8A4B, 0x7A4B71CB7A0D720B,  // 0x00000A48 
	0x720B7A4D720B71CB, 0x69C969C97A4B720B, 0x7A4B720B69C96189, 0x51055949720B720B,  // 0x00000A68 
	0x61C9720B7A4B5147, 0x6189720B7A4B720B, 0x7A4B7A49824B69C9, 0x720B61897A4B7A0B,  // 0x00000A88 
	0x824B720B71CB69C9, 0x720B69C9720B720B, 0x720B71CB61896187, 0x71C971C951454905,  // 0x00000AA8 
	0x824B824B720B7A4D, 0x6147720B7A4B720B, 0x720B928B7A4D928B, 0x720B61878A8B92CB,  // 0x00000AC8 
	0x720B7A4D7A0971CB, 0x69C96A0B7A4D720B, 0x6189720B71C961C9, 0x618769C971C95145,  // 0x00000AE8 
	0x7A4B7A4D7A4B69C9, 0x720B6189720B8A8B, 0x69C9720B824B824B, 0x824B6189720B8A8B,  // 0x00000B08 
	0x92CB828D720B824B, 0x7A4D720B720B720B, 0x720B7A4D720B7A4D, 0x6189720B8A4B928B,  // 0x00000B28 
	0x720B720B7A4D720B, 0x69C9720B824D720B, 0x8A8D7A4B828D824B, 0x824B928B5187720B,  // 0x00000B48 
	0x8A8B92CB7A4D7A4D, 0x720B720B61897A4D, 0x824B7A4B7A4D7A4D, 0x720B7A0B8A8B92CB,  // 0x00000B68 
	0x8A8B7A4B61897A4B, 0x71CB7A4B720B828D, 0x828D8A8B8A8B8A8B, 0x720B824B720B6187,  // 0x00000B88 
	0x6A0B8A8B92CB69C9, 0x61CB7A4B720B7A4D, 0x8A8B8A8D7A4B824B, 0x8A8B8A8D71CB8A8B,  // 0x00000BA8 
	0x7A4B7A4B720B720B, 0x7A4B69C971CB7A4D, 0x828D824D824B69C9, 0x720B71C97A4B7A4D,  // 0x00000BC8 
	0x6147720B6189720B, 0x720B720B720B824B, 0x828D8A8B824B720B, 0x7A4D8A8B824B720B,  // 0x00000BE8 
	0x71CB69C97A4B720B, 0x720B69C9618969C9, 0x71C9720B720B71CB, 0x69C961896189720B,  // 0x00000C08 
	0x79CB4945618771C9, 0x618769C9720B7A0D, 0x6189824D8A8B720B, 0x7A4D720B824B7A4B,  // 0x00000C28 
	0x7A0B720B69C969C9, 0x69C9618969C96189, 0x69C971C9720B720B, 0x69C969C96147720B,  // 0x00000C48 
	0x618771C9490369C9, 0x514769C9720B6189, 0x69C969C971C97A4B, 0x720B69C9720B6A0B,  // 0x00000C68 
	0x7A4B7A4B720B6189, 0x69C969CB720B7A4B, 0x824B720B71C971C9, 0x720B7A4B720B720B,  // 0x00000C88 
	0x618771C9720B6147, 0x61897A4B720B7A0B, 0x720B720B618969C9, 0x824B720B720B69C9,  // 0x00000CA8 
	0x6147720B69C9720B, 0x720B6189720B720B, 0x824B8A8B824B824B, 0x7A4D720B7A4B6187,  // 0x00000CC8 
	0x61897A4D720B6187, 0x720B720B824B7A4B, 0x7A0D79CB71CB69C9, 0x720B7A0B720B71C9,  // 0x00000CE8 
	0x720B618961C97A4B, 0x61877A4B720B824B, 0x71CB71CB8A8B720B, 0x7A4B69C97A4D5145,  // 0x00000D08 
	0x720B61C9720B720B, 0x69C9720B828D824B, 0x7A4B824B61477A0B, 0x61C9720B69C97A4B,  // 0x00000D28 
	0x720B7A4B69C9720B, 0x69C9720B7A0B7A0B, 0x7A4D6189720B720B, 0x69C969C951476187,  // 0x00000D48 
	0x720B69C9614769C9, 0x720B7A4B720B7A4D, 0x6A0B61897A0B7A4B, 0x720B720B69C9720B,  // 0x00000D68 
	0x69C9824D7A0B61C9, 0x69C9824B7A4D8A8B, 0x720B69C971C971C9, 0x6189618971C969C9,  // 0x00000D88 
	0x720B720B61C96189, 0x61877A4D720B824B, 0x720B69C97A4D61C9, 0x720B71CB720B720B,  // 0x00000DA8 
	0x720B720B824B824B, 0x824B8A498A8B7A4B, 0x7A4D7A4B7A4D6A0B, 0x7A4D69C97A4D7A4B,  // 0x00000DC8 
	0x824B8A8D7A0B69C9, 0x69C969C9720B71CB, 0x7A0B71C969C9720B, 0x71CB720B720B7A4B,  // 0x00000DE8 
	0x8A8B720B720B8A8B, 0x824D7A4B8A8B824B, 0x8A8B7A4B720B92CB, 0x928B824B69C9720B,  // 0x00000E08 
	0x928D828D8A8B824B, 0x618969C96A0B7A0B, 0x720B71C971C969C9, 0x69C969C969C97A0B,  // 0x00000E28 
	0x824B824B7A4B8A8D, 0x824B7A4D720B824B, 0x8A8B7A4B7A4B7A4B, 0x8A8B928B6A0B6187,  // 0x00000E48 
	0x7A4B928B8A8B8A8D, 0x824B824B6A0B720B, 0x8A4B8A4D71C97A4B, 0x824B69C969C9720B,  // 0x00000E68 
	0x5147720B7A4D7A4B, 0x824B824D824B7A4D, 0x824B7A0B71CB71C9, 0x824B8A8B61895949,  // 0x00000E88 
	0x720B824B720B7A4D, 0x824B8A8D824B69C9, 0x7A0D7A4B8A497A0B, 0x7A4B8A4B8A4B69C9,  // 0x00000EA8 
	0x8A8B720B618969C9, 0x720B824B7A4B720B, 0x720B8A8B720B69C9, 0x7A0B618751476A0B,  // 0x00000EC8 
	0x61C96189720B720B, 0x71CB720B720B71C9, 0x61C971CB720B69C9, 0x71C9720B6A0B7A4B,  // 0x00000EE8 
	0x69C9824B518769C9, 0x69C97A4D7A0B720B, 0x69C971C97A4B720B, 0x69C9514569C969C9,  // 0x00000F08 
	0x61C969C969C971C9, 0x71CB720B69C969C9, 0x69C971C971C971CB, 0x618969C971CB720B,  // 0x00000F28 
	0x69C97A0B8A4B7A4D, 0x5945618971C9824B, 0x7A0B6A0B71C9720B, 0x7A0B69C961CB720B,  // 0x00000F48 
	0x720B69C9720B69C9, 0x720B69C9824B720B, 0x720B720B71CB69C9, 0x7A4D720B69C9720B,  // 0x00000F68 
	0x824B7A0D7A0B824B, 0x724D69C95147928B, 0x7A0B7A4B7A4D720B, 0x69C969C9720B720B,  // 0x00000F88 
	0x7A0B720B720B720B, 0x71CB720B7A0B7A4B, 0x720B7A0B824B720B, 0x720B824B720B720B,  // 0x00000FA8 
};

static u8 unaccounted0FC8[] = 
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

