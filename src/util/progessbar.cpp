#include "util/progressbar.h"

#include <iostream>
#include <iomanip>
using namespace std::chrono;


//void ProgressBar::start(std::string filename, const RenderInfo& info)
void ProgressBar::start(const ScenePtr& scene)
{
    start_point = system_clock::now();
    auto& vp = scene->viewport();
    pixels_per_update_ = (vp->width() * vp->height()) / 200;

    std::ios_base::sync_with_stdio(false);

    std::cout << "Rendering " << scene->outputConfig()->filename << "\n"
              << "(" << scene->surfaces().size() << " surfaces, "
              << scene->lights().size() << " lights)" << std::endl;
}


int ProgressBar::pixels_per_update() const
{
    return pixels_per_update_;
}


void ProgressBar::update(float progress)
{
    std::cout << std::setprecision(1) << std::fixed
              << "progress: " << progress * 100 << "%\r"
              << std::flush;
}


void ProgressBar::finish()
{
    auto finish_point = system_clock::now();
    duration<double> diff = finish_point - start_point;
    std::cout << "\nrendered in " << std::setprecision(2) << diff.count() << " s\n";
}
