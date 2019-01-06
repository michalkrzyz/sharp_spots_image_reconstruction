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

#ifndef TL_FILTERS_COMMON_H
#define TL_FILTERS_COMMON_H

#include <cstdint>

namespace tl
{
namespace filters
{
const int32_t SIMPLE_EDGE_SIZE = 3;
const int32_t SIMPLE_EDGE_N[] =  { 0,  1,  0,
                                   0,  0,  0,
                                   0, -1,  0};
const int32_t SIMPLE_EDGE_S[] =  { 0, -1,  0,
                                   0,  0,  0,
                                   0,  1,  0};
const int32_t SIMPLE_EDGE_W[] =  { 0,  0,  0,
                                   1,  0, -1,
                                   0,  0,  0};
const int32_t SIMPLE_EDGE_E[] =  { 0,  0,  0,
                                  -1,  0,  1,
                                   0,  0,  0};
const int32_t SIMPLE_EDGE_NW[] = { 1,  0,  0,
                                   0,  0,  0,
                                   0,  0, -1};
const int32_t SIMPLE_EDGE_NE[] = { 0,  0,  1,
                                   0,  0,  0,
                                  -1,  0,  0};
const int32_t SIMPLE_EDGE_SW[] = { 0,  0, -1,
                                   0,  0,  0,
                                   1,  0,  0};
const int32_t SIMPLE_EDGE_SE[] = {-1,  0,  0,
                                   0,  0,  0,
                                   0,  0,  1};

const int32_t SOBEL_SIZE = 3;
const int32_t SOBEL_N[] =  { 1,  2,  1,
                             0,  0,  0,
                            -1, -2, -1};
const int32_t SOBEL_S[] =  {-1, -2, -1,
                             0,  0,  0,
                             1,  2,  1};
const int32_t SOBEL_W[] =  { 1,  0, -1,
                             2,  0, -2,
                             1,  0, -1};
const int32_t SOBEL_E[] =  {-1,  0,  1,
                            -2,  0,  2,
                            -1,  0,  1};
const int32_t SOBEL_NW[] = { 2,  1,  0,
                             1,  0, -1,
                             0, -1, -2};
const int32_t SOBEL_NE[] = { 0,  1,  2,
                            -1,  0,  1,
                            -2, -1,  0};
const int32_t SOBEL_SW[] = { 0, -1, -2,
                             1,  0, -1,
                             2,  1,  0};
const int32_t SOBEL_SE[] = {-2, -1,  0,
                            -1,  0,  1,
                             0,  1,  2};

const int32_t PREWITT_SIZE = 3;
const int32_t PREWITT_N[] =  { 1,  1,  1,
                               0,  0,  0,
                              -1, -1, -1};
const int32_t PREWITT_S[] =  {-1, -1, -1,
                               0,  0,  0,
                               1,  1,  1};
const int32_t PREWITT_W[] =  { 1,  0, -1,
                               1,  0, -1,
                               1,  0, -1};
const int32_t PREWITT_E[] =  {-1,  0,  1,
                              -1,  0,  1,
                              -1,  0,  1};
const int32_t PREWITT_NW[] = { 1,  1,  0,
                               1,  0, -1,
                               0, -1, -1};
const int32_t PREWITT_NE[] = { 0,  1,  1,
                              -1,  0,  1,
                              -1, -1,  0};
const int32_t PREWITT_SW[] = { 0, -1, -1,
                               1,  0, -1,
                               1,  1,  0};
const int32_t PREWITT_SE[] = {-1, -1,  0,
                              -1,  0,  1,
                               0,  1,  1};

const int32_t KIRSH_SIZE = 3;
const int32_t KIRSH_N[] =  { 5,  5,  5,
                            -3,  0, -3,
                            -3, -3, -3};
const int32_t KIRSH_S[] =  {-3, -3, -3,
                            -3,  0, -3,
                             5,  5,  5};
const int32_t KIRSH_W[] =  { 5, -3, -3,
                             5,  0, -3,
                             5, -3, -3};
const int32_t KIRSH_E[] =  {-3, -3,  5,
                            -3,  0,  5,
                            -3, -3,  5};
const int32_t KIRSH_NW[] = { 5,  5, -3,
                             5,  0, -3,
                            -3, -3, -3};
const int32_t KIRSH_NE[] = {-3,  5,  5,
                            -3,  0,  5,
                            -3, -3, -3};
const int32_t KIRSH_SW[] = {-3, -3, -3,
                             5,  0, -3,
                             5,  5, -3};
const int32_t KIRSH_SE[] = {-3, -3, -3,
                            -3,  0,  5,
                            -3,  5,  5};

const int32_t LAPLACIAN_SIZE = 3;
const int32_t LAPLACIAN_EDGE1[] = { 0, -1,  0,
                                   -1,  4, -1,
                                    0, -1,  0};
const int32_t LAPLACIAN_EDGE2[] = {-1, -1, -1,
                                   -1,  8, -1,
                                   -1, -1, -1};
}
}
#endif // TL_FILTERS_COMMON_H
