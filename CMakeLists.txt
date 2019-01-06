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

cmake_minimum_required(VERSION 3.0)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES_RDIR src)
set(SOURCES_DIR ${PROJECT_DIR}/${SOURCES_RDIR})
set(SOURCES_DIR ${PROJECT_DIR}/${SOURCES_RDIR})

set(APP_RDIR app)
set(APP_DIR ${PROJECT_DIR}/${APP_RDIR})

set(TESTS_DIR ${PROJECT_DIR}/tests)
set(TESTS_UT_DIR ${TESTS_DIR}/ut)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wunreachable-code")

set(MODULES
  ${SOURCES_RDIR}/tl/Filter
  ${SOURCES_RDIR}/tl/sharp_spots_image_reconstruction
  ${SOURCES_RDIR}/utils/bound
  ${SOURCES_RDIR}/utils/time_measure
)

foreach(module ${MODULES})
  string(REPLACE / _ module_target ${module})

  set(module_path ${PROJECT_DIR}/${module}.cpp)

  if(EXISTS ${module_path})
    message("'${module}' is cpp module.")
    set(MODULES_TARGETS ${MODULES_TARGETS} ${module_target})
    set(MODULES_SOURCES ${MODULES_SOURCES} ${module_path})

    add_library(${module_target} OBJECT ${module_path})
    target_include_directories(${module_target} PUBLIC ${PROJECT_DIR} ${SOURCES_DIR} ${APP_DIR})

    set(MODULES_OBJECTS ${MODULES_OBJECTS} $<TARGET_OBJECTS:${module_target}>)
  else(EXISTS ${module_path})
    message("'${module}' is header only module.")
  endif(EXISTS ${module_path})
endforeach()

add_custom_target(cyclomatics lizard ${SOURCES_DIR} ${TARGET_DIR})

set(TESTS_UT OFF CACHE BOOL "Switch to unittests")
if(${TESTS_UT})
  add_subdirectory(${TESTS_UT_DIR})
else(${TESTS_UT})
  add_subdirectory(${APP_DIR})
endif(${TESTS_UT})
