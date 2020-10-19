// Author Philip Siedlecki
// Copyright 2018
// Desigened by 3081 Professors

#include <math.h>
#include "imagetools/filter_convolution_sharpen.h"
#include "imagetools/float_matrix.h"
#include "imagetools/image_tools_math.h"

namespace image_tools {

  ConvolutionFilterSharpen::ConvolutionFilterSharpen(float rad) {
    rad_ = static_cast<int>(round(rad));
    SetKernel(CreateKernel());
  }

  FloatMatrix * ConvolutionFilterSharpen::CreateKernel() {
    FloatMatrix *  kernel = new FloatMatrix(rad_);
    float distance;
    for (int y = 0; y < rad_ * 2 + 1; y++) {
      for (int x = 0; x < rad_ * 2 + 1; x++) {
        // distance from center to current x, y position
        distance = sqrt(pow((rad_ - x), 2.0) + pow((rad_ - y), 2.0));
        kernel->set_value(x, y, ImageToolsMath::Gaussian(distance, rad_));
      }
    }
    kernel->Normalize();
    kernel->Scale(-1.0);
    kernel->set_value(rad_, rad_, 2.0);  // set center value
    return kernel;
  }

}  // namespace image_tools
