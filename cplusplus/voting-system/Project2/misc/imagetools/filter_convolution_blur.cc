// Author Philip Siedlecki
// Copyright 2018
// Desigened by 3081 Professors

#include <math.h>
#include "imagetools/filter_convolution.h"
#include "imagetools/filter_convolution_blur.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {

  ConvolutionFilterBlur::ConvolutionFilterBlur(float radius) {
    radius_ = static_cast<int>(round(radius));
    SetKernel(CreateKernel());
  }

  FloatMatrix * ConvolutionFilterBlur::CreateKernel() {
    FloatMatrix * kernel = new FloatMatrix(radius_);
    float distance;
    // using gaussian blur, x = rad y = rad is the center
    for (int y = 0; y < radius_ * 2 + 1; y++) {
      for (int x = 0; x < radius_ * 2 + 1; x++) {
        // distance from center to current x, y position
        distance = sqrt(pow((radius_ - x), 2.0) + pow((radius_ - y), 2.0));
        kernel->set_value(x, y, ImageToolsMath::Gaussian(distance, radius_));
      }
    }
    kernel->Normalize();
    return kernel;
  }
}  // namespace image_tools
