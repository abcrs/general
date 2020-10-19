// Author: Philip Siedlecki
// Copyright: 2018

#include "imagetools/color_data.h"
#include "imagetools/filter.h"
#include "imagetools/filter_channels.h"

namespace image_tools {

  // Constructor
  FilterChannels::FilterChannels(float red, float green, float blue) {
    red_ = red;
    green_ = green;
    blue_ = blue;
  }

  ColorData FilterChannels::CalculateFilteredPixel(const PixelBuffer &buffer,
                                                   int x, int y) {
    ColorData current_pixel = buffer.pixel(x, y);

    float old_red = current_pixel.red();
    float old_green = current_pixel.green();
    float old_blue = current_pixel.blue();

    // Multiply by the constructor values
    old_red *= red_;
    old_green *= green_;
    old_blue *= blue_;

    ColorData new_color = ColorData(old_red, old_green, old_blue);
    return new_color;
  }
}  // namespace image_tools
