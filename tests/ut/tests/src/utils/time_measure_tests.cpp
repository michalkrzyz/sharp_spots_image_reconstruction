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
#include <utils/time_measure.h>

#include <chrono>
//-----------------------

TEST_CASE("[src/utils/time_measure]")
{
  SECTION("start() shall call chrono steady_clock now()")
  {
    int32_t TEST_T0_SECONDS = 10;
    int32_t TEST_T1_SECONDS = 15;
    int32_t TEST_T2_SECONDS = 20;
    MockRepository mocks;
    mocks.ExpectCallFunc(std::chrono::steady_clock::now).Return(std::chrono::time_point<std::chrono::steady_clock>(std::chrono::seconds(TEST_T0_SECONDS)));
    utils::time_measure::start();

    SECTION("get_seconds() shall call chrono steady_clock now()")
    {
      mocks.ExpectCallFunc(std::chrono::steady_clock::now).Return(std::chrono::time_point<std::chrono::steady_clock>(std::chrono::seconds(TEST_T1_SECONDS)));
      (void)utils::time_measure::get_seconds();
    }

    SECTION("get_seconds() shall return difference in seconds between call of start() and now()")
    {
      mocks.ExpectCallFunc(std::chrono::steady_clock::now).Return(std::chrono::time_point<std::chrono::steady_clock>(std::chrono::seconds(TEST_T2_SECONDS)));
      REQUIRE(utils::time_measure::get_seconds() == (TEST_T2_SECONDS - TEST_T0_SECONDS));
    }
  }
}
