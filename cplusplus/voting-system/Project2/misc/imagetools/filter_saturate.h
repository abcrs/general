/**
   Author Philip Siedlecki
   Copyright 2018
   Desigened by 3081 Professors
 */

#ifndef IMAGETOOLS_FILTER_SATURATE_H_
#define IMAGETOOLS_FILTER_SATURATE_H_

#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"
#include "imagetools/filter.h"

namespace image_tools {

/** @brief Linearly interpolate the pictue by a saturation value.
 */
class FilterSaturate : public Filter {
 public:
  FilterSaturate() {}

  /** @brief Set s_value_ (The amount to saturate by).
   */
  explicit FilterSaturate(float s_value);

  /** @brief Saturate each pixel in the buffer with by s_value_.
   */
  ColorData CalculateFilteredPixel(const PixelBuffer &buffer,
                                   int x, int y) override;
 private:
  float s_value_;  // saturate value passed in by saturate GUI
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_SATURATE_H_
