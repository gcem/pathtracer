#include "PNGExporter.hpp"
#include <libpng/png.h>

namespace Image {
bool
PNGExporter::exportImage(Image<unsigned char>& image, std::string filename)
{
    // about all of this code is taken from libpng manual

    FILE* fp = fopen(filename.c_str(), "wb");
    if (!fp)
        return false;

    png_structp pngStructPtr =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!pngStructPtr)
        return false;

    png_infop pngInfoPtr = png_create_info_struct(pngStructPtr);
    if (!pngInfoPtr) {
        png_destroy_write_struct(&pngStructPtr, nullptr);
        return false;
    }

    png_init_io(pngStructPtr, fp);

    png_set_IHDR(pngStructPtr,
                 pngInfoPtr,
                 image.getWidth(),
                 image.getHeight(),
                 8,
                 PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    auto rowPointers = image.rowPointers();
    png_set_rows(pngStructPtr, pngInfoPtr, &rowPointers.front());
    png_write_png(pngStructPtr, pngInfoPtr, PNG_TRANSFORM_IDENTITY, NULL);
    png_write_end(pngStructPtr, pngInfoPtr);

    png_destroy_write_struct(&pngStructPtr, &pngInfoPtr);
    return true;
}
}