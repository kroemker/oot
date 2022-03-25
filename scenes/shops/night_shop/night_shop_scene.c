#include <ultra64.h>
#include <z64.h>
#include "night_shop_scene.h"
#include <z64.h>
#include <segment_symbols.h>
#include <command_macros_base.h>
#include <z64cutscene_commands.h>
#include <variables.h>



SCmdSoundSettings _night_shop_scene_set0000_cmd00 = { 0x15, 0x05, 0x00, 0x00, 0x00, 0x00, 0x13, 0x55 }; // 0x0000
SCmdRoomList _night_shop_scene_set0000_cmd01 = { 0x04, 0x01, (u32)&_night_shop_scene_roomList_00000078 }; // 0x0008
SCmdMiscSettings _night_shop_scene_set0000_cmd02 = { 0x19, 0x10, 0x0000000E }; // 0x0010
SCmdColHeader _night_shop_scene_set0000_cmd03 = { 0x03, 0x00, (u32)&_night_shop_scene_collisionHeader_00000644}; // 0x0018
SCmdEntranceList _night_shop_scene_set0000_cmd04 = { 0x06, 0x00, (u32)&_night_shop_scene_entranceList_00000080 }; // 0x0020
SCmdSpecialFiles _night_shop_scene_set0000_cmd05 = { 0x07, 0x00, 0x0002}; // 0x0028
SCmdSpawnList _night_shop_scene_set0000_cmd06 = { 0x00, 0x02, (u32)&_night_shop_scene_startPositionList_00000058}; // 0x0030
SCmdSkyboxSettings _night_shop_scene_set0000_cmd07 = { 0x11, 0x00, 0x00, 0x00, 0x18, 0x00, 0x01}; // 0x0038
SCmdExitList _night_shop_scene_set0000_cmd08 = { 0x13, 0x00, (u32)&_night_shop_scene_exitList_00000084 }; // 0x0040
SCmdLightSettingList _night_shop_scene_set0000_cmd09 = { 0x0F, 1, (u32)&_night_shop_scene_lightSettings_00000088}; // 0x0048
SCmdEndMarker _night_shop_scene_set0000_cmd0A = { 0x14, 0x00, 0x00 }; // 0x0050
ActorEntry _night_shop_scene_startPositionList_00000058[] = 
{
	{ ACTOR_PLAYER, 0, 0, 147, 0, -32768, 0, 0x0E00 },
	{ ACTOR_PLAYER, 0, 0, 147, 0, -32768, 0, 0x0EFF },
};

RomFile _night_shop_scene_roomList_00000078[] = 
{
	{ (u32)_night_shop_room_0SegmentRomStart, (u32)_night_shop_room_0SegmentRomEnd },
};

EntranceEntry _night_shop_scene_entranceList_00000080[] = 
{
	{ 0x00, 0x00 }, //0x00000080 
	{ 0x01, 0x00 }, //0x00000082 
};

u16 _night_shop_scene_exitList_00000084[] = 
{
	0x03C0,
	0x0000,
};

LightSettings _night_shop_scene_lightSettings_00000088[] = 
{
	{ 0x46, 0x28, 0x28, 0x42, 0x3E, 0x58, 0xC8, 0xAA, 0x96, 0xA3, 0x47, 0x2E, 0x32, 0x3C, 0x46, 0x0A, 0x0A, 0x0A, 0x07E0, 0x07D0 }, // 0x00000088 
};

CamPosData _night_shop_scene_camPosData_000000A0[] = 
{
	{ 0, 80, 280, 1820, -32768, 0, 5000, -1, 0xFFFF }, // 0x020000A0
	{ 0, 60, 60, 0, -32768, 0, -1, -1, 0xFFFF }, // 0x020000B2
};

CamData _night_shop_scene_camData_000000C4 = { 0x0019, 0x0003, (u32)_night_shop_scene_camPosData_000000A0 };

CamPosDataEntry _night_shop_scene_camPosDataEntries_000000CC[] = 
{
	{ 0x00170003, (u32)&_night_shop_scene_camPosData_000000A0[1] }, // 0x000000CC
	{ 0x00000000, 0x00000000 }, // 0x000000D4
};

u32 _night_shop_scene_polygonTypes_000000DC[] = 
{
	 0x00000002, 0x000037C2, 
	 0x00000102, 0x000C37C2, 
	 0x00200002, 0x00003002, 
};

RoomPoly _night_shop_scene_polygons_000000F4[] = 
{
	{ 0x0000, 0x003C, 0x003D, 0x003E, 0x0000, 0x0000, 0x7FFF, 0xFFD8 }, // 0x000000F4
	{ 0x0000, 0x003C, 0x003E, 0x003F, 0x0000, 0x0000, 0x7FFF, 0xFFD8 }, // 0x00000104
	{ 0x0000, 0x0040, 0x0041, 0x003F, 0x7FFF, 0x0000, 0x0000, 0x0064 }, // 0x00000114
	{ 0x0000, 0x0040, 0x003F, 0x003E, 0x7FFF, 0x0000, 0x0000, 0x0064 }, // 0x00000124
	{ 0x0000, 0x0042, 0x003D, 0x003C, 0x8001, 0x0000, 0x0000, 0x0064 }, // 0x00000134
	{ 0x0000, 0x0042, 0x003C, 0x0043, 0x8001, 0x0000, 0x0000, 0x0064 }, // 0x00000144
	{ 0x0000, 0x0041, 0x0043, 0x003C, 0x0000, 0x7FFF, 0x0000, 0x0000 }, // 0x00000154
	{ 0x0000, 0x0041, 0x003C, 0x003F, 0x0000, 0x7FFF, 0x0000, 0x0000 }, // 0x00000164
	{ 0x0001, 0x0044, 0x2045, 0x0046, 0x0000, 0x7FFF, 0x0000, 0xFFFF }, // 0x00000174
	{ 0x0001, 0x0044, 0x2047, 0x0045, 0x0000, 0x7FFF, 0x0000, 0xFFFF }, // 0x00000184
	{ 0x0002, 0x0000, 0x0001, 0x0002, 0x8B7A, 0x0000, 0xCB09, 0xFFEC }, // 0x00000194
	{ 0x0002, 0x0000, 0x0002, 0x0003, 0x8B7A, 0x0000, 0xCB09, 0xFFEC }, // 0x000001A4
	{ 0x0002, 0x0004, 0x0003, 0x0002, 0x393E, 0x0000, 0x8D84, 0x0098 }, // 0x000001B4
	{ 0x0002, 0x0004, 0x0002, 0x0005, 0x393E, 0x0000, 0x8D84, 0x0098 }, // 0x000001C4
	{ 0x0002, 0x0005, 0x0006, 0x0007, 0x7486, 0x0000, 0x34F7, 0xFFFE }, // 0x000001D4
	{ 0x0002, 0x0005, 0x0007, 0x0004, 0x7486, 0x0000, 0x34F7, 0xFFFE }, // 0x000001E4
	{ 0x0002, 0x0008, 0x0009, 0x000A, 0x34F7, 0x0000, 0x8B7A, 0x00BF }, // 0x000001F4
	{ 0x0002, 0x0008, 0x000A, 0x000B, 0x34F7, 0x0000, 0x8B7A, 0x00BF }, // 0x00000204
	{ 0x0002, 0x000C, 0x000B, 0x000A, 0x727C, 0x0000, 0x393E, 0xFFD0 }, // 0x00000214
	{ 0x0002, 0x000C, 0x000A, 0x000D, 0x727C, 0x0000, 0x393E, 0xFFD0 }, // 0x00000224
	{ 0x0002, 0x000D, 0x000E, 0x000F, 0xC8F8, 0x0000, 0x7390, 0xFF2B }, // 0x00000234
	{ 0x0002, 0x000D, 0x000F, 0x000C, 0xC8F8, 0x0000, 0x7390, 0xFF2B }, // 0x00000244
	{ 0x0002, 0x0010, 0x0011, 0x0012, 0x7732, 0x0000, 0xD15C, 0x0079 }, // 0x00000254
	{ 0x0002, 0x0010, 0x0012, 0x0013, 0x7732, 0x0000, 0xD15C, 0x0079 }, // 0x00000264
	{ 0x0002, 0x0011, 0x0014, 0x0015, 0x2EA4, 0x0000, 0x88CE, 0x00AB }, // 0x00000274
	{ 0x0002, 0x0011, 0x0015, 0x0012, 0x2EA4, 0x0000, 0x88CE, 0x00AB }, // 0x00000284
	{ 0x0002, 0x0014, 0x0016, 0x0017, 0xD15C, 0x0000, 0x88CE, 0x0068 }, // 0x00000294
	{ 0x0002, 0x0014, 0x0017, 0x0015, 0xD15C, 0x0000, 0x88CE, 0x0068 }, // 0x000002A4
	{ 0x0002, 0x0018, 0x0019, 0x001A, 0xD15C, 0x0000, 0x7732, 0xFF19 }, // 0x000002B4
	{ 0x0002, 0x0018, 0x001A, 0x001B, 0xD15C, 0x0000, 0x7732, 0xFF19 }, // 0x000002C4
	{ 0x0002, 0x0019, 0x001C, 0x001D, 0x2EA4, 0x0000, 0x7732, 0xFF5C }, // 0x000002D4
	{ 0x0002, 0x0019, 0x001D, 0x001A, 0x2EA4, 0x0000, 0x7732, 0xFF5C }, // 0x000002E4
	{ 0x0002, 0x001C, 0x0010, 0x0013, 0x7732, 0x0000, 0x2EA4, 0xFFF6 }, // 0x000002F4
	{ 0x0002, 0x001C, 0x0013, 0x001D, 0x7732, 0x0000, 0x2EA4, 0xFFF6 }, // 0x00000304
	{ 0x0002, 0x001E, 0x001F, 0x0020, 0x7486, 0x0000, 0xCB09, 0xFFEC }, // 0x00000314
	{ 0x0002, 0x001E, 0x0020, 0x0021, 0x7486, 0x0000, 0xCB09, 0xFFEC }, // 0x00000324
	{ 0x0002, 0x0022, 0x001F, 0x001E, 0xC6C2, 0x0000, 0x8D84, 0x0098 }, // 0x00000334
	{ 0x0002, 0x0022, 0x001E, 0x0023, 0xC6C2, 0x0000, 0x8D84, 0x0098 }, // 0x00000344
	{ 0x0002, 0x0023, 0x0024, 0x0025, 0x8B7A, 0x0000, 0x34F7, 0xFFFE }, // 0x00000354
	{ 0x0002, 0x0023, 0x0025, 0x0022, 0x8B7A, 0x0000, 0x34F7, 0xFFFE }, // 0x00000364
	{ 0x0002, 0x0026, 0x0027, 0x0028, 0xCB09, 0x0000, 0x8B7A, 0x00BF }, // 0x00000374
	{ 0x0002, 0x0026, 0x0028, 0x0029, 0xCB09, 0x0000, 0x8B7A, 0x00BF }, // 0x00000384
	{ 0x0002, 0x002A, 0x0027, 0x0026, 0x8D84, 0x0000, 0x393E, 0xFFD0 }, // 0x00000394
	{ 0x0002, 0x002A, 0x0026, 0x002B, 0x8D84, 0x0000, 0x393E, 0xFFD0 }, // 0x000003A4
	{ 0x0002, 0x002B, 0x002C, 0x002D, 0x3708, 0x0000, 0x7390, 0xFF2B }, // 0x000003B4
	{ 0x0002, 0x002B, 0x002D, 0x002A, 0x3708, 0x0000, 0x7390, 0xFF2B }, // 0x000003C4
	{ 0x0002, 0x002E, 0x002F, 0x0030, 0x88CE, 0x0000, 0xD15C, 0x0079 }, // 0x000003D4
	{ 0x0002, 0x002E, 0x0030, 0x0031, 0x88CE, 0x0000, 0xD15C, 0x0079 }, // 0x000003E4
	{ 0x0002, 0x002F, 0x0032, 0x0033, 0xD15C, 0x0000, 0x88CE, 0x00AB }, // 0x000003F4
	{ 0x0002, 0x002F, 0x0033, 0x0030, 0xD15C, 0x0000, 0x88CE, 0x00AB }, // 0x00000404
	{ 0x0002, 0x0032, 0x0034, 0x0035, 0x2EA4, 0x0000, 0x88CE, 0x0068 }, // 0x00000414
	{ 0x0002, 0x0032, 0x0035, 0x0033, 0x2EA4, 0x0000, 0x88CE, 0x0068 }, // 0x00000424
	{ 0x0002, 0x0036, 0x0037, 0x0038, 0x2EA4, 0x0000, 0x7732, 0xFF19 }, // 0x00000434
	{ 0x0002, 0x0036, 0x0038, 0x0039, 0x2EA4, 0x0000, 0x7732, 0xFF19 }, // 0x00000444
	{ 0x0002, 0x0037, 0x003A, 0x003B, 0xD15C, 0x0000, 0x7732, 0xFF5C }, // 0x00000454
	{ 0x0002, 0x0037, 0x003B, 0x0038, 0xD15C, 0x0000, 0x7732, 0xFF5C }, // 0x00000464
	{ 0x0002, 0x003A, 0x002E, 0x0031, 0x88CE, 0x0000, 0x2EA4, 0xFFF6 }, // 0x00000474
	{ 0x0002, 0x003A, 0x0031, 0x003B, 0x88CE, 0x0000, 0x2EA4, 0xFFF6 }, // 0x00000484
};

Vec3s _night_shop_scene_vertices_00000494[72] = 
{
	{ -91, 0, 152 }, // 0x00000494
	{ -91, 120, 152 }, // 0x0000049A
	{ -81, 120, 130 }, // 0x000004A0
	{ -81, 0, 130 }, // 0x000004A6
	{ -61, 0, 140 }, // 0x000004AC
	{ -61, 120, 140 }, // 0x000004B2
	{ -71, 120, 162 }, // 0x000004B8
	{ -71, 0, 162 }, // 0x000004BE
	{ -64, 0, 181 }, // 0x000004C4
	{ -64, 120, 181 }, // 0x000004CA
	{ -42, 120, 191 }, // 0x000004D0
	{ -42, 0, 191 }, // 0x000004D6
	{ -52, 0, 211 }, // 0x000004DC
	{ -52, 120, 211 }, // 0x000004E2
	{ -73, 120, 201 }, // 0x000004E8
	{ -73, 0, 201 }, // 0x000004EE
	{ -60, 0, 180 }, // 0x000004F4
	{ -69, 0, 157 }, // 0x000004FA
	{ -69, 120, 157 }, // 0x00000500
	{ -60, 120, 180 }, // 0x00000506
	{ -92, 0, 148 }, // 0x0000050C
	{ -92, 120, 148 }, // 0x00000512
	{ -115, 0, 157 }, // 0x00000518
	{ -115, 120, 157 }, // 0x0000051E
	{ -115, 0, 203 }, // 0x00000524
	{ -92, 0, 212 }, // 0x0000052A
	{ -92, 120, 212 }, // 0x00000530
	{ -115, 120, 203 }, // 0x00000536
	{ -69, 0, 203 }, // 0x0000053C
	{ -69, 120, 203 }, // 0x00000542
	{ 81, 0, 130 }, // 0x00000548
	{ 81, 120, 130 }, // 0x0000054E
	{ 91, 120, 152 }, // 0x00000554
	{ 91, 0, 152 }, // 0x0000055A
	{ 61, 120, 140 }, // 0x00000560
	{ 61, 0, 140 }, // 0x00000566
	{ 71, 0, 162 }, // 0x0000056C
	{ 71, 120, 162 }, // 0x00000572
	{ 42, 0, 191 }, // 0x00000578
	{ 42, 120, 191 }, // 0x0000057E
	{ 64, 120, 181 }, // 0x00000584
	{ 64, 0, 181 }, // 0x0000058A
	{ 52, 120, 211 }, // 0x00000590
	{ 52, 0, 211 }, // 0x00000596
	{ 73, 0, 201 }, // 0x0000059C
	{ 73, 120, 201 }, // 0x000005A2
	{ 60, 120, 180 }, // 0x000005A8
	{ 69, 120, 157 }, // 0x000005AE
	{ 69, 0, 157 }, // 0x000005B4
	{ 60, 0, 180 }, // 0x000005BA
	{ 92, 120, 148 }, // 0x000005C0
	{ 92, 0, 148 }, // 0x000005C6
	{ 115, 120, 157 }, // 0x000005CC
	{ 115, 0, 157 }, // 0x000005D2
	{ 115, 120, 203 }, // 0x000005D8
	{ 92, 120, 212 }, // 0x000005DE
	{ 92, 0, 212 }, // 0x000005E4
	{ 115, 0, 203 }, // 0x000005EA
	{ 69, 120, 203 }, // 0x000005F0
	{ 69, 0, 203 }, // 0x000005F6
	{ 100, 0, 40 }, // 0x000005FC
	{ 100, 120, 40 }, // 0x00000602
	{ -100, 120, 40 }, // 0x00000608
	{ -100, 0, 40 }, // 0x0000060E
	{ -100, 120, 230 }, // 0x00000614
	{ -100, 0, 230 }, // 0x0000061A
	{ 100, 120, 230 }, // 0x00000620
	{ 100, 0, 230 }, // 0x00000626
	{ 40, 1, 160 }, // 0x0000062C
	{ -40, 1, 200 }, // 0x00000632
	{ 40, 1, 200 }, // 0x00000638
	{ -40, 1, 160 }, // 0x0000063E
};

CollisionHeader _night_shop_scene_collisionHeader_00000644 = { 0xFF60, 0x0000, 0xFF88, 0x00A0, 0x0090, 0x00F0, 72, _night_shop_scene_vertices_00000494, 0x003A, _night_shop_scene_polygons_000000F4, _night_shop_scene_polygonTypes_000000DC, &_night_shop_scene_camData_000000C4, 0x0000, 0 };

