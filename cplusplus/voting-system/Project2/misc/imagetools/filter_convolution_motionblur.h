/**
   Author Philip Siedlecki
   Copyright 2018
   Desigened by 3081 Professors
*/

#ifndef IMAGETOOLS_FILTER_CONVOLUTION_MOTIONBLUR_H_
#define IMAGETOOLS_FILTER_CONVOLUTION_MOTIONBLUR_H_

#include <string>

#include "imagetools/filter_convolution.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"

namespace image_tools {

/** @brief Given a radius and direction, create a motion blur kernel
    and apply it to the pixel buffer.
 */
class ConvolutionFilterMotionBlur : public ConvolutionFilter {
 public:
  ConvolutionFilterMotionBlur() {}

  /** @brief Set radius_ and dir_ given the input parameters
      Create and set kernel_.
  */
  ConvolutionFilterMotionBlur(float rad, std::string dir);

  /** @brief Create a motion blur kernel given the radius_ and dir_
   */
  FloatMatrix * CreateKernel() override;
 private:
  // Pass in these values from the constructor for later use
  int radius_;
  std::string dir_;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_CONVOLUTION_MOTIONBLUR_H_
