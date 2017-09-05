#ifndef DEATHRAY_OBJPARSER_H_
#define DEATHRAY_OBJPARSER_H_

#include <vector>
#include "material.h"
#include "triangle.h"

struct ObjParserResult
{
    bool ok;
    std::vector<SurfacePtr> surfaces;
};


ObjParserResult parseObj(std::string filename);


#endif // DEATHRAY_OBJPARSER_H_
