#include "ultra64.h"
#include "z64.h"
#include "macros.h"

SurfaceType gPlatform_polygonTypes[1] = {
    { SURFACETYPE0(0, 0, 0x00, 0, 0x00, 0x00, 0, 0), SURFACETYPE1(0x00, 0x00, 0, 0, 0, 0, 0, 0) },
};

Vec3s gPlatform_vertices[8] = {
    { -10000,  -1000,  10000 },
    { -10000,   1000,  10000 },
    { -10000,   1000, -10000 },
    { -10000,  -1000, -10000 },
    {  10000,   1000, -10000 },
    {  10000,  -1000, -10000 },
    {  10000,   1000,  10000 },
    {  10000,  -1000,  10000 },
};

CollisionPoly gPlatform_polygons[12] = {
    { 0, COLPOLY_VTX(0, COLPOLY_IGNORE_NONE), COLPOLY_VTX(1, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(2), { COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 55536 },
    { 0, COLPOLY_VTX(0, COLPOLY_IGNORE_NONE), COLPOLY_VTX(2, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(3), { COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 55536 },
    { 0, COLPOLY_VTX(3, COLPOLY_IGNORE_NONE), COLPOLY_VTX(2, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(4), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0) }, 55536 },
    { 0, COLPOLY_VTX(3, COLPOLY_IGNORE_NONE), COLPOLY_VTX(4, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(5), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0) }, 55536 },
    { 0, COLPOLY_VTX(5, COLPOLY_IGNORE_NONE), COLPOLY_VTX(4, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(6), { COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 55536 },
    { 0, COLPOLY_VTX(5, COLPOLY_IGNORE_NONE), COLPOLY_VTX(6, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(7), { COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 55536 },
    { 0, COLPOLY_VTX(7, COLPOLY_IGNORE_NONE), COLPOLY_VTX(6, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(1), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0) }, 55536 },
    { 0, COLPOLY_VTX(7, COLPOLY_IGNORE_NONE), COLPOLY_VTX(1, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(0), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0) }, 55536 },
    { 0, COLPOLY_VTX(3, COLPOLY_IGNORE_NONE), COLPOLY_VTX(5, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(7), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(4.470348002882929e-08) }, 64536 },
    { 0, COLPOLY_VTX(3, COLPOLY_IGNORE_NONE), COLPOLY_VTX(7, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(0), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(4.470348002882929e-08) }, 64536 },
    { 0, COLPOLY_VTX(4, COLPOLY_IGNORE_NONE), COLPOLY_VTX(2, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(1), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(-4.470348002882929e-08) }, 64536 },
    { 0, COLPOLY_VTX(4, COLPOLY_IGNORE_NONE), COLPOLY_VTX(1, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(6), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(-4.470348002882929e-08) }, 64536 },
};

CollisionHeader gPlatform_collisionHeader = {
    { -10000, -1000, -10000 },
    { 10000, 1000, 10000 },
    ARRAY_COUNT(gPlatform_vertices), gPlatform_vertices,
    ARRAY_COUNT(gPlatform_polygons), gPlatform_polygons,
    gPlatform_polygonTypes,
    NULL,
    0, NULL
};