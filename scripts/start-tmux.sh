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

#!/bin/bash

if [ -h $0 ]
then
  P=$PWD/`readlink $0`
else
  P=$0
fi
PROJECT_DIR=`dirname $P`/..

TMUX_SESSION_NAME=tooploox
tmux att -t ${TMUX_SESSION_NAME} ||
tmux \
  new -s ${TMUX_SESSION_NAME} -n src \; \
  send-keys "cd ${PROJECT_DIR}/src
" \; \
  neww -n out \; \
  send-keys "cd ${PROJECT_DIR}/out
" \; \
  neww -n ut \; \
  send-keys "cd ${PROJECT_DIR}/tests/ut
" \; \
  neww -n ref \; \
  send-keys "cd ${PROJECT_DIR}/ext
" \; \
  neww -n poc \; \
  send-keys "cd ${PROJECT_DIR}/poc
" \; \
  selectw -t 0  \; \
  detach \; && tmux att -t ${TMUX_SESSION_NAME}
