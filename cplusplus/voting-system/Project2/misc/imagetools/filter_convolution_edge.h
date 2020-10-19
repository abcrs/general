/**
   Author Philip Siedlecki
   Copyright 2018
   Desigened by 3081 Professors
*/

#ifndef IMAGETOOLS_FILTER_CONVOLUTION_EDGE_H_
#define IMAGETOOLS_FILTER_CONVOLUTION_EDGE_H_

#include "imagetools/filter_convolution.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"
#include "imagetools/float_matrix.h"

namespace image_tools {

/** @brief Apply an edge detection kernel to the pixel buffer.
 */
class ConvolutionFilterEdge : public ConvolutionFilter {
 public:
  /** @breif Set the kernel to CreateKernel.
   */
  ConvolutionFilterEdge();
  
  /** @brief Create an edge detection kernel.
   */
  FloatMatrix * CreateKernel() override;
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_CONVOLUTION_EDGE_H_
