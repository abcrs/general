// Author Philip Siedlecki
// Copyright 2018
// Desigened by 3081 Professors
#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"
#include "imagetools/filter_convolution.h"

namespace image_tools {
  ConvolutionFilter::ConvolutionFilter() {
    kernel_ = CreateKernel();
  }

  void ConvolutionFilter::SetKernel(FloatMatrix * kernel) {
    kernel_ = kernel;
  }

  FloatMatrix * ConvolutionFilter::GetKernel() {
    return kernel_;
  }

  // Defualt kernel will return the same picture
  FloatMatrix * ConvolutionFilter::CreateKernel() {
    return new FloatMatrix(0);  // create a 1 by 1 matrix
  }

  void ConvolutionFilter::SetupFilter(void) {
    return;
  }

  // The kernel will pull values from the other side of the buffer if it goes
  // Out of bounds
  ColorData ConvolutionFilter::
  CalculateFilteredPixel(const PixelBuffer &buffer, int x, int y) {
    int buf_width = buffer.width();
    int buf_height = buffer.height();
    int ker_width = kernel_->width();
    int ker_height = kernel_->height();

    // The upper left corner of the kernel
    int ker_x = x - (ker_width / 2);  // possible 1 off error
    int ker_y = y - (ker_height / 2);

    // buffer x, y under the kernel
    int cur_x = 0;
    int cur_y = 0;

    ColorData color_sum = ColorData(0, 0, 0);

    for (int i_x = 0; i_x < ker_width; i_x++) {
      for (int j_y = 0; j_y < ker_height; j_y++) {
        cur_x = ker_x + i_x;
        cur_y = ker_y + j_y;
        // Correct Horizontally
        if (cur_x < 0) {
          // the kernel is over the left side, wrap right
          cur_x += buf_width;
        } else if (cur_x >= buf_width) {
          // the kernel is over the right side, wrap left
          cur_x -= buf_width;
        }
        // Correct vertically
        if (cur_y < 0) {
          // the kernel is over the top, wrap to bottom
          cur_y += buf_height;
        } else if (cur_y >= buf_height) {
          // the kernel is over the bottom, wrap to the top
          cur_y -= buf_height;
        }
        // cur_x, cur_y are now mapped to the buffer
        // i_x j_y itterate over the kernel_ while cur_x, cur_y
        // itterate over the buffer. Sum each element from kernel * buffer
        color_sum = color_sum +
                    (buffer.pixel(cur_x, cur_y) * kernel_->value(i_x, j_y));
      }
    }
    // Make sure all values in color_sum are between 0 and 1
    color_sum.Clamp();
    return color_sum;
  }

  void ConvolutionFilter::CleanupFilter(void) {
    delete(kernel_);
    return;
  }

  bool ConvolutionFilter::can_calculate_in_place(void) { return false; }

}  // namespace image_tools
