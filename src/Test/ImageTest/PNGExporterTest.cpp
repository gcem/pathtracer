#include "PNGExporter.hpp"
#include <gtest/gtest.h>

namespace Image {
namespace Test {
TEST(PNGExporterTest, ExportSmallPNG)
{
    /**
     * Exports a 5 by 3 image. It should look like:
     *
     * r k k k k
     * k k g k k
     * k b k k k
     *
     */

    Image<unsigned char> image(5, 3);
    image.setPixel(0, 0, { 255, 0, 0 });
    image.setPixel(2, 1, { 0, 255, 0 });
    image.setPixel(1, 2, { 0, 0, 255 });
    PNGExporter exporter;
    exporter.exportImage(image, "ExportSmallPNGResult.png");
}
}
}