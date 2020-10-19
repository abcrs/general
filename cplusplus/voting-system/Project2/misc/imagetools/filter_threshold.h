/**
   Author Philip Siedlecki
   Copyright 2018
   Desigened by 3081 Professors
*/

#ifndef IMAGETOOLS_FILTER_THRESHOLD_H_
#define IMAGETOOLS_FILTER_THRESHOLD_H_

#include "imagetools/filter.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"

namespace image_tools {

/** @brief Round all pixels in the pixel buffer that are below the threshold
    to zero, above to black.
    
 */
class FilterThreshold : public Filter {
 public:
  FilterThreshold() {}

  /** @brief  Set threshold_ to threshold passed by user.
   */
  explicit FilterThreshold(float threshold);

  /** @brief Round each pixel to 0 or 1 relative to the threshold.
   */
  ColorData CalculateFilteredPixel(const PixelBuffer &buffer,
                                   int x, int y) override;

 private:
  // CalculateColorValue will round up / down based on theshold
  float CalculateColorValue(float color, float threshold);
  float threshold_;  // passed in by user
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_THRESHOLD_H_
