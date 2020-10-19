/**
   Author Philip Siedlecki
   Copyright 2018
   Desigened by 3081 Professors
*/

#ifndef IMAGETOOLS_FILTER_CONVOLUTION_BLUR_H_
#define IMAGETOOLS_FILTER_CONVOLUTION_BLUR_H_

#include "imagetools/filter_convolution.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"

namespace image_tools {
  
/** @brief Create a copy of the piel buffer, apply a gaussian blur
    in the given radius.
 */
class ConvolutionFilterBlur : public ConvolutionFilter {
 public:
  ConvolutionFilterBlur() {}

  /** @brief Create a guassian blur Kernel with the given radius.
   */
  explicit ConvolutionFilterBlur(float radius);

  /** @brief Using radius_, create a gaussian blur kernel.
   */
  FloatMatrix * CreateKernel() override;
 private:
  int radius_;  // store radius passed into constructor
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_CONVOLUTION_BLUR_H_
