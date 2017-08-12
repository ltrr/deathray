#ifndef DEATHRAY_SCENE_DESCRIPTION_H_
#define DEATHRAY_SCENE_DESCRIPTION_H_

#include <string>
#include <lua.h>
#include "vector.h"

class SceneDescription {
private:
    lua_State *L;

    SceneDescription(lua_State *L);

public:
    ~SceneDescription();

    template<typename T>
    T getsetting(const std::string& name) const;

    template<typename T>
    T getsetting(const std::string& name, const T& default_) const;

    static SceneDescription fromfile(const std::string& filename);
};

#endif // DEATHRAY_SCENE_DESCRIPTION_H_
