#include "ImageExporter.hpp"
#include <string>

namespace Image {
/**
 * @brief Saves an Image to a file
 *
 */
class PNGExporter : public ImageExporter
{
public:
    /**
     * @brief Export image to a file with given name
     *
     * @param image
     * @param filename
     * @return true Success
     * @return false Failure
     */
    bool exportImage(Image<unsigned char>& image,
                     std::string filename) override;
};
}