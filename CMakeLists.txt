cmake_minimum_required(VERSION 3.18.2 FATAL_ERROR)

set(PROJECT_VERSION "0.0.0")

project(
  golden_binding
  LANGUAGES C CXX
  VERSION "${PROJECT_VERSION}"
  DESCRIPTION "fhmdot - Fast Hilbert Matrix Dot")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

# ##############################################################################
# OPTIONS
# ##############################################################################

option(PROJECT_TESTS "Build Cpp Tests" ON)
option(PROJECT_PRECISION_FLOAT32 "Build with floating point 32" OFF)
# option(PROJECT_QNUM "Build with spin sz=" 0.5) option(PROJECT_QNUM_DOUBLED
# "Build for a doubled Hilbert space" ON)
option(PROJECT_SANDBOX "Build Project Sandbox" OFF)
option(PROJECT_BENCHMARK "Build Python Tests" OFF)
option(PROJECT_PYTHON "Build Python Wrapper (pybind)" OFF)
option(PROJECT_VALIDATION "Build Validation" OFF)
option(PROJECT_TBBMALLOC_PROXY
       "enable tbb_malloc_proxy linking (conflicts with pybind)" OFF)

# set(PROJECT_CXX_FLAGS_DEBUG -g -Wall -Wextra -fno-omit-frame-pointer
# -fno-inline) set(PROJECT_CXX_FLAGS_RELEASE -mfma -mavx) # -q openmp-simd
# -mftree-vectorize set(PROJECT_CXX_FLAGS_RELWITHDEBUG
# ${PROJECT_CXX_FLAGS_RELEASE} -g) set(PROJECT_CXX_FLAGS_MINSIZERELEASE
# ${PROJECT_CXX_FLAGS_RELEASE} -g)

add_compile_options(
  ${CMAKE_CXX_FLAGS}
  "$<$<CONFIG:Debug>:${PROJECT_CXX_FLAGS_DEBUG}>"
  "$<$<CONFIG:Release>:${PROJECT_CXX_FLAGS_RELEASE}>"
  "$<$<CONFIG:RelWithDebug>:${PROJECT_CXX_FLAGS_RELWITHDEBUG}>"
  "$<$<CONFIG:MinSizeRelease>:${PROJECT_CXX_FLAGS_MINSIZERELEASE}>")

# ##############################################################################
# FIND PACKAGES
# ##############################################################################
# * Boost
find_package(
  Boost REQUIRED
  COMPONENTS filesystem system program_options unit_test_framework
  REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIR})

# * TBB
if(${PROJECT_TBBMALLOC_PROXY})
  find_package(TBB REQUIRED tbb tbbmalloc_proxy)
else()
  find_package(TBB REQUIRED tbb)
endif()

if(${PROJECT_PYTHON})
  # * Pybind11
  find_package(
    Python
    COMPONENTS Interpreter Development
    REQUIRED)
  find_package(pybind11 CONFIG REQUIRED)
  # python install prefix
  if(NOT DEFINED CMAKE_INSTALL_PYTHON_SITE_PACKAGE)
    set(CMAKE_INSTALL_PYTHON_SITE_PACKAGE
        "${CMAKE_INSTALL_PREFIX}/lib/python${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}/site-packages/"
    )
  endif()
endif()

# ##############################################################################
# Headers/Interface
# ##############################################################################
configure_file("${CMAKE_SOURCE_DIR}/src/utils/static.hpp.in"
               "${CMAKE_BINARY_DIR}/static.hpp")
configure_file("${CMAKE_SOURCE_DIR}/src/fhmdot/utils/file_header.hpp.in"
               "${CMAKE_BINARY_DIR}/fhmdot/utils/file_header.hpp")
include_directories("${CMAKE_SOURCE_DIR}/src" ${CMAKE_BINARY_DIR})

# Installation of headers
install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/fhmdot
  DESTINATION "include"
  FILES_MATCHING
  PATTERN "*.hpp")

# Installation of configured headers
install(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/fhmdot
  DESTINATION "include"
  FILES_MATCHING
  PATTERN "*.hpp")

# ##############################################################################
# PROJECT
# ##############################################################################
add_subdirectory(src/fhmdot)
if(${PROJECT_PYTHON})
  add_subdirectory(src/pybind)
endif()

# ##############################################################################
# TESTS and miscelaneous
# ##############################################################################
if(${PROJECT_TESTS})
  include(CTest)
  enable_testing()
  add_subdirectory(tests/cpp_unit)
  if(${PROJECT_PYTHON})
    add_subdirectory(tests/python_unit)
  endif()
endif()
if(${PROJECT_SANDBOX})
  add_subdirectory(tests/cpp_sandbox)
endif()
if(${PROJECT_BENCHMARK})
  add_subdirectory(tests/cpp_benchmark)
endif()
if(${PROJECT_VALIDATION})
  add_subdirectory(tests/cpp_validation)
endif()
