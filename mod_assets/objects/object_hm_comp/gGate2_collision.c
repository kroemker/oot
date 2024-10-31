#include "ultra64.h"
#include "z64.h"
#include "macros.h"

SurfaceType gGate2_polygonTypes[1] = {
    { SURFACETYPE0(0, 0, 0x00, 0, 0x00, 0x00, 0, 0), SURFACETYPE1(0x00, 0x00, 0, 0, 0, 0, 0, 0) },
};

Vec3s gGate2_vertices[4] = {
    {   7692,  22353,      0 },
    {  -7692,  22353,      0 },
    {  -7692,      0,      0 },
    {   7692,      0,      0 },
};

CollisionPoly gGate2_polygons[2] = {
    { 0, COLPOLY_VTX(2, COLPOLY_IGNORE_NONE), COLPOLY_VTX(0, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(1), { COLPOLY_SNORMAL(9.298665304413589e-08), COLPOLY_SNORMAL(4.371139183945161e-08), COLPOLY_SNORMAL(1.0) }, 0 },
    { 0, COLPOLY_VTX(2, COLPOLY_IGNORE_NONE), COLPOLY_VTX(3, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(0), { COLPOLY_SNORMAL(9.298666014956325e-08), COLPOLY_SNORMAL(4.371139183945161e-08), COLPOLY_SNORMAL(1.0) }, 0 },
};

CollisionHeader gGate2_collisionHeader = {
    { -7692, 0, 0 },
    { 7692, 22353, 0 },
    ARRAY_COUNT(gGate2_vertices), gGate2_vertices,
    ARRAY_COUNT(gGate2_polygons), gGate2_polygons,
    gGate2_polygonTypes,
    NULL,
    0, NULL
};