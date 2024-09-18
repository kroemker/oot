#include "hm_comp_scene.h"


/**
 * Header Child Day (Default)
*/
#define LENGTH_HM_COMP_ROOM_0_HEADER00_OBJECTLIST 4
#define LENGTH_HM_COMP_ROOM_0_HEADER00_ACTORLIST 20
SceneCmd hm_comp_room_0_header00[] = {
    SCENE_CMD_ROOM_SHAPE(&hm_comp_room_0_shapeHeader),
    SCENE_CMD_ECHO_SETTINGS(0x00),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x00, false, false),
    SCENE_CMD_SKYBOX_DISABLES(true, true),
    SCENE_CMD_TIME_SETTINGS(255, 255, 0),
    SCENE_CMD_OBJECT_LIST(LENGTH_HM_COMP_ROOM_0_HEADER00_OBJECTLIST, hm_comp_room_0_header00_objectList),
    SCENE_CMD_ACTOR_LIST(LENGTH_HM_COMP_ROOM_0_HEADER00_ACTORLIST, hm_comp_room_0_header00_actorList),
    SCENE_CMD_END(),
};

s16 hm_comp_room_0_header00_objectList[LENGTH_HM_COMP_ROOM_0_HEADER00_OBJECTLIST] = {
    OBJECT_IK,
    OBJECT_HIDAN_OBJECTS,
    OBJECT_HM_COMP,
    OBJECT_BOX,
};

ActorEntry hm_comp_room_0_header00_actorList[LENGTH_HM_COMP_ROOM_0_HEADER00_ACTORLIST] = {
    // Custom Actor
    {
        /* Actor ID   */ ACTOR_HM_COMP_OBJECTS,
        /* Position   */ { -824, -120, -290 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x1005
    },

    // Treasure Chest
    {
        /* Actor ID   */ ACTOR_EN_BOX,
        /* Position   */ { -223, -120, -126 },
        /* Rotation   */ { 0, 0, 1 },
        /* Parameters */ 0x27E1
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 160, -120, -99 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0413
    },

    // Custom Actor
    {
        /* Actor ID   */ ACTOR_HM_COMP_OBJECTS,
        /* Position   */ { 243, 72, -291 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(270.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0400
    },

    // Iron Knuckle
    {
        /* Actor ID   */ ACTOR_EN_IK,
        /* Position   */ { 0, -120, 234 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0001
    },

    // Custom Actor
    {
        /* Actor ID   */ ACTOR_HM_COMP_OBJECTS,
        /* Position   */ { -1200, -120, -328 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x0301
    },

    // Iron Knuckle
    {
        /* Actor ID   */ ACTOR_EN_IK,
        /* Position   */ { -652, -120, 69 },
        /* Rotation   */ { 0, 0x8000, 0 },
        /* Parameters */ 0x8201
    },

    // Iron Knuckle
    {
        /* Actor ID   */ ACTOR_EN_IK,
        /* Position   */ { -752, -120, 69 },
        /* Rotation   */ { 1, 0x8000, 0 },
        /* Parameters */ 0x8211
    },

    // Iron Knuckle
    {
        /* Actor ID   */ ACTOR_EN_IK,
        /* Position   */ { -852, -120, 69 },
        /* Rotation   */ { 2, 0x8000, 0 },
        /* Parameters */ 0x8221
    },

    // Iron Knuckle
    {
        /* Actor ID   */ ACTOR_EN_IK,
        /* Position   */ { -952, -120, 69 },
        /* Rotation   */ { 3, 0x8000, 0 },
        /* Parameters */ 0x8231
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { -752, -120, -6 },
        /* Rotation   */ { 1, 0, 0 },
        /* Parameters */ 0x0205
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { -852, -120, -6 },
        /* Rotation   */ { 2, 0, 0 },
        /* Parameters */ 0x0205
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { -952, -120, -6 },
        /* Rotation   */ { 3, 0, 0 },
        /* Parameters */ 0x0205
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { -652, -120, -6 },
        /* Rotation   */ { 0, 0, 0 },
        /* Parameters */ 0x0205
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 0, -120, -515 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x8100
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 80, -120, -515 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x8100
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 160, -120, -435 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x8100
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 0, -120, -595 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x8100
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 0, -120, -435 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x8100
    },

    // Dungeon Switches
    {
        /* Actor ID   */ ACTOR_OBJ_SWITCH,
        /* Position   */ { 80, -120, -435 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(180.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ 0x8100
    },
};

RoomShapeNormal hm_comp_room_0_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(hm_comp_room_0_shapeDListsEntry),
    hm_comp_room_0_shapeDListsEntry,
    hm_comp_room_0_shapeDListsEntry + ARRAY_COUNT(hm_comp_room_0_shapeDListsEntry)
};

RoomShapeDListsEntry hm_comp_room_0_shapeDListsEntry[1] = {
    { hm_comp_room_0_shapeHeader_entry_0_opaque, NULL }
};

Gfx hm_comp_room_0_shapeHeader_entry_0_opaque[] = {
	gsSPDisplayList(hm_comp_room_0_dl_Floor_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

u64 hm_comp_room_0_dl_Bmori1_sceneTex_015B90_ci8_ci8[] = {
	0x0001020304050607, 0x0809030a0b0c0d0e, 0x0f10110612131415, 0x0a04130016160317, 0x181815190708070b, 0x0607081a1b1c041d, 0x11051d091e071914, 0x151d0b0a01161f07, 
	0x02200a210a090904, 0x090b052219192208, 0x2217231e00190824, 0x250a0a031e1e0726, 0x2703070b21072700, 0x0326062615071108, 0x2113040719191919, 0x21190c0301022701, 
	0x19072407070a1c28, 0x2919192525191903, 0x232307062619142a, 0x1426190202141903, 0x01020907030a202b, 0x150a0c0a27150202, 0x1407060607191502, 0x0214141427191914, 
	0x0d0109190a22060a, 0x0c0c0a1827040707, 0x1207120707141515, 0x19192c140a0a0201, 0x0d0c19010a190b2d, 0x1515030123141217, 0x0912132e2f07232c, 0x142c2c2719023030, 
	0x260b150129200b19, 0x20202c2331310413, 0x231e132f2f322331, 0x0133150a190c0a30, 0x1925030030150a00, 0x0323010227270d1f, 0x1e231e30341e2e35, 0x36021536200a070a, 
	0x27262701032d0704, 0x0d232727120a031f, 0x1f37132e1f1f2323, 0x1914152015010203, 0x0a210400030c0a01, 0x1f1f0a090a15151f, 0x1f03230407231f07, 0x190a14190703010a, 
	0x19210a0a03003000, 0x35011c0027030020, 0x0d0118181c200203, 0x03000001010d0a06, 0x192608040a0a0409, 0x0302020303033501, 0x00291c2938290315, 0x1514031818350a22, 
	0x0509191907080714, 0x27190a27231e1e1f, 0x001c20391f1f1515, 0x0c1919121e230706, 0x06260c1907220701, 0x2c1427132e2e321e, 0x34182939150c1502, 0x152c142112120a03, 
	0x0a0a270c1907211f, 0x1f27011e1e1e2e23, 0x231f181c150a0018, 0x011219130a110604, 0x15090a152720140a, 0x0a03030118011f1f, 0x2327140202010a09, 0x0a0a230a2c070807, 
	0x0b0b0a0419010000, 0x1800030123131f1e, 0x183a020220351f07, 0x131f232319062205, 0x0506090919012c18, 0x3b180101090d0404, 0x01201504011f0706, 0x0a03141919222208, 
	0x1909120a14311c18, 0x01001c030320150a, 0x2506261d13130407, 0x0c142c1906072625, 0x0a011e3502022c15, 0x1520383938200a04, 0x091209131f231538, 0x3915141919151407, 
	0x0c0d123501013101, 0x010000151c201d17, 0x1d32322e1e130939, 0x393c142b2a202b15, 0x1919040a01351e34, 0x1f1e1f151f1f0d0d, 0x370e092e2e131539, 0x3c142d15152b1415, 
	0x0319011818010135, 0x1332120d0a091f1f, 0x230909321f090a0a, 0x3d14142b142b1525, 0x0004022818003030, 0x233523130d0d0130, 0x0a131e1f1f03030c, 0x241903150a151526, 
	0x0726190300001830, 0x351e090a0303181f, 0x37131f01231f1c0a, 0x220a200320200a0a, 0x0d192c1501201c30, 0x0001002801030001, 0x00001f000101011f, 0x0d010a0d03030319, 
	0x0907211903290303, 0x03021c3619190118, 0x2000201c29001c01, 0x0000150304021509, 0x1214060719030c0c, 0x2b1c361921190302, 0x15020a0a1c1c293b, 0x3e02210b0c0a2d02, 
	0x09151919040c0239, 0x1c3802191415191c, 0x0102361407031c1c, 0x3614063f01151402, 0x0a0214190c151515, 0x0a1c010419090902, 0x0707282a260d2820, 0x0921192c190a1908, 
	
};

u64 hm_comp_room_0_dl_Bmori1_sceneTex_015B90_ci8_pal_rgba16[] = {
	0xc62dbdabbde7b567, 0x94615ad56b57841d, 0x73598c1f9ca37bdb, 0x9c21aca5739d6b5b, 0x525363178c619463, 0x9d63b4e5d6b3739b, 0xce2f949f5acf7bd7, 0xce2d83ddadabb4e7, 
	0xc5eb7c1b63159ce5, 0x6b157b9b83dbad65, 0xd671d62fce2bc567, 0xada5aca194a57c21, 0xcdefb5ed8463c66d, 0xbe31be2dc62b9421, 0xd62dcdebce6fdef3, 0xc5658c1be6f16b59, 
	
};

u64 hm_comp_room_0_dl_Bmori1_room_3Tex_0033D8_ci8_ci8[] = {
	0x0001020304050506, 0x05070806090a0b04, 0x050c0d04030e0a0c, 0x040405040f101011, 0x1213140215011617, 0x1802060e191a1b1b, 0x1b1c1d181b011b14, 0x011e1b161f202122, 
	0x0003230903240e16, 0x161606011d181f16, 0x21021f2524010016, 0x1602152116012026, 0x030c27280429281f, 0x0e24060118161b1b, 0x180102240e2a021d, 0x1d16012801021703, 
	0x0924230b2b232c28, 0x160e060a1c141e14, 0x2a01012d0016182a, 0x211f02092601162e, 0x030b2323161f2816, 0x162408031d141c1b, 0x0202020e01182001, 0x162a2d0e020e1610, 
	0x1c0e18012a010e19, 0x1a2a0607012f1b1e, 0x1c1e180e2a2d2a16, 0x161e141b18171607, 0x0607070410303105, 0x0c3211080631102e, 0x03052e05090a0b03, 0x0c090305050f1033, 
	0x11070c0c07043432, 0x072e030a0c040410, 0x06352e0f32081110, 0x0d0c060707080705, 0x0a36361a1e1d0122, 0x2821151528281f1f, 0x2a181e370e060a36, 0x1d1d1e1e38181515, 
	0x0a0e241417010e28, 0x2339153a22280021, 0x161c381b02061436, 0x25251f1d02152623, 0x0d16180e18152f28, 0x273b232623020221, 0x21181c1603082a1b, 0x010b03030021122e, 
	0x0317200b18212128, 0x393a052303381416, 0x18170e020c080116, 0x01090b060501213c, 0x0b2123241d162128, 0x39150005012a141b, 0x1e2a00160a061621, 0x25240203010e183d, 
	0x052125181e142a18, 0x1500020e1c181e1b, 0x1c1c14360a071618, 0x2a1c140202142400, 0x082e31100c0b0505, 0x2e2e2e0c0a030b0b, 0x0900030607080405, 0x03090c0c05030304, 
	0x380a0c030c0c0607, 0x081111080d0d0c0c, 0x060606060c0a0c06, 0x0d06070606071111, 0x3619362a2a181b02, 0x020b080e1a1e1a36, 0x1b1919383814141e, 0x1e1b1c1c1c1c0c08, 
	0x0c03090a0109090d, 0x0309041b1b2a141d, 0x162d2409240a021d, 0x160b252901142432, 0x0c06050c060c0c06, 0x0129100e012a1c14, 0x2d240a090916211d, 0x1d09132328160108, 
	0x0c060c0d1005080d, 0x160a0824021c1e14, 0x380e0a090902010e, 0x1d01232327000008, 0x070410080404070d, 0x0a09080e1d1c1c2a, 0x14240b090b000121, 0x0e1623222e002932, 
	0x100403050c0c0a24, 0x240c33022a1e3617, 0x1816160e16012a1d, 0x1d182a0103290008, 0x1033103032070606, 0x081108060c030d07, 0x2e2e0f0606040404, 0x0606040707301008, 
	0x33060c0c0404060c, 0x0c0c0a0c032e2e0c, 0x06060f070811330c, 0x090a0c0a0c030002, 0x062a1c381b1d142a, 0x2a141b212a02002a, 0x0100152807061d1a, 0x3e381e361401161b, 
	0x0701050c2b030305, 0x272c3d27232b040d, 0x2b233126060d141d, 0x2d0e1c1c0e000116, 0x100b29050404070f, 0x3c0f232c050b0c05, 0x0d2e0416060c1e16, 0x1d24021c240a0b0c, 
	0x071f030306300732, 0x300d0704343c2831, 0x2e050c240d060e21, 0x1624290216280303, 0x0628032604310407, 0x040b07042e3c1328, 0x280028160b100116, 0x0e380e0e16000003, 
	0x112e16283c032904, 0x030b0c2626222816, 0x16011f180c321616, 0x160e1d1b0e161621, 0x11322e323f040407, 0x303332323211320f, 0x071032083306060f, 0x32342e0f3232100f, 
	
};

u64 hm_comp_room_0_dl_Bmori1_room_3Tex_0033D8_ci8_pal_rgba16[] = {
	0x53535b556b994a91, 0x39cd424f39cf29cb, 0x218b63175b595b15, 0x4a934a5173db29c9, 0x298910c56b8f5ad1, 0x845f5b916b9773d7, 0x7419ad679ce38c5d, 0x84217c1b8cdf5b53, 
	0x63136b933a8b4a8d, 0x739b52cf4b0f424b, 0x53115b13741b5ad3, 0x420d83df3a0b8415, 0x2185318919452107, 0x31c7294794e39d9f, 0x9463534f4ac9634b, 0x3ac95309b5ab2145, 
	
};

Vtx hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-1424, -732, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1424, 243, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1424, 243, -775}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1424, -732, -775}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {300, -732, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {300, 243, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {300, 243, -775}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {300, -732, -775}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_0[48] = {
	{{ {-300, -120, -444}, 0, {-1337, -2217}, {0, 127, 0, 255} }},
	{{ {-300, -120, 300}, 0, {-1337, 2329}, {0, 127, 0, 255} }},
	{{ {300, -120, 300}, 0, {2329, 2329}, {0, 127, 0, 255} }},
	{{ {-300, -120, -775}, 0, {-1337, -4239}, {0, 127, 0, 255} }},
	{{ {300, -120, -775}, 0, {2329, -4239}, {0, 127, 0, 255} }},
	{{ {-504, -120, -775}, 0, {-2582, -4239}, {0, 127, 0, 255} }},
	{{ {-504, -120, -444}, 0, {-2582, -2217}, {0, 127, 0, 255} }},
	{{ {-867, -120, -775}, 0, {-4798, -4239}, {0, 127, 0, 255} }},
	{{ {-1143, -120, -444}, 0, {-6486, -2217}, {0, 127, 0, 255} }},
	{{ {-300, 243, -775}, 0, {9336, -1576}, {0, 129, 0, 255} }},
	{{ {-300, 243, -444}, 0, {5559, -1576}, {0, 129, 0, 255} }},
	{{ {-504, 243, -444}, 0, {5559, -1576}, {0, 129, 0, 255} }},
	{{ {-504, 243, -775}, 0, {9336, -1576}, {0, 129, 0, 255} }},
	{{ {-504, -120, 172}, 0, {-2582, 1549}, {0, 127, 0, 255} }},
	{{ {-504, -120, -444}, 0, {-2582, -2217}, {0, 127, 0, 255} }},
	{{ {-1143, -120, -444}, 0, {-6486, -2217}, {0, 127, 0, 255} }},
	{{ {-1143, -120, -213}, 0, {-6486, -807}, {0, 127, 0, 255} }},
	{{ {-1167, -120, -420}, 0, {-6632, -2071}, {0, 127, 0, 255} }},
	{{ {-1400, -120, -420}, 0, {-8059, -2071}, {0, 127, 0, 255} }},
	{{ {-1424, -120, -444}, 0, {-8205, -2217}, {0, 127, 0, 255} }},
	{{ {-1400, -120, -237}, 0, {-8059, -953}, {0, 127, 0, 255} }},
	{{ {-1424, -120, -213}, 0, {-8205, -807}, {0, 127, 0, 255} }},
	{{ {-1167, -120, -237}, 0, {-6632, -953}, {0, 127, 0, 255} }},
	{{ {-1143, -120, 172}, 0, {-6486, 1549}, {0, 127, 0, 255} }},
	{{ {-1143, 243, -444}, 0, {5559, -1576}, {0, 129, 0, 255} }},
	{{ {-1143, 243, -213}, 0, {2931, -1576}, {0, 129, 0, 255} }},
	{{ {-1424, 243, -213}, 0, {2931, -1576}, {0, 129, 0, 255} }},
	{{ {-1424, 243, -444}, 0, {5559, -1576}, {0, 129, 0, 255} }},
	{{ {-1400, -120, -237}, 0, {-8059, -953}, {0, 0, 129, 255} }},
	{{ {-1167, -120, -237}, 0, {-6632, -953}, {0, 0, 129, 255} }},
	{{ {-1167, -732, -237}, 0, {-6632, -954}, {0, 0, 129, 255} }},
	{{ {-1400, -732, -237}, 0, {-8059, -954}, {0, 0, 129, 255} }},
	{{ {-1167, -732, -237}, 0, {-6632, -954}, {0, 127, 0, 255} }},
	{{ {-1167, -732, -420}, 0, {-6632, -2072}, {0, 127, 0, 255} }},
	{{ {-1400, -732, -420}, 0, {-8059, -2072}, {0, 127, 0, 255} }},
	{{ {-1400, -732, -237}, 0, {-8059, -954}, {0, 127, 0, 255} }},
	{{ {-1400, -120, -420}, 0, {-8059, -2071}, {127, 0, 0, 255} }},
	{{ {-1400, -120, -237}, 0, {-8059, -953}, {127, 0, 0, 255} }},
	{{ {-1400, -732, -237}, 0, {-8059, -954}, {127, 0, 0, 255} }},
	{{ {-1400, -732, -420}, 0, {-8059, -2072}, {127, 0, 0, 255} }},
	{{ {-1167, -120, -420}, 0, {-6632, -2071}, {0, 0, 127, 255} }},
	{{ {-1400, -120, -420}, 0, {-8059, -2071}, {0, 0, 127, 255} }},
	{{ {-1400, -732, -420}, 0, {-8059, -2072}, {0, 0, 127, 255} }},
	{{ {-1167, -732, -420}, 0, {-6632, -2072}, {0, 0, 127, 255} }},
	{{ {-1167, -120, -237}, 0, {-6632, -953}, {129, 0, 0, 255} }},
	{{ {-1167, -120, -420}, 0, {-6632, -2071}, {129, 0, 0, 255} }},
	{{ {-1167, -732, -420}, 0, {-6632, -2072}, {129, 0, 0, 255} }},
	{{ {-1167, -732, -237}, 0, {-6632, -954}, {129, 0, 0, 255} }},
};

Gfx hm_comp_room_0_dl_Floor_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_0 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
	gsSP2Triangles(2, 4, 3, 0, 0, 3, 5, 0),
	gsSP2Triangles(0, 5, 6, 0, 6, 5, 7, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(9, 11, 12, 0, 13, 14, 15, 0),
	gsSP2Triangles(15, 16, 13, 0, 17, 16, 15, 0),
	gsSP2Triangles(18, 17, 15, 0, 18, 15, 19, 0),
	gsSP2Triangles(20, 18, 19, 0, 20, 19, 21, 0),
	gsSP2Triangles(22, 20, 21, 0, 22, 21, 16, 0),
	gsSP2Triangles(17, 22, 16, 0, 16, 23, 13, 0),
	gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
	gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
	gsSPVertex(hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_0 + 32, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSPEndDisplayList(),
};

Vtx hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_1[52] = {
	{{ {300, -120, 300}, 0, {-2926, 2568}, {129, 0, 0, 255} }},
	{{ {300, 243, 300}, 0, {-2926, -1576}, {129, 0, 0, 255} }},
	{{ {300, 243, -775}, 0, {9336, -1576}, {129, 0, 0, 255} }},
	{{ {300, -120, -775}, 0, {9336, 2568}, {129, 0, 0, 255} }},
	{{ {300, -120, -775}, 0, {3918, 2568}, {0, 0, 127, 255} }},
	{{ {300, 243, -775}, 0, {3918, -1576}, {0, 0, 127, 255} }},
	{{ {-300, 243, -775}, 0, {-2926, -1576}, {0, 0, 127, 255} }},
	{{ {-300, -120, -775}, 0, {-2926, 2568}, {0, 0, 127, 255} }},
	{{ {-504, 243, -775}, 0, {-5251, -1576}, {0, 0, 127, 255} }},
	{{ {-504, -120, -775}, 0, {-5251, 2568}, {0, 0, 127, 255} }},
	{{ {-867, 243, -775}, 0, {-9388, -1576}, {0, 0, 127, 255} }},
	{{ {-867, -120, -775}, 0, {-9388, 2568}, {0, 0, 127, 255} }},
	{{ {-300, -120, 300}, 0, {-2926, 2568}, {0, 0, 129, 255} }},
	{{ {-300, 243, 300}, 0, {-2926, -1576}, {0, 0, 129, 255} }},
	{{ {300, 243, 300}, 0, {3918, -1576}, {0, 0, 129, 255} }},
	{{ {300, -120, 300}, 0, {3918, 2568}, {0, 0, 129, 255} }},
	{{ {-504, 243, -444}, 0, {5559, -1576}, {129, 0, 0, 255} }},
	{{ {-504, -120, -444}, 0, {5561, 2568}, {129, 0, 0, 255} }},
	{{ {-504, -120, 172}, 0, {5561, 2568}, {129, 0, 0, 255} }},
	{{ {-504, 243, 173}, 0, {5559, -1576}, {129, 0, 0, 255} }},
	{{ {-300, -120, -444}, 0, {5561, 2568}, {127, 0, 0, 255} }},
	{{ {-300, 243, -444}, 0, {5559, -1576}, {127, 0, 0, 255} }},
	{{ {-300, 243, 300}, 0, {-2926, -1576}, {127, 0, 0, 255} }},
	{{ {-300, -120, 300}, 0, {-2926, 2568}, {127, 0, 0, 255} }},
	{{ {-300, 243, -444}, 0, {5559, -1576}, {0, 0, 129, 255} }},
	{{ {-300, -120, -444}, 0, {5561, 2568}, {0, 0, 129, 255} }},
	{{ {-504, -120, -444}, 0, {5561, 2568}, {0, 0, 129, 255} }},
	{{ {-504, 243, -444}, 0, {5559, -1576}, {0, 0, 129, 255} }},
	{{ {-867, -120, -775}, 0, {9336, 2568}, {98, 0, 81, 255} }},
	{{ {-867, 243, -775}, 0, {9336, -1576}, {98, 0, 81, 255} }},
	{{ {-1143, 243, -444}, 0, {5559, -1576}, {98, 0, 81, 255} }},
	{{ {-1143, -120, -444}, 0, {5561, 2568}, {98, 0, 81, 255} }},
	{{ {-504, 243, 173}, 0, {5559, -1576}, {0, 0, 129, 255} }},
	{{ {-504, -120, 172}, 0, {5561, 2568}, {0, 0, 129, 255} }},
	{{ {-1143, -120, 172}, 0, {5561, 2568}, {0, 0, 129, 255} }},
	{{ {-1143, 243, 173}, 0, {5559, -1576}, {0, 0, 129, 255} }},
	{{ {-1143, -120, -444}, 0, {5561, 2568}, {0, 0, 127, 255} }},
	{{ {-1143, 243, -444}, 0, {5559, -1576}, {0, 0, 127, 255} }},
	{{ {-1424, 243, -444}, 0, {3980, -1576}, {0, 0, 127, 255} }},
	{{ {-1424, -120, -444}, 0, {3982, 2569}, {0, 0, 127, 255} }},
	{{ {-1424, -120, -444}, 0, {5561, 2568}, {127, 0, 0, 255} }},
	{{ {-1424, 243, -444}, 0, {5559, -1576}, {127, 0, 0, 255} }},
	{{ {-1424, 243, -213}, 0, {2931, -1576}, {127, 0, 0, 255} }},
	{{ {-1424, -120, -213}, 0, {2928, 2569}, {127, 0, 0, 255} }},
	{{ {-1143, -120, -213}, 0, {2928, 2569}, {127, 0, 0, 255} }},
	{{ {-1143, 243, -213}, 0, {2931, -1576}, {127, 0, 0, 255} }},
	{{ {-1143, 243, 173}, 0, {-1472, -1574}, {127, 0, 0, 255} }},
	{{ {-1143, -120, 172}, 0, {-1471, 2571}, {127, 0, 0, 255} }},
	{{ {-1143, 243, -213}, 0, {2931, -1576}, {0, 0, 129, 255} }},
	{{ {-1143, -120, -213}, 0, {2928, 2569}, {0, 0, 129, 255} }},
	{{ {-1424, -120, -213}, 0, {2928, 2569}, {0, 0, 129, 255} }},
	{{ {-1424, 243, -213}, 0, {2931, -1576}, {0, 0, 129, 255} }},
};

Gfx hm_comp_room_0_dl_Floor_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_1 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(7, 6, 8, 0, 7, 8, 9, 0),
	gsSP2Triangles(9, 8, 10, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSP2Triangles(24, 25, 26, 0, 24, 26, 27, 0),
	gsSP2Triangles(28, 29, 30, 0, 28, 30, 31, 0),
	gsSPVertex(hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_1 + 32, 20, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_room_0_dl_floor_mat_layerOpaque[] = {
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_room_0_dl_Bmori1_sceneTex_015B90_ci8_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 63),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_comp_room_0_dl_Bmori1_sceneTex_015B90_ci8_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_hm_comp_room_0_dl_wall_layerOpaque[] = {
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_comp_room_0_dl_Bmori1_room_3Tex_0033D8_ci8_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 63),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_comp_room_0_dl_Bmori1_room_3Tex_0033D8_ci8_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx hm_comp_room_0_dl_Floor_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(hm_comp_room_0_dl_Floor_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_hm_comp_room_0_dl_floor_mat_layerOpaque),
	gsSPDisplayList(hm_comp_room_0_dl_Floor_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_hm_comp_room_0_dl_wall_layerOpaque),
	gsSPDisplayList(hm_comp_room_0_dl_Floor_mesh_layer_Opaque_tri_1),
	gsSPEndDisplayList(),
};

