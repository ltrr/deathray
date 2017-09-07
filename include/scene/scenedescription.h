#ifndef DEATHRAY_SCENEDESCRIPTION_H_
#define DEATHRAY_SCENEDESCRIPTION_H_

#include <string>
#include <lua.h>
#include "util/vector.h"


class SceneDescription
{
private:
    lua_State *L;

    SceneDescription(lua_State *L);

public:
    ~SceneDescription();

    template<typename T>
    T getSetting(const std::string& name) const;

    template<typename T>
    T getSetting(const std::string& name, const T& default_) const;

    static SceneDescription fromFile(const std::string& filename);
};

#endif // DEATHRAY_SCENEDESCRIPTION_H_
