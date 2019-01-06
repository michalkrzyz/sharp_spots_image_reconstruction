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

project(tl_ut CXX)

set(CATCH_DIR            ${TESTS_DIR}/../../test-frameworks/Catch2)
set(CATCH_SINGLE_INCLUDE ${CATCH_DIR}/single_include)
set(CATCH_INCLUDE        ${CATCH_DIR}/include)
set(HIPPOMOCKS_DIR       ${TESTS_DIR}/../../test-frameworks/hippomocks)
set(HIPPOMOCKS_INCLUDE   ${HIPPOMOCKS_DIR}/HippoMocks)
set(TESTS_STUBS_DIR      ${TESTS_UT_DIR}/stubs)
set(TESTS_SUITES_DIR     ${TESTS_UT_DIR}/tests)
set(TESTS_UTILS_DIR      ${TESTS_UT_DIR}/utils)

set(TESTS ${MODULES})

set(CMAKE_POSITION_INDEPENDENT_CODE True)


#STUBS
set(STUBS )
foreach(stub ${STUBS})
  string(REPLACE / _ stub_target ${stub})

  set(stub_path ${stub}.cpp)

  if(EXISTS ${stub_path})
    add_library(${stub_target} OBJECT ${stub_path})
    target_include_directories(${stub_target} PUBLIC ${TESTS_STUBS_DIR})
    target_compile_options(${stub_target}  PRIVATE -DUNITTESTS -Dprivate=public -Dprotected=public)
    set(TESTS_STUBS_OBJECTS ${TESTS_STUBS_OBJECTS} $<TARGET_OBJECTS:${stub_target}>)
  else(EXISTS ${stub_path})
  endif(EXISTS ${stub_path})
endforeach()
######


foreach(uut ${TESTS})
  string(REPLACE / _ uut_target ${uut})

  set(uut_path ${PROJECT_DIR}/${uut}.cpp)

  if(EXISTS ${uut_path})
    target_include_directories(${uut_target} PUBLIC ${TESTS_STUBS_DIR})
    target_compile_options(${uut_target}  PRIVATE -DUNITTESTS -Dprivate=public -Dprotected=public)
  else(EXISTS ${uut_path})
  endif(EXISTS ${uut_path})

  set(uut_tests_name ${uut}_tests)
  set(uut_tests_target ${uut_target}_tests)

  set(uut_tests_path ${TESTS_SUITES_DIR}/${uut_tests_name}.cpp)
  set(TESTS_TARGETS ${TESTS_TARGETS} ${uut_tests_target})
  set(TESTS_SOURCES ${TESTS_SOURCES} ${uut_tests_path})

  add_library(${uut_tests_target} OBJECT ${uut_tests_path})
  target_include_directories(${uut_tests_target} PUBLIC ${PROJECT_DIR} ${SOURCES_DIR} ${CATCH_INCLUDE} ${HIPPOMOCKS_INCLUDE} ${TESTS_UTILS_DIR} ${TESTS_STUBS_DIR})
  target_compile_options(${uut_tests_target}  PRIVATE -DUNITTESTS)

  set(TESTS_UT_OBJECTS ${TESTS_UT_OBJECTS} $<TARGET_OBJECTS:${uut_tests_target}>)
endforeach()

set(TL_UT_MAIN ${TESTS_UT_DIR}/main.cpp)
add_executable(tl_ut ${TL_UT_MAIN} ${MODULES_OBJECTS} ${TESTS_UT_OBJECTS} ${TESTS_STUBS_OBJECTS})
add_custom_target(run ${CMAKE_CURRENT_BINARY_DIR}/tl_ut DEPENDS tl_ut)

target_include_directories(tl_ut PUBLIC ${CATCH_SINGLE_INCLUDE})
