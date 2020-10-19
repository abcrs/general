// Author: Philip Siedlecki
// Copyright: 2018
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"
#include "imagetools/filter.h"
#include "imagetools/filter_saturate.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {

  // Constructor
  FilterSaturate::FilterSaturate(float s_value) {
    s_value_ = s_value;
  }

  ColorData FilterSaturate::CalculateFilteredPixel(const PixelBuffer &buffer,
                                                   int x, int y) {
    ColorData current_pixel = buffer.pixel(x, y);
    float lum = current_pixel.Luminance();
    ColorData gray_scale = ColorData(lum, lum, lum);
    return ImageToolsMath::Lerp(gray_scale, current_pixel, s_value_);
  }

}  // namespace image_tools
