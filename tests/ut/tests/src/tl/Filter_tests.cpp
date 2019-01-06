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
#include <tl/Filter.h>
//-----------------------

const int32_t TEST_FILTER_DATA[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const int32_t TEST_FILTER_SIZE = 3;
const int32_t TEST_FILTER_CENTER = 1;

TEST_CASE("[src/tl/Filter]")
{
  tl::Filter<int32_t> filter(TEST_FILTER_DATA, TEST_FILTER_SIZE);

  SECTION("Center shall be equal to floored half of size.")
  {
    REQUIRE(filter.center == TEST_FILTER_CENTER);
  }

  SECTION("Default convert function shall return value casted to uint8_t.")
  {
    REQUIRE(filter.convert(100) == 100);
    REQUIRE(filter.convert(257) == 1);
  }

  SECTION("get_data() shall return data value with offset equal to: y * N + x")
  {
    REQUIRE(filter.get_data(1, 2) == 8);
  }
}

TEST_CASE("[src/tl/Filter] Throw an exception when invalid filter parameters were used.")
{
  const int32_t TEST_EVEN_NUMBER_FILTER_SIZE = 2;
  const int32_t TEST_NEGATIVE_FILTER_SIZE = -3;

  SECTION("Filter shall throw an exception when even number is used")
  {
    REQUIRE_THROWS_WITH(tl::Filter<int32_t>(TEST_FILTER_DATA, TEST_EVEN_NUMBER_FILTER_SIZE),
                        "Filter size shall be an odd number.");

    REQUIRE_THROWS_AS(tl::Filter<int32_t>(TEST_FILTER_DATA, TEST_EVEN_NUMBER_FILTER_SIZE),
                      tl::Exception);
  }

  SECTION("Filter shall throw an exception when negative number is used")
  {
    REQUIRE_THROWS_WITH(tl::Filter<int32_t>(TEST_FILTER_DATA, TEST_NEGATIVE_FILTER_SIZE),
                        "Filter size shall be an odd number.");

    REQUIRE_THROWS_AS(tl::Filter<int32_t>(TEST_FILTER_DATA, TEST_NEGATIVE_FILTER_SIZE),
                      tl::Exception);
  }

  SECTION("Filter shall throw an exception when nullptr is used as data")
  {
    REQUIRE_THROWS_WITH(tl::Filter<int32_t>(nullptr, TEST_FILTER_SIZE),
                        "Filter data shall not be nullptr.");

    REQUIRE_THROWS_AS(tl::Filter<int32_t>(nullptr, TEST_FILTER_SIZE),
                      tl::Exception);
  }

}
