#!/usr/bin/python3

# BSD 3-Clause License
#
# Copyright (c) 2019, michalkrzyz
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# * Neither the name of the copyright holder nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

def convert_image_with_filter_mask_3x3_avg0(image, mask):
  validate_mask_3x3(mask)

  new_image = []
  v_size = len(image)
  h_size = len(image[0])
  for v_idx in range(v_size):
    new_v_line = []
    for h_idx in range(h_size):
      v_lo = max(v_idx - 1, 0)
      h_lo = max(h_idx - 1, 0)
      v_hi = min(v_idx + 1, v_size - 1)
      h_hi = min(h_idx + 1, h_size - 1)
      new_h_pix = abs(sum([mask[0][0] * image[v_lo][h_lo],
                           mask[0][1] * image[v_lo][h_idx],
                           mask[0][2] * image[v_lo][h_hi],
                           mask[1][0] * image[v_idx][h_lo],
                           mask[1][1] * image[v_idx][h_idx],
                           mask[1][2] * image[v_idx][h_hi],
                           mask[2][0] * image[v_hi][h_lo],
                           mask[2][1] * image[v_hi][h_idx],
                           mask[2][2] * image[v_hi][h_hi]]) - 127)
      new_v_line.append(new_h_pix)
    new_image.append(new_v_line)
  return new_image

def convert_image_with_filter_mask_3x3_avg1(image, mask):
  validate_mask_3x3(mask)

  new_image = []
  v_size = len(image)
  h_size = len(image[0])
  for v_idx in range(v_size):
    new_v_line = []
    for h_idx in range(h_size):
      v_lo = max(v_idx - 1, 0)
      h_lo = max(h_idx - 1, 0)
      v_hi = min(v_idx + 1, v_size - 1)
      h_hi = min(h_idx + 1, h_size - 1)
      new_h_pix = minmax(sum([mask[0][0] * image[v_lo][h_lo],
                              mask[0][1] * image[v_lo][h_idx],
                              mask[0][2] * image[v_lo][h_hi],
                              mask[1][0] * image[v_idx][h_lo],
                              mask[1][1] * image[v_idx][h_idx],
                              mask[1][2] * image[v_idx][h_hi],
                              mask[2][0] * image[v_hi][h_lo],
                              mask[2][1] * image[v_hi][h_idx],
                              mask[2][2] * image[v_hi][h_hi]]), 0, 255)
      new_v_line.append(new_h_pix)
    new_image.append(new_v_line)
  return new_image


def convert_images_with_filter_mask_3x3_avg0(images, mask):
  validate_mask_3x3(mask)

  new_images = []
  for image in images:
    new_images.append(convert_image_with_filter_mask_3x3_avg0(image, mask))
  return new_images

def convert_images_with_filter_mask_3x3_avg1(images, mask):
  validate_mask_3x3(mask)

  new_images = []
  for image in images:
    new_images.append(convert_image_with_filter_mask_3x3_avg1(image, mask))
  return new_images
