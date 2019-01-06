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

import sys

import imageio
import numpy
import scipy.stats

import time

VERBOSE = True
CREATE_SPOT_MAPS = False
TIME0 = time.time()

if VERBOSE:
  def log(*args, **kwargs):
    print("%.3f:" % (time.time() - TIME0), *args, **kwargs)
else:
  def log(*args, **kwargs):
    pass

def get_image_from_file(filename):
  log("Reading '%s'..." % filename)
  return(imageio.imread(filename))

def get_images_from_list_of_files(list_of_files):
  images = []
  for filename in list_of_files:
    images.append(get_image_from_file(filename))
  return images

def create_gray_image_from_rgb_image(image):
  new_image = []
  for v_line in image:
    new_v_line = []
    for h_pix in v_line:
      new_h_pix = int(sum(h_pix[0:3]) / 3)
      new_v_line.append(new_h_pix)
    new_image.append(new_v_line)
  return new_image
  
def create_gray_images_from_rgb_images(images):
  new_images = []
  for image in images:
    new_images.append(create_gray_image_from_rgb_image(image))
  return new_images

class SIMPLE_EDGE_MASK:
  N = [[ 0,  1,  0],
       [ 0,  0,  0],
       [ 0, -1,  0]]

  S = [[ 0, -1,  0],
       [ 0,  0,  0],
       [ 0,  1,  0]]

  W = [[ 0,  0,  0],
       [ 1,  0, -1],
       [ 0,  0,  0]]

  E = [[ 0,  0,  0],
       [-1,  0,  1],
       [ 0,  0,  0]]

  NW = [[ 1,  0,  0],
        [ 0,  0,  0],
        [ 0,  0, -1]]

  NE = [[ 0,  0,  1],
        [ 0,  0,  0],
        [-1,  0,  0]]

  SW = [[ 0,  0, -1],
        [ 0,  0,  0],
        [ 1,  0,  0]]

  SE = [[-1,  0,  0],
        [ 0,  0,  0],
        [ 0,  0,  1]]

class SOBEL_MASK:
  N = [[ 1,  2,  1],
       [ 0,  0,  0],
       [-1, -2, -1]]

  S = [[-1, -2, -1],
       [ 0,  0,  0],
       [ 1,  2,  1]]

  W = [[ 1,  0, -1],
       [ 2,  0, -2],
       [ 1,  0, -1]]

  E = [[-1,  0, 1],
       [-2,  0, 2],
       [-1,  0, 1]]

  NW = [[ 2,  1,  0],
        [ 1,  0, -1],
        [ 0, -1, -2]]

  NE = [[ 0,  1,  2],
        [-1,  0,  1],
        [-2, -1,  0]]

  SW = [[ 0, -1, -2],
        [ 1,  0, -1],
        [ 2,  1,  0]]

  SE = [[-2, -1,  0],
        [-1,  0,  1],
        [ 0,  1,  2]]

class PREWITT_MASK:
  N = [[ 1,  1,  1],
       [ 0,  0,  0],
       [-1, -1, -1]]

  S = [[-1, -1, -1],
       [ 0,  0,  0],
       [ 1,  1,  1]]

  W = [[ 1,  0, -1],
       [ 1,  0, -1],
       [ 1,  0, -1]]

  E = [[-1,  0,  1],
       [ 1,  0,  1],
       [ 1,  0,  1]]

  NW = [[ 1,  1,  0],
        [ 1,  0, -1],
        [ 0, -1, -1]]

  NE = [[ 0,  1,  1],
        [ 1,  0,  1],
        [ 1, -1,  0]]

  SW = [[ 0, -1, -1],
        [ 1,  0, -1],
        [ 1,  1,  0]]

  SE = [[-1, -1,  0],
        [-1,  0,  1],
        [ 0,  1,  1]]

class KIRSH_MASK:
  N = [[ 5,  5,  5],
       [-3,  0, -3],
       [-3, -3, -3]]

  S = [[-3, -3, -3],
       [-3,  0, -3],
       [ 5,  5,  5]]

  W = [[ 5, -3, -3],
       [ 5,  0, -3],
       [ 5, -3, -3]]

  E = [[-3, -3,  5],
       [-3,  0,  5],
       [-3, -3,  5]]

  NW = [[ 5,  5, -3],
        [ 5,  0, -3],
        [-3, -3, -3]]

  NE = [[-3,  5,  5],
        [-3,  0,  5],
        [-3, -3, -3]]

  SW = [[-3, -3, -3],
        [ 5,  0, -3],
        [ 5,  5, -3]]

  SE = [[-3, -3, -3],
        [-3,  0,  5],
        [-3,  5,  5]]

LAPLACIAN_EDGE_DETECTION_1 = [[ 0, -1,  0],
                              [-1,  4, -1],
                              [ 0, -1,  0]]

LAPLACIAN_EDGE_DETECTION_2 = [[-1, -1, -1],
                              [-1,  8, -1],
                              [-1, -1, -1]]


def validate_mask(mask):
  assert (len(mask) % 2) == 1, "Mask lines shall be impair number"
  assert (len(mask[0]) % 2) == 1, "Mask rows shall be impair number"
  assert (len(mask) == len(mask[0])), "Mask shall be a square"

def minmax(n, minn, maxn):
  return min(max(n, minn), maxn)

def convert_image_with_filter_mask_avg0(image, mask):
  validate_mask(mask)

  new_image = []
  v_size = len(image)
  h_size = len(image[0])
  v_mask_size = len(mask)
  h_mask_size = len(mask[0])
  mask_center = int(v_mask_size / 2)
  for v_idx in range(v_size):
    new_v_line = []
    for h_idx in range(h_size):
      s = 0
      for vm_idx in range(v_mask_size):
        v = minmax(v_idx + vm_idx - mask_center, 0, v_size - 1)
        for hm_idx in range(h_mask_size):
          h = minmax(h_idx + hm_idx - mask_center, 0, h_size - 1)
          s += mask[vm_idx][hm_idx] * image[v][h]
      new_h_pix = abs(s)
      new_v_line.append(new_h_pix)
    new_image.append(new_v_line)
  return new_image

def convert_image_with_filter_mask_avg1(image, mask):
  validate_mask(mask)

  new_image = []
  v_size = len(image)
  h_size = len(image[0])
  v_mask_size = len(mask)
  h_mask_size = len(mask[0])
  mask_center = int(v_mask_size / 2)
  for v_idx in range(v_size):
    new_v_line = []
    for h_idx in range(h_size):
      s = 0
      for vm_idx in range(v_mask_size):
        v = minmax(v_idx + vm_idx - mask_center, 0, v_size - 1)
        for hm_idx in range(h_mask_size):
          h = minmax(h_idx + hm_idx - mask_center, 0, h_size - 1)
          s += mask[vm_idx][hm_idx] * image[v][h]
      new_h_pix = minmax(s, 0, 255)
      new_v_line.append(new_h_pix)
    new_image.append(new_v_line)
  return new_image

def convert_images_with_filter_mask_avg0(images, mask):
  validate_mask(mask)

  new_images = []
  for image in images:
    new_images.append(convert_image_with_filter_mask_avg0(image, mask))
  return new_images

def convert_images_with_filter_mask_avg1(images, mask):
  validate_mask(mask)

  new_images = []
  for image in images:
    new_images.append(convert_image_with_filter_mask_avg1(image, mask))
  return new_images

def convert_image_to_numpy_image(image):
  new_image = []
  for v_line in image:
    new_v_line = []
    for h_pix in v_line:
      new_h_pix = [ h_pix ] * 3
      new_v_line.append(numpy.asarray(new_h_pix).astype(numpy.uint8))
    new_image.append(imageio.core.util.Array(numpy.asarray(new_v_line)))
  return imageio.core.util.Array(numpy.asarray(new_image))


def create_gaussian_mask(n, nsig=3):
  assert (n > 0) and (n % 2 == 1), "Mask has to be impair, possitive number"
  interval = (2 * nsig + 1.0) / (n)
  x = numpy.linspace(-nsig-interval / 2.0, nsig+interval / 2.0, n + 1)
  kern1d = numpy.diff(scipy.stats.norm.cdf(x))
  kernel_raw = numpy.sqrt(numpy.outer(kern1d, kern1d))
  kernel = kernel_raw/kernel_raw.sum()
  new_kernel = []
  for v in kernel:
    new_v = []
    for h in v:
      new_v.append(h)
    new_kernel.append(new_v)
  return new_kernel
 
def find_max_idx(l):
  m = max(l)
  ret = [i for i, j in enumerate(l) if j == m][0]
  return ret


def create_image_and_spot_maps_using_focus_spot_mask_output_and_origin_images(origin_images, focus_masks):
  assert len(origin_images) == len(focus_masks), "Origin images and focus masks count shall be the same"

  image = imageio.core.util.Array(origin_images[0])
  v_size = len(image)
  h_size = len(image[0])
  spot_maps = []
  for i in range(len(origin_images)):
    nmap = []
    for v in range(v_size):
      nv = []
      for h in range(h_size):
        nv.append(0)
      nmap.append(nv)
    spot_maps.append(nmap)
  for v_idx in range(v_size):
    for h_idx in range(h_size):
      img_idx = find_max_idx([m[v_idx][h_idx] for m in focus_masks])
      image[v_idx][h_idx] = origin_images[img_idx][v_idx][h_idx]
      spot_maps[img_idx][v_idx][h_idx] = 255
  return image, spot_maps

def create_image_using_focus_spot_mask_output_and_origin_images(origin_images, focus_masks):
  assert len(origin_images) == len(focus_masks), "Origin images and focus masks count shall be the same"

  image = imageio.core.util.Array(origin_images[0])
  v_size = len(image)
  h_size = len(image[0])
  for v_idx in range(v_size):
    for h_idx in range(h_size):
      img_idx = find_max_idx([m[v_idx][h_idx] for m in focus_masks])
      image[v_idx][h_idx] = origin_images[img_idx][v_idx][h_idx]
  return image

def focus_spot_reconstruction(origin_images):
  "Creates focused image using N images with blures"

  log("Converting images to grayscale...")
  grayscale_images = create_gray_images_from_rgb_images(origin_images)
  log("Converting images using sobel...")
  sobel_images = convert_images_with_filter_mask_avg0(grayscale_images, SOBEL_MASK.N)
  log("Getting focus masks image...")
  focus_masks = convert_images_with_filter_mask_avg1(sobel_images, create_gaussian_mask(25, nsig=2))
  log("Getting focused image...")
  if CREATE_SPOT_MAPS:
    focused_image, spot_maps = create_image_and_spot_maps_using_focus_spot_mask_output_and_origin_images(origin_images, focus_masks)
    spot_map_images = []
    log("Converting spot maps to numpy images...")
    for s in spot_maps:
      spot_map_images.append(convert_image_to_numpy_image(s))
    return focused_image, spot_map_images
  else:
    focused_image = create_image_using_focus_spot_mask_output_and_origin_images(origin_images, focus_masks)
  return focused_image


if __name__ == "__main__":
  assert len(sys.argv) > 1, "At least one argument with image file shall be provided."
  origin_images = get_images_from_list_of_files(sys.argv[1:])

  if CREATE_SPOT_MAPS:
    output_image, spot_map_images = focus_spot_reconstruction(origin_images)
    for i, s in enumerate(spot_map_images):
      imageio.imwrite("output%d.png" % i, s)
  else:
    output_image = focus_spot_reconstruction(origin_images)

  imageio.imwrite("output.png", output_image)
