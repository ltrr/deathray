#ifndef DEATHRAY_OBJPARSER_H_
#define DEATHRAY_OBJPARSER_H_

#include <vector>
#include "material/material.h"
#include "description/surface.h"

/*
struct ObjParserResult
{
    bool ok;
    std::vector<SurfacePtr> surfaces;
};
*/


bool parseObj(std::string filename, MeshDescription *);


#endif // DEATHRAY_OBJPARSER_H_
