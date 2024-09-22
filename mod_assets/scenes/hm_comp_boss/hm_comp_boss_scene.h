#ifndef HM_COMP_BOSS_SCENE_H
#define HM_COMP_BOSS_SCENE_H

#include "ultra64.h"
#include "macros.h"
#include "z64.h"


extern SceneCmd hm_comp_boss_scene_header00[];
extern RomFile hm_comp_boss_scene_roomList[];
extern u8 _hm_comp_boss_room_0SegmentRomStart[];
extern u8 _hm_comp_boss_room_0SegmentRomEnd[];
extern ActorEntry hm_comp_boss_scene_header00_playerEntryList[];
extern Spawn hm_comp_boss_scene_header00_entranceList[];
extern TransitionActorEntry hm_comp_boss_scene_header00_transitionActors[];
extern EnvLightSettings hm_comp_boss_scene_header00_lightSettings[4];
extern CollisionHeader hm_comp_boss_scene_collisionHeader;
extern SurfaceType hm_comp_boss_scene_polygonTypes[1];
extern Vec3s hm_comp_boss_scene_vertices[36];
extern CollisionPoly hm_comp_boss_scene_polygons[62];
extern SceneCmd hm_comp_boss_room_0_header00[];
extern s16 hm_comp_boss_room_0_header00_objectList[];
extern Gfx hm_comp_boss_room_0_shapeHeader_entry_0_opaque[];
extern u64 hm_comp_boss_room_0_dl_HAKAdanCH_sceneTex_00B590_rgba16_ci8[];
extern u64 hm_comp_boss_room_0_dl_HAKAdanCH_sceneTex_00B590_rgba16_pal_rgba16[];
extern u64 hm_comp_boss_room_0_dl_HAKAdanCH_room_5Tex_002190_rgba16_ci8[];
extern u64 hm_comp_boss_room_0_dl_HAKAdanCH_room_5Tex_002190_rgba16_pal_rgba16[];
extern Vtx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_cull[8];
extern Vtx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_0[35];
extern Gfx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_tri_0[];
extern Vtx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_vtx_1[42];
extern Gfx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque_tri_1[];
extern Gfx mat_hm_comp_boss_room_0_dl_floor_mat_layerOpaque[];
extern Gfx mat_hm_comp_boss_room_0_dl_wall_mat_layerOpaque[];
extern Gfx hm_comp_boss_room_0_dl_Floor_mesh_layer_Opaque[];
extern RoomShapeNormal hm_comp_boss_room_0_shapeHeader;
extern RoomShapeDListsEntry hm_comp_boss_room_0_shapeDListsEntry[1];

#endif
