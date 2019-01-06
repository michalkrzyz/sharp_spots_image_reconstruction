#!/usr/bin/python3

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
