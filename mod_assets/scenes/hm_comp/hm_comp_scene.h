#ifndef HM_COMP_SCENE_H
#define HM_COMP_SCENE_H

#include "ultra64.h"
#include "macros.h"
#include "z64.h"


extern SceneCmd hm_comp_scene_header00[];
extern RomFile hm_comp_scene_roomList[];
extern u8 _hm_comp_room_0SegmentRomStart[];
extern u8 _hm_comp_room_0SegmentRomEnd[];
extern ActorEntry hm_comp_scene_header00_playerEntryList[];
extern Spawn hm_comp_scene_header00_entranceList[];
extern EnvLightSettings hm_comp_scene_header00_lightSettings[4];
extern CollisionHeader hm_comp_scene_collisionHeader;
extern Vec3s hm_comp_scene_camPosData[];
extern BgCamInfo hm_comp_scene_bgCamInfo[];
extern SurfaceType hm_comp_scene_polygonTypes[1];
extern Vec3s hm_comp_scene_vertices[36];
extern CollisionPoly hm_comp_scene_polygons[60];
extern SceneCmd hm_comp_room_0_header00[];
extern s16 hm_comp_room_0_header00_objectList[];
extern ActorEntry hm_comp_room_0_header00_actorList[];
extern Gfx hm_comp_room_0_shapeHeader_entry_0_opaque[];
extern u64 hm_comp_room_0_dl_Bmori1_sceneTex_015B90_ci8_ci8[];
extern u64 hm_comp_room_0_dl_Bmori1_sceneTex_015B90_ci8_pal_rgba16[];
extern u64 hm_comp_room_0_dl_Bmori1_room_3Tex_0033D8_ci8_ci8[];
extern u64 hm_comp_room_0_dl_Bmori1_room_3Tex_0033D8_ci8_pal_rgba16[];
extern Vtx hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_cull[8];
extern Vtx hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_0[48];
extern Gfx hm_comp_room_0_dl_Floor_mesh_layer_Opaque_tri_0[];
extern Vtx hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_1[52];
extern Gfx hm_comp_room_0_dl_Floor_mesh_layer_Opaque_tri_1[];
extern Gfx mat_hm_comp_room_0_dl_floor_mat_layerOpaque[];
extern Gfx mat_hm_comp_room_0_dl_wall_layerOpaque[];
extern Gfx hm_comp_room_0_dl_Floor_mesh_layer_Opaque[];
extern RoomShapeNormal hm_comp_room_0_shapeHeader;
extern RoomShapeDListsEntry hm_comp_room_0_shapeDListsEntry[1];

#endif
