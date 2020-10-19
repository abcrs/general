// Author: Philip Siedlecki
// Copyright: 2018

#include "imagetools/color_data.h"
#include "imagetools/filter.h"
#include "imagetools/filter_threshold.h"

namespace image_tools {

  // Constructor
  FilterThreshold::FilterThreshold(float threshold) {
    threshold_ = threshold;
  }

  // return a color value based on the threshold
  float FilterThreshold::CalculateColorValue(float color, float threshold) {
    if (color <= threshold) {
      return 0.0;
    } else {
      return 1.0;
    }
  }

  ColorData FilterThreshold::CalculateFilteredPixel(const PixelBuffer &buffer,
                                                    int x, int y) {
    ColorData current_pixel = buffer.pixel(x, y);

    float d_red = current_pixel.red();
    float d_green = current_pixel.green();
    float d_blue = current_pixel.blue();

    float average = (d_red + d_green + d_blue) / 3.0;

    d_red = CalculateColorValue(average, threshold_);
    d_green = CalculateColorValue(average, threshold_);
    d_blue = CalculateColorValue(average, threshold_);

    return ColorData(d_red, d_green, d_blue);
  }

}  // namespace image_tools
