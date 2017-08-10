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

template<>
std::string SceneDescription::getsetting<std::string>(
    const std::string& name) const;

template<>
std::string SceneDescription::getsetting<std::string>(
    const std::string& name,
    const std::string& default_) const;

template<>
float SceneDescription::getsetting<float>(
    const std::string& name) const;

template<>
float SceneDescription::getsetting<float>(
    const std::string& name,
    const float& default_) const;

template<>
Vec3 SceneDescription::getsetting<Vec3>(
    const std::string& name) const;

template<>
Vec3 SceneDescription::getsetting<Vec3>(
    const std::string& name,
    const Vec3& default_) const;


#endif // DEATHRAY_SCENE_DESCRIPTION_H_
