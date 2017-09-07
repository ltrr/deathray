#include "scene/renderer.h"

#include "util/blue.h"


Image Renderer::render(const RenderInfo& info, ProgressBar& progress)
{
    float* blue = getblue(info.num_samples);
    if (!blue) {
        std::cerr << "error: invalid number of samples ("
                  << info.num_samples << ")" << std::endl;
        exit(1);
    }

    int rows = info.viewport->height();
    int cols = info.viewport->width();

    int update_period = progress.pixels_per_update();

    Image im(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Color3f color;
            for (int k = 0; k < info.num_samples; k++) {
                float id = i + blue[k << 1];
                float jd = j + blue[(k << 1) + 1];
                Vec3 uv = info.viewport->pixelToWindow(id, jd);
                Ray ray = info.camera->windowToRay(uv);
                //TODO: use correct gamma combination
                color += info.shader->colorAt(info.scene, ray);
            }
            color /= info.num_samples;
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
