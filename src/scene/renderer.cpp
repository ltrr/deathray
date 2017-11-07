#include "scene/renderer.h"

#include "util/blue.h"


Image Renderer::render(const ScenePtr& scene, ProgressBar& progress)
{
    auto& viewport = scene->viewport();
    auto& camera = scene->camera();
    auto& shader = scene->shader();
    int sample_count = scene->sampleCount();

    float* blue = getblue(sample_count);
    if (!blue) {
        std::cerr << "error: invalid number of samples ("
                  << sample_count << ")" << std::endl;
        exit(1);
    }

    int rows = viewport->height();
    int cols = viewport->width();
    int update_period = progress.pixels_per_update();

    //scene->accelerate();

    Image im(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Color3f color;
            for (int k = 0; k < sample_count; k++) {
                float id = i + blue[k << 1];
                float jd = j + blue[(k << 1) + 1];
                Vec3 uv = viewport->pixelToWindow(id, jd);
                Ray ray = camera->windowToRay(uv);
                //TODO: use correct gamma combination
                color += shader->colorAt(scene, ray);
            }
            color /= sample_count;
            im(i, j) = sqrt(color); // gamma correction

            int n = i*cols + j;
            if (n % update_period == 0) {
                progress.update(float(i*cols + j) / (rows*cols));
            }
        }
    }
    progress.update(1);

    return im;
}
