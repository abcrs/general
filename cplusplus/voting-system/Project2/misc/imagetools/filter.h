/**
Author Philip Siedlecki
Copyright 2018
Desigened by 3081 Professors
 */

#ifndef IMAGETOOLS_FILTER_H_
#define IMAGETOOLS_FILTER_H_

#include "imagetools/pixel_buffer.h"
#include "imagetools/color_data.h"

namespace image_tools {

  
class Filter {
 public:
  /** ApplyToBuffer() is a template method that defines the key recipe for filtering:
   * 1. Create a temp copy of the buffer if not_can_copy_in_place()
   * 2. SetupFilter()
   * 3. Use a double for loop to loop through every pixel in the buffer
   * 4. Call CalculateFilteredPixel() for each pixel
   * 5. CleanupFilter()
   * 
   * The virtual methods in the base class allow subclasses to fill in the
   * implementation details for the key steps. */
  
  /** @brief Apply CalculateFilteredPixel to each pixel in the buffer
   */
  virtual void ApplyToBuffer(PixelBuffer * buffer);

  /** @brief A hook, this code will execute before the filter calculation
   */
  virtual void SetupFilter();

  /** @brief Return the ColorData that (x, y) should be.
   */
  virtual ColorData CalculateFilteredPixel(const PixelBuffer &buffer,
                                           int x, int y);

  /** @brief A hook, this code will execute after the filter calculation
   */
  virtual void CleanupFilter();

  /** @brief Return false to create a copy of the canvas
   */
  virtual bool can_calculate_in_place();
};
}  // namespace image_tools

#endif  // IMAGETOOLS_FILTER_H_
