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

#ifndef TL_FILTERS_GAUSSIAN_H
#define TL_FILTERS_GAUSSIAN_H

// To generate tl::fitler::GAUSSIAN use following command:
// python -m cogapp -d -e -ogaussian.h -DN=25 -DNSIG=2 gaussian_generator.h
//   Where N is filter size and NSIG is sigma profile.

namespace tl
{
namespace filters
{
/*[[[cog
import cog
cog.outl("// Gaussian Filter with N=%d and nsigma=%d" % (int(N), int(NSIG)))
cog.outl("const int32_t GAUSSIAN_SIZE = %d;" % int(N))
]]]*/
/*[[[end]]]*/

const double GAUSSIAN[] =
{
/*[[[cog
import cog
import numpy
import scipy.stats

def create_gaussian_kernel(n, nsig=3):
  assert (n > 0) and (n % 2 == 1), "Kernel size (N) has to be odd, possitive number."
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

g = create_gaussian_kernel(int(N), int(NSIG))
for y in g:
  for x in y:
    cog.outl("%f," % x)
]]]*/
/*[[[end]]]*/
};

}
}

#endif // TL_FILTERS_GAUSSIAN_H
