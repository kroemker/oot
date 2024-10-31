#include "hm_comp_scene.h"


/**
 * Header Child Day (Default)
*/
SceneCmd hm_comp_room_6_header00[] = {
    SCENE_CMD_ROOM_SHAPE(&hm_comp_room_6_shapeHeader),
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
    SCENE_CMD_SKYBOX_DISABLES(false, false),
    SCENE_CMD_TIME_SETTINGS(255, 255, 0),
    SCENE_CMD_END(),
};

RoomShapeNormal hm_comp_room_6_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(hm_comp_room_6_shapeDListsEntry),
    hm_comp_room_6_shapeDListsEntry,
    hm_comp_room_6_shapeDListsEntry + ARRAY_COUNT(hm_comp_room_6_shapeDListsEntry)
};

RoomShapeDListsEntry hm_comp_room_6_shapeDListsEntry[0] = {
    
};

