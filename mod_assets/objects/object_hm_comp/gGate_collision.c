#include "ultra64.h"
#include "z64.h"
#include "macros.h"

SurfaceType gGate_polygonTypes[1] = {
    { SURFACETYPE0(0, 0, 0x00, 0, 0x00, 0x00, 0, 0), SURFACETYPE1(0x00, 0x00, 0, 0, 0, 0, 0, 0) },
};

Vec3s gGate_vertices[4] = {
    { -11772,  21161,      0 },
    {  11772,  21161,      0 },
    {  11772,      0,      0 },
    { -11772,      0,      0 },
};

CollisionPoly gGate_polygons[2] = {
    { 0, COLPOLY_VTX(2, (COLPOLY_IGNORE_PROJECTILES)), COLPOLY_VTX(0, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(1), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.371139183945161e-08), COLPOLY_SNORMAL(-1.0) }, 0 },
    { 0, COLPOLY_VTX(2, (COLPOLY_IGNORE_PROJECTILES)), COLPOLY_VTX(3, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(0), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.371139183945161e-08), COLPOLY_SNORMAL(-1.0) }, 0 },
};

CollisionHeader gGate_collisionHeader = {
    { -11772, 0, 0 },
    { 11772, 21161, 0 },
    ARRAY_COUNT(gGate_vertices), gGate_vertices,
    ARRAY_COUNT(gGate_polygons), gGate_polygons,
    gGate_polygonTypes,
    NULL,
    0, NULL
};