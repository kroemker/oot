#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "spot01_scene.h"

#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"

SCmdSoundSettings spot01_scene_header00_cmd00 = { 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 };

SCmdRoomList spot01_scene_header00_cmd01 = { 0x04, 1, (u32)&spot01_scene_roomList };

SCmdMiscSettings spot01_scene_header00_cmd02 = { 0x19, 0x00, 0x00 };

SCmdColHeader spot01_scene_header00_cmd03 = { 0x03, 0x00, (u32)&spot01_collisionHeader };

SCmdEntranceList spot01_scene_header00_cmd04 = { 0x06, 0x00, (u32)&spot01_scene_header00_entranceList };

SCmdSpecialFiles spot01_scene_header00_cmd05 = { 0x07, 0x00, 0x0002 };

SCmdSpawnList spot01_scene_header00_cmd06 = { 0x00, 1, (u32)&spot01_scene_header00_startPositionList };

SCmdSkyboxSettings spot01_scene_header00_cmd07 = { 0x11, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 };

SCmdLightSettingList spot01_scene_header00_cmd08 = { 0x0F, 4, (u32)&spot01_scene_header00_lightSettings };

SCmdEndMarker spot01_scene_header00_cmd09 = { 0x14, 0x00, 0x00 };


ActorEntry spot01_scene_header00_startPositionList[] = {
	{ ACTOR_PLAYER, 0, -120, 0, 0, 0, 0, 0x0FFF },
};

RomFile spot01_scene_roomList[] = {
	{ (u32)_spot01_room_0SegmentRomStart, (u32)_spot01_room_0SegmentRomEnd },
};

EntranceEntry spot01_scene_header00_entranceList[1] = {
	{ 0, 0 },
};

LightSettings spot01_scene_header00_lightSettings[4] = {
	{ 70, 45, 57, 73, 73, 73, 180, 154, 138, 183, 183, 183, 20, 20, 60, 140, 120, 100, 0x07e1, 12800 },
	{ 105, 90, 90, 73, 73, 73, 255, 255, 240, 183, 183, 183, 50, 50, 90, 100, 100, 120, 0x07e4, 12800 },
	{ 120, 90, 0, 73, 73, 73, 250, 135, 50, 183, 183, 183, 30, 30, 60, 120, 70, 50, 0x07e3, 12800 },
	{ 40, 70, 100, 73, 73, 73, 20, 20, 35, 183, 183, 183, 50, 50, 100, 0, 0, 30, 0x07e0, 12800 },
};

u32 spot01_polygonTypes[] = {
	 0x00000000, 0x00000000,
};

CollisionPoly spot01_polygons[] = {
	{ 0x0000, 0x0000, 0x0001, 0x0002, 0x0000, 0x7fff, 0x0000, 0x0078 },
	{ 0x0000, 0x0000, 0x0002, 0x0003, 0x0000, 0x7fff, 0x0000, 0x0078 },
};

Vec3s spot01_vertices[4] = {
	{ -300, -120, 300 },
	{ 300, -120, 300 },
	{ 300, -120, -300 },
	{ -300, -120, -300 },
};

CollisionHeader spot01_collisionHeader = { -300, -120, -300, 300, -120, 300, 4, spot01_vertices, 2, spot01_polygons, spot01_polygonTypes, 0, 0, 0 };

