#ifndef DEATHRAY_OBJECT_H_
#define DEATHRAY_OBJECT_H_

#include <memory>
#include "ray.h"

class Object
{
public:
    virtual bool hit(const Ray &ray) const = 0;
};


typedef std::shared_ptr<Object> ObjectPtr;

#endif // DEATHRAY_OBJECT_H_
