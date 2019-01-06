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

#include <algorithm>
#include <vector>

#include <png++/png.hpp>

#include <tl/Exception.h>
#include <tl/Filter.h>
#include <tl/filters/common.h>
#include <tl/filters/gaussian.h>
#include <utils/bound.h>

#include <tl/sharp_spots_image_reconstruction-internal.h>

namespace tl
{
namespace internal
{
Gray_pixel rgb_to_gray(Rgb_pixel rgb_pixel)
{
  return Gray_pixel(((uint32_t)rgb_pixel.red + (uint32_t)rgb_pixel.green + (uint32_t)rgb_pixel.blue) / 3);
}

Rgb_images read_images(const tl::List_of_filenames filenames)
{
  Rgb_images images;
  for(auto image_filename : filenames)
  {
    images.push_back(Rgb_image(image_filename));
  }
  return images;
}

Gray_images create_gray_images_from_rgb_images(const Rgb_images& rgb_images)
{
  Gray_images gray_images;

  for(auto rgb_image : rgb_images)
  {
    Gray_image gray_image(rgb_image.get_width(), rgb_image.get_height());
    for(int32_t y = 0; y < (int32_t)rgb_image.get_height(); y++)
    {
      for(int32_t x = 0; x < (int32_t)rgb_image.get_width(); x++)
      {
        gray_image[y][x] = rgb_to_gray(rgb_image[y][x]);
      }
    }
    gray_images.push_back(gray_image);
  }
  return gray_images;
}

Rgb_image create_image_from_sharp_spots_masks_and_origin_images(const Gray_images& sharp_spots_masks,
                                                                const Rgb_images& origin_images)
{
  if(sharp_spots_masks.size() != origin_images.size())
  {
    throw tl::Exception("Sharp spot  masks count should be the same as origin images.");
  }

  int32_t width = (int32_t)origin_images[0].get_width();
  int32_t height = (int32_t)origin_images[0].get_height();
  Rgb_image output_image(width, height);

  for(int32_t y = 0; y < height; y++)
  {
    for(int32_t x = 0; x < width; x++)
    {
      auto it = std::max_element(sharp_spots_masks.begin(),
                                 sharp_spots_masks.end(),
                                 [x, y](const Gray_image& a,
                                        const Gray_image& b)
                                 {
                                   return a[y][x] < b[y][x];
                                 });
      int32_t best_sharpness_level_idx = it - sharp_spots_masks.begin();
      output_image[y][x] = origin_images[best_sharpness_level_idx][y][x];
    }
  }
  return output_image;
}
}

Gray_image create_gray_depth_image_from_ordered_sharp_spots_masks(const Gray_images& sharp_spots_masks)
{
  uint8_t depth_step = 255 / sharp_spots_masks.size();
  int32_t width = (int32_t)sharp_spots_masks[0].get_width();
  int32_t height = (int32_t)sharp_spots_masks[0].get_height();
  Gray_image output_image(width, height);

  for(int32_t y = 0; y < height; y++)
  {
    for(int32_t x = 0; x < width; x++)
    {
      auto it = std::max_element(sharp_spots_masks.begin(),
                                 sharp_spots_masks.end(),
                                 [x, y](const Gray_image& a,
                                        const Gray_image& b)
                                 {
                                   return a[y][x] < b[y][x];
                                 });
      int32_t best_sharpness_level_idx = sharp_spots_masks.end() - it;
      output_image[y][x] = best_sharpness_level_idx * depth_step;
    }
  }
  return output_image;
}
}

void tl::sharp_spots_image_reconstruction(const List_of_filenames input_filenames, const char* output_filename, const char* output_depth_filename)
{
  Rgb_images origin_images = read_images(input_filenames);
  Gray_images sharp_spots_masks = create_gray_images_from_rgb_images(origin_images);
  apply_filter_on_gray_images<int32_t>(sharp_spots_masks,
                                       tl::Filter<int32_t>(tl::filters::SOBEL_N,
                                                           tl::filters::SOBEL_SIZE,
                                                           [](int32_t n)
                                                           {
                                                             return (n > 255) ? 255 : abs(n);
                                                           }));
  apply_filter_on_gray_images<double>(sharp_spots_masks,
                                      tl::Filter<double>(tl::filters::GAUSSIAN,
                                                         tl::filters::GAUSSIAN_SIZE));

  Rgb_image output_image = create_image_from_sharp_spots_masks_and_origin_images(sharp_spots_masks,
                                                                                 origin_images);
  output_image.write(output_filename);

  Gray_image output_depth_image = create_gray_depth_image_from_ordered_sharp_spots_masks(sharp_spots_masks);
  output_depth_image.write(output_depth_filename);
}
