
//! @file svg_to_png.hpp
#ifndef __svg_svg_to_png_hpp__
#define __svg_svg_to_png_hpp__

#include <fstream>

namespace svg {
    //! Convert SVG file to PNG file.
    //! @param svg_file Name of SVG file.
    //! param png_file Name of PNG file.
    void
    svg_to_png(const std::string &svg_file, const std::string &png_file);
}
#endif
