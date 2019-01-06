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

#include <iostream>
#include <vector>

#include <tl/sharp_spots_image_reconstruction.h>
#include <utils/time_measure.h>

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    std::cerr << "At least one argument with image file shall be provided." << std::endl;
    std::cerr << "Usage: " << argv[0] << " FILE1.png FILE2.png ..." << std::endl;
    exit(1);
  }

  tl::List_of_filenames files;
  for(int i = 1; i < argc; i++)
  {
    files.push_back(argv[i]);
  }

  utils::time_measure::start();

  try
  {
    tl::sharp_spots_image_reconstruction(files, "output.png", "output-depth.png");
  }
  catch(const tl::Exception & e)
  {
    std::cerr << "ERROR: " << e.what() << std::endl;
    std::cerr << "Failed to process files." << std::endl;
    exit(1);
  }

  std::cout << "Done (" << utils::time_measure::get_seconds() << " s)." << std::endl;
  exit(0);
}
