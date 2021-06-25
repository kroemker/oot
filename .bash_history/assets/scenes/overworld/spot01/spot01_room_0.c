#include "ultra64.h"
#include "z64.h"
#include "macros.h"
#include "spot01_room_0.h"

#include "segment_symbols.h"
#include "command_macros_base.h"
#include "z64cutscene_commands.h"
#include "variables.h"
#include "spot01_scene.h"

SCmdEchoSettings spot01_room_0_header00_cmd00 = { 0x16, 0x00, {0x00}, 0x00 };

SCmdRoomBehavior spot01_room_0_header00_cmd01 = { 0x08, 0x00, 0x00000000 };

SCmdSkyboxDisables spot01_room_0_header00_cmd02 = { 0x12, 0x00, 0x00, 0x00, 0x00, 0x00 };

SCmdTimeSettings spot01_room_0_header00_cmd03 = { 0x10, 0x00, 0x00, 0x00, 0xFF, 0xFF, 10 };

SCmdMesh spot01_room_0_header00_cmd04 = { 0x0A, 0x00, (u32)&spot01_room_0_meshHeader };

SCmdEndMarker spot01_room_0_header00_cmd05 = { 0x14, 0x00, 0x00 };


MeshHeader0 spot01_room_0_meshHeader = { {0}, 1, (u32)&spot01_room_0_meshDListEntry, (u32)&(spot01_room_0_meshDListEntry) + sizeof(spot01_room_0_meshDListEntry) };

MeshEntry0 spot01_room_0_meshDListEntry[1] = {
	{ (u32)spot01_room_0_entry_0_opaque, (u32)0 },
};

Gfx spot01_room_0_entry_0_opaque[] = {
	gsSPDisplayList(spot01_dl_Floor_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

Vtx spot01_dl_Floor_mesh_layer_Opaque_vtx_cull[8] = {
	{{{-300, -120, 300},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-300, -120, 300},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-300, -120, -300},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-300, -120, -300},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{300, -120, 300},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{300, -120, 300},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{300, -120, -300},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{300, -120, -300},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx spot01_dl_Floor_mesh_layer_Opaque_vtx_0[4] = {
	{{{-300, -120, 300},0, {-16, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{300, -120, 300},0, {1008, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{300, -120, -300},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-300, -120, -300},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx spot01_dl_Floor_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(spot01_dl_Floor_mesh_layer_Opaque_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_spot01_dl_floor_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPClearGeometryMode(G_CULL_FRONT | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 254, 254, 254, 255),
	gsSPEndDisplayList(),
};

Gfx spot01_dl_Floor_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(spot01_dl_Floor_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_spot01_dl_floor_mat_layerOpaque),
	gsSPDisplayList(spot01_dl_Floor_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};

