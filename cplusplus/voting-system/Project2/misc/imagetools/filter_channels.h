/**
   Author Philip Siedlecki
   Copyright 2018
   Desigened by 3081 Professors
*/

#ifndef IMAGETOOLS_FILTER_CHANNELS_H_
#define IMAGETOOLS_FILTER_CHANNELS_H_

#include "imagetools/filter.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"

namespace image_tools {
  
/** @brief Adjust each color channel in the pixel buffer by a
    percentage, given by RGB.
 */
class FilterChannels : public Filter {
 public:
  FilterChannels() {}

  /** @brief Initialize the channel values for R,G,B.
   */
  FilterChannels(float red, float green, float blue);

  /** Caluculate pixel using R,G,B values from constructor.
   */
  ColorData CalculateFilteredPixel(const PixelBuffer &buffer,
                                     int x, int y) override;

 private:
  // Store values passed into constructor
  float red_;
  float green_;
  float blue_;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_CHANNELS_H_
