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

#ifndef PNGPP_PNG_H
#define PNGPP_PNG_H

#include <cstdint>

namespace png
{
class rgb_pixel
{
public:
  rgb_pixel() : red(0), green(0), blue(0) {}
  rgb_pixel(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

class gray_pixel
{
public:
  gray_pixel() : value(0) {}
  gray_pixel(uint8_t value) : value(value) {}
  uint8_t value;

  virtual operator uint8_t() const { return value; }
};

template <class TPixel>
class row_access
{
public:
  row_access() : pixel(TPixel()) {}
  virtual TPixel& operator[](size_t index) { (void)index; return pixel; }
  virtual TPixel const& operator[](size_t index) const { (void)index; return pixel; }

private:
  TPixel pixel;
};

template <class TPixel> class image;
extern image<rgb_pixel> * image_mock_instance;

template <class TPixel>
class image
{
public:
  image(const char* filename) : row_access_object(row_access<TPixel>())
  {
    if(image_mock_instance != nullptr)
    {
      image_mock_instance->calling_image_constructor(filename);
    }
  }
  image(size_t width, size_t height) : row_access_object(row_access<TPixel>()) { (void)width; (void)height; }
  virtual void write(const char* filename) { (void)filename; }
  virtual size_t get_width() const { return 0; }
  virtual size_t get_height() const { return 0; }
  virtual row_access<TPixel>& operator[](size_t index) { (void)index; return row_access_object; }
  virtual row_access<TPixel> const& operator[](size_t index) const { (void)index; return row_access_object; }

  virtual void calling_image_constructor(const char* filename) { (void)filename; }
  virtual void calling_image_constructor(size_t width, size_t height) { (void)width; (void)height; }

private:
  row_access<TPixel> row_access_object;
};
}

#endif // PNGPP_PNG_H
