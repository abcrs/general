// Author: Philip Siedlecki
// Copyright: 2018

#include "imagetools/color_data.h"
#include "imagetools/filter.h"
#include "imagetools/filter_quantize.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {

  // Constructor
  FilterQuantize::FilterQuantize(int buckets) {
    buckets_ = buckets;
  }

  // Given a color return the new color, acording to num of bins
  float FilterQuantize::SelectBin(float color) {
    float last_val = 0;
    float cur_val;

    // May need to adjust for round off errors
    for (int i = 1; i <= buckets_ - 1; i++) {
      // This will generate cut off values at even intervals
      cur_val = static_cast<float>(i) / static_cast<float>(buckets_ - 1);
      if (color < cur_val) {  // The color fits between two buckets
        if ((color - last_val) < (cur_val - color)) {
          return last_val;
        } else {  // if the color is equa-distance, return the greater bin
          return cur_val;
        }
      }
      last_val = cur_val;
    }
    return 1.0;  // 1.0 is last bucket, only value color could be here
  }

  ColorData FilterQuantize::CalculateFilteredPixel(const PixelBuffer &buffer,
                                                   int x, int y) {
    ColorData current_pixel = buffer.pixel(x, y);

    float d_red = current_pixel.red();
    float d_green = current_pixel.green();
    float d_blue = current_pixel.blue();

    d_red = SelectBin(d_red);
    d_green = SelectBin(d_green);
    d_blue = SelectBin(d_blue);

    return ColorData(d_red, d_green, d_blue);
  }
}  // namespace image_tools
