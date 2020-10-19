// Author Philip Siedlecki
// Copyright 2018
// Desigened by 3081 Professors

#include "imagetools/filter_convolution_edge.h"
#include "imagetools/float_matrix.h"

namespace image_tools {

  ConvolutionFilterEdge::ConvolutionFilterEdge() {
    SetKernel(CreateKernel());
  }

  FloatMatrix * ConvolutionFilterEdge::CreateKernel() {
    FloatMatrix *  kernel = new FloatMatrix(1);  // 3 * 3
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        kernel->set_value(x, y, -1.0);
      }
    }
    // set center value
    kernel->set_value(1, 1, 8.0);
    return kernel;
  }

}  // namespace image_tools
