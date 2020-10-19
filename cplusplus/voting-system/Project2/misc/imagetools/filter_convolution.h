/**
   Author Philip Siedlecki
   Copyright 2018
   Desigened by 3081 Professors
 */

#ifndef IMAGETOOLS_FILTER_CONVOLUTION_H_
#define IMAGETOOLS_FILTER_CONVOLUTION_H_


#include "imagetools/float_matrix.h"
#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"
#include "imagetools/filter.h"

namespace image_tools {

/** @brief A subset of the filter class, these filters operate on a copy
    of the pixel buffer.
 */
class ConvolutionFilter : public Filter {
 public:
  /** @brief Initialize the kernel, this should be overriden.
   */
  ConvolutionFilter();
  
  // Set kernel_
  void SetKernel(FloatMatrix * kernel);

  // Getter for kernel_
  FloatMatrix * GetKernel();

  /** @brief Creates a kernel given parameters, or private vars.
   */
  virtual FloatMatrix * CreateKernel();

  /** @brief Hook, this is called before applying the filter.
   */
  void SetupFilter() override;

  // Calculate a pixels color based on the kernel
  ColorData CalculateFilteredPixel(const PixelBuffer &buffer,
                                   int x, int y) override;

  /** Each subclass will create a new pointer that kernel_ will
   * be assigned. The cleanupFilter() will delete the space
   *created by the subclasses for this kernel_. */
  /** @brief Hook, this is called after applying the filter.
   */
  void CleanupFilter() override;

  /** @brief Returns false so filter will read data from a copy
      and over-write buffer.
  */
  bool can_calculate_in_place() override;

 private:
  FloatMatrix * kernel_;  // Store a constructor generated kernel
};

}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_CONVOLUTION_H_
