#ifndef DEATHRAY_PROGRESSBAR_H_
#define DEATHRAY_PROGRESSBAR_H_

#include <chrono>
#include "scene/scene.h"


class ProgressBar {
private:
    std::chrono::system_clock::time_point start_point;
    int total_pixels_;
    int pixels_per_update_;

public:
    void start(const ScenePtr& info);
    void update(float progress);
    void finish();

    int pixels_per_update() const;
};

#endif // DEATHRAY_PROGRESSBAR_H_
