// Author Philip Siedlecki
// Copyright 2018
// Desigened by 3081 Professors

#include "imagetools/filter_convolution_motionblur.h"

#include <math.h>

namespace image_tools {

  ConvolutionFilterMotionBlur::
  ConvolutionFilterMotionBlur(float rad, std::string dir) {
    radius_ = static_cast<int>(round(rad));
    dir_ = dir;
    SetKernel(CreateKernel());
  }

  FloatMatrix * ConvolutionFilterMotionBlur::CreateKernel() {
    FloatMatrix * kernel = new FloatMatrix(radius_);
    for (int i = 0; i < radius_ * 2 + 1; i++) {
      for (int j = 0; j < radius_ * 2 + 1; j++) {
        kernel->set_value(j, i, 0.0);  // 0 out the matrix
      }
    }
    // Place a row of 1's deppending on the direction in dir
    if (dir_ == "North/South") {
      for (int i = 0; i < radius_ * 2 + 1; i++) {
        kernel->set_value(radius_, i, 1.0);
      }
    } else if (dir_ == "East/West") {
      for (int i = 0; i < radius_ * 2 + 1; i++) {
        kernel->set_value(i, radius_, 1.0);
      }
    } else if (dir_ == "Northwest/Southeast") {
      for (int i = 0; i < radius_ * 2 + 1; i++) {
        kernel->set_value(i, i, 1.0);
      }
    } else if (dir_ == "Northeast/Southwest") {
      int diameter = radius_ * 2 + 1;
      for (int i = 0; i < diameter; i++) {
        kernel->set_value(i, diameter - i - 1, 1.0);
      }
    }
    kernel->Normalize();
    return kernel;
  }
}  // namespace image_tools
