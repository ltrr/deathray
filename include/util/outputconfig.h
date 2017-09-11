#ifndef DEATHRAY_OUTPUTCONFIG_H_
#define DEATHRAY_OUTPUTCONFIG_H_

#include <memory>


enum class ImageFormat { PPM };
enum class ImageCodification { BINARY, ASCII };


class OutputConfig
{
public:
    ImageFormat format;
    ImageCodification codification;
    std::string filename;

    OutputConfig(std::string filename,
        ImageFormat format = ImageFormat::PPM,
        ImageCodification codification = ImageCodification::BINARY)
        : filename(filename), format(format), codification(codification) {}
};


typedef std::shared_ptr<OutputConfig> OutputConfigPtr;

#endif // DEATHRAY_OUTPUTCONFIG_H_
