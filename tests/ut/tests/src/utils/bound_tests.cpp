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
#include <utils/bound.h>

#include <chrono>
//-----------------------

TEST_CASE("[src/utils/bound]")
{
  int32_t TEST_VAL_MIN = -10;
  int32_t TEST_VAL_MAX = 20;
  int32_t TEST_VAL_IN_RANGE = 0;
  int32_t TEST_VAL_LOWER_THAN_MIN = TEST_VAL_MIN - 11;
  int32_t TEST_VAL_GREATER_THAN_MAX = TEST_VAL_MAX + 11;

  SECTION("bound() shall return minimum value when n is lower than minimum.")
  {
    REQUIRE(utils::bound<int32_t>(TEST_VAL_LOWER_THAN_MIN, TEST_VAL_MIN, TEST_VAL_MAX) == TEST_VAL_MIN);
  }

  SECTION("bound() shall return maximum value when n is greater than maximum.")
  {
    REQUIRE(utils::bound<int32_t>(TEST_VAL_GREATER_THAN_MAX, TEST_VAL_MIN, TEST_VAL_MAX) == TEST_VAL_MAX);
  }

  SECTION("bound() shall return n when n is in range from minimum to maximum value.")
  {
    REQUIRE(utils::bound<int32_t>(TEST_VAL_IN_RANGE, TEST_VAL_MIN, TEST_VAL_MAX) == TEST_VAL_IN_RANGE);
  }
}
