/**
   Author Philip Siedlecki
   Copyright 2018
   Desigened by 3081 Professors
 */

#ifndef IMAGETOOLS_FILTER_CONVOLUTION_SHARPEN_H_
#define IMAGETOOLS_FILTER_CONVOLUTION_SHARPEN_H_

#include "imagetools/filter_convolution.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  
/** @brief Apply a sharpen kernel with the given radius to the pixel buffer
 */
class ConvolutionFilterSharpen : public ConvolutionFilter {
 public:
  ConvolutionFilterSharpen() {}

  /** @brief Set rad_ to rad, initialize kernel_.
   */
  explicit ConvolutionFilterSharpen(float rad);

  /** @brief Create a guassian sharpen kernel based on rad_
   */
  FloatMatrix * CreateKernel() override;
 private:
  int rad_;  // Initialize rad in constructor use throughout
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_CONVOLUTION_SHARPEN_H_
