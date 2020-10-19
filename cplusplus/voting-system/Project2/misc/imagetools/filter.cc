// Author: Philip Siedlecki
// Copyright: 2018
#include "imagetools/color_data.h"
#include "imagetools/filter.h"
#include "imagetools/pixel_buffer.h"

namespace image_tools {

  // Given a pixel buffer, apply the filter to each pixel
  void Filter::ApplyToBuffer(PixelBuffer * buffer) {
    // temp will be the untouched copy, using it for original data
    PixelBuffer * temp = buffer;
    if (!can_calculate_in_place()) {
      // using PixelBuffer copy constructor
      temp = new PixelBuffer(*buffer);
    }
    SetupFilter();

    int height = buffer->height();
    int width = buffer->width();

    // Apply the altered color value to each pixel in the buffer
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        ColorData color = CalculateFilteredPixel(*temp, x, y);
        color.Clamp();
        buffer->set_pixel(x, y, color);
      }
    }
    CleanupFilter();
    if (!can_calculate_in_place()) {
      delete temp;  // only delete if we use 'new'
    }
  }

  void Filter::SetupFilter() {
    return;
  }

  ColorData Filter::CalculateFilteredPixel(const PixelBuffer &buffer,
                                           int x, int y) {
    return buffer.pixel(x, y);  // No filter by default
  }

  void Filter::CleanupFilter() {
    return;
  }

  // Should be true by defualt
  bool Filter::can_calculate_in_place() { return true; }

}  // namespace image_tools
