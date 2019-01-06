Task description:
  Description: Your task is to develop a simple computer vision algorithm in
  C++. Your input are photographs taken for the same object, but with
  different focus setting. Therefore only a part of an image is sharp, rest is
  blurred.
  Images are also sorted - the first image is sharp for parts that are nearest
  camera and last image is sharp for parts that are farther.
  Using this knowledge your task is to come up with an algorithm to combine
  all images to produce a single, sharp color image and also a grayscale
  image of an estimated depth map (white - nearest, black - farthest).
  You don’t need to implement any super fancy algorithm (but you can if you
  wish!), but ensure you are following our requirements (on the next page).

Deadline: 2 days.

Solution:

image of an estimated depth map (white - nearest, black - farthest).
* Application should handle n images passed via argument line

Following algorithm shall be implemented:
  1. Read all images to buffers.
  2. For each image:
    1. Create gray-scale 8-bit image.
    2. Use Sobel mask to convert gray-scale image to 8-bit Sobel image (N, S, W, E, NW, NE, SW, SE).
    3. Use N x N Gaussian mask to convert Sobel image to Gaussian one.
  3. For each pixel of output image:
    1. Iterate through all images to find biggest value of Gaussian images.
    2. Origin value of pixel for greates Gaussian pixel value shall be taken to create pixel of output image.


Sobel filter is used for an edge detection, the best sharppness of spot shall be detected by the value of sobel and it's neighbours.


Directories:
app/ - main and cmake for application
poc/ - just a proof of concept
scripts/ - some automation added as helpers
src/ - sources of app libraries
res/ - images (3rd party images are excluded)
tests/ - unittests
