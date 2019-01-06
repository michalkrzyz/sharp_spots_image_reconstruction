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

#include "catch.hpp"
#include "hippomocks.h"

//---- INCLUDE STUBS ----
#include <testing.h>
//-----------------------

//----INCLUDE MODULES----
#include <tl/sharp_spots_image_reconstruction-internal.h>
//-----------------------

namespace png
{
  Rgb_image * image_mock_instance = nullptr;
}

TEST_CASE("src/tl/sharp_spots_image_reconstruction]")
{
  SECTION("rgb_to_gray function shall produce gray_pixel with value equal to average value of red, green and blue from rgb_pixel")
  {
    REQUIRE(rgb_to_gray(Rgb_pixel(10, 20, 30)) == 20);
  }

  SECTION("read_images shall call Rgb_image constructor for all filenames passed via vector. Call of read image shall produce Rgb_images for all passed filenames.")
  {
    const char* TEST_FILENAME1 = "filename1";
    const char* TEST_FILENAME2 = "filename2";
    const char* TEST_FILENAME3 = "filename3";

    tl::List_of_filenames filenames = { TEST_FILENAME1, TEST_FILENAME2, TEST_FILENAME3 };

    MockRepository mocks;
    png::image_mock_instance = mocks.Mock<Rgb_image>();
    mocks.ExpectCallOverload(png::image_mock_instance, (void(Rgb_image::*)(const char* filename))&Rgb_image::calling_image_constructor).With(TEST_FILENAME1);
    mocks.ExpectCallOverload(png::image_mock_instance, (void(Rgb_image::*)(const char* filename))&Rgb_image::calling_image_constructor).With(TEST_FILENAME2);
    mocks.ExpectCallOverload(png::image_mock_instance, (void(Rgb_image::*)(const char* filename))&Rgb_image::calling_image_constructor).With(TEST_FILENAME3);
    REQUIRE(read_images(filenames).size() == 3);
  }
}
