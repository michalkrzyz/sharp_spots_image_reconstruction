// BSD 3-Clause License
//
// Copyright (c) 2019, michalkrzyz
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef TL_SHARP_SPOTS_IMAGE_RECONSTRUCTION_INTERNAL_H
#define TL_SHARP_SPOTS_IMAGE_RECONSTRUCTION_INTERNAL_H

#include <png++/png.hpp>

#include <tl/sharp_spots_image_reconstruction.h>

namespace tl
{
namespace internal
{
using Rgb_image = png::image<png::rgb_pixel>;
using Rgb_images = std::vector<Rgb_image>;
using Rgb_pixel = png::rgb_pixel;
using Gray_image = png::image<png::gray_pixel>;
using Gray_images = std::vector<Gray_image>;
using Gray_pixel = png::gray_pixel;

Gray_pixel rgb_to_gray(Rgb_pixel rgb_pixel);
Rgb_images read_images(const tl::List_of_filenames filenames);
Gray_images create_gray_images_from_rgb_images(const Rgb_images& rgb_images);

template <class TData>
Gray_image filter_gray_image(const Gray_image& image, const tl::Filter<TData> filter)
{
  Gray_image output_image(image.get_width(), image.get_height());
  int32_t width = (int32_t)image.get_width();
  int32_t height = (int32_t)image.get_height();

  for(int32_t y = 0; y < height; y++)
  {
    for(int32_t x = 0; x < width; x++)
    {
      TData pixel = 0;
      for(int32_t fy = 0; fy < filter.N; fy++)
      {
        int32_t cy = utils::bound<int32_t>(y + fy - filter.center, 0, height - 1);
        for(int32_t fx = 0; fx < filter.N; fx++)
        {
          int32_t cx = utils::bound<int32_t>(x + fx - filter.center, 0, width - 1);
          pixel += filter.get_data(fx, fy) * (TData)image[cy][cx];
        }
      }
      pixel = filter.convert(pixel);
      output_image[y][x] = pixel;
    }
  }

  return output_image;
}

template <class TData>
void apply_filter_on_gray_images(Gray_images& gray_images, const tl::Filter<TData> filter)
{
  for(auto& image : gray_images)
  {
    image = filter_gray_image<TData>(image, filter);
  }
}

Rgb_image create_image_from_sharp_spots_masks_and_origin_images(const Gray_images& sharp_spots_masks,
                                                                const Rgb_images& origin_images);
Gray_image create_gray_depth_image_from_ordered_sharp_spots_masks(const Gray_images& sharp_spots_masks);
}
}

using namespace tl::internal;

#endif // TL_SHARP_SPOTS_IMAGE_RECONSTRUCTION_H
