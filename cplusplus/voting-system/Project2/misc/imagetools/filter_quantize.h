/**
   Author Philip Siedlecki
   Copyright 2018
   Desigened by 3081 Professors
 */

#ifndef IMAGETOOLS_FILTER_QUANTIZE_H_
#define IMAGETOOLS_FILTER_QUANTIZE_H_

#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"

namespace image_tools {

/** @brief This filter rounds each pixel to the nearest bucket.
 */ 
class FilterQuantize : public Filter{
 public:
  FilterQuantize() {}

  // Set buckets_ to buckets
  /** @brief Set the number of buckets.
   */
  explicit FilterQuantize(int buckets);

  /** @brief Place each pixel in the buffer into a bucket.
   */
  ColorData CalculateFilteredPixel(const PixelBuffer &buffer,
                                   int x, int y) override;

 private:
  int buckets_;  // number of buckets passed in by user

  /** return the color rounded to the nearest bin
   */
  float SelectBin(float color);
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_QUANTIZE_H_
