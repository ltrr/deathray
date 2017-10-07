#ifndef DEATHRAY_MATERIAL_H_
#define DEATHRAY_MATERIAL_H_

#include <memory>
#include "util/vector.h"


class Material
{
public:
    virtual ~Material() { }
};


typedef std::shared_ptr<Material> MaterialPtr;

#endif // DEATHRAY_MATERIAL_H_
