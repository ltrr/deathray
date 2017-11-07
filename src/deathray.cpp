/*#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "scene/scenedescription.h"
#include "scene/camera.h"
#include "scene/viewport.h"
#include "scene/renderer.h"
#include "scene/scene.h"
#include "shader/raytracer.h"
#include "shader/debug.h"
#include "util/image.h"
#include "util/progressbar.h"
#include "util/transform.h"
using std::string;
using std::shared_ptr;


void render(char* filename)
{
    // Load settings
    SceneDescription sd = SceneDescription::fromFile(filename);
    auto scene = sd.getSetting<ScenePtr>("scene");

    ProgressBar progress;
    progress.start(scene);

    std::cerr << "ns = " << scene->sampleCount() << '\n';

    Renderer renderer;
    Image image(renderer.render(scene, progress));

    progress.finish();

    auto& config = scene->outputConfig();

    if (config->codification == ImageCodification::BINARY) {
        std::ofstream out(config->filename, std::ofstream::out | std::ofstream::binary);
        image.writePpmBin(out);
        out.close();
    }
    else {
        std::ofstream out(config->filename, std::ofstream::out);
        image.writePpmAscii(out);
        out.close();
    }
}


int main(int argc, char** argv)
{
    // Check args
    if (argc < 2) {
        std::cerr << "usage: deathray scenefile.lua [...]" << std::endl;
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        render(argv[i]);
    }

    return 0;
}
*/

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "description/scene.h"
#include "description/surface.h"
#include "description/light.h"
#include "description/camera.h"
#include "scene/scenebuilder.h"
#include "lua/scene.h"
#include "util/image.h"
#include "util/progressbar.h"
#include "scene/renderer.h"


class Observer : public SceneDescriptionVisitor
{
    void onSurface(const SurfaceDescription *surf)
    {
        switch (surf->getKind()) {
            case SurfaceKind::SPHERE:
                std::cout << "sphere" << '\n';
                break;

            case SurfaceKind::TRIANGLE:
                std::cout << "triangle" << '\n';
                break;

            case SurfaceKind::MESH:
                std::cout << "mesh" << '\n';
                break;
        }
    }

    void onLight(const LightDescription *)
    {
        std::cout << "light" << '\n';
    }

    void onCamera(const CameraDescription *cam)
    {
        std::cout << "camera" << '\n';
    }

    void onEnterTransform(const Transform&)
    {
        std::cout << "enter transform" << '\n';
    }

    void onExitTransform()
    {
        std::cout << "exit transform" << '\n';
    }
};


void render(char* filename)
{
    // Load settings
    //SceneDescription sd = SceneDescription::fromFile(filename);
    // auto scene = sd.getSetting<ScenePtr>("scene");

    SceneDescriptionPtr desc = loadSceneDescription(filename);

    SceneDescriptionVisitor *v = new Observer();
    desc->visit(v);

    SceneBuilder sb;
    sb.start(desc);
    desc->visit(&sb);
    ScenePtr scene { sb.finish() };

    ProgressBar progress;
    progress.start(scene);



    //std::cerr << "ns = " << scene->sampleCount() << '\n';

    Renderer renderer;
    Image image(renderer.render(scene, progress));

    progress.finish();

    auto& config = scene->outputConfig();

    if (config->codification == ImageCodification::BINARY) {
        std::ofstream out(config->filename, std::ofstream::out | std::ofstream::binary);
        image.writePpmBin(out);
        out.close();
    }
    else {
        std::ofstream out(config->filename, std::ofstream::out);
        image.writePpmAscii(out);
        out.close();
    }
}


int main(int argc, char** argv)
{
    // Check args
    if (argc < 2) {
        std::cerr << "usage: deathray scenefile.lua [...]" << std::endl;
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        render(argv[i]);
    }

    return 0;
}
