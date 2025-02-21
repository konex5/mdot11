#pragma once

#include <map>
#include <tuple>

#include <pybind11/numpy.h>

namespace py = pybind11;

template <typename T> using numpy_array = py::array_t<T, py::array::c_style>;

using pydmbloc_type =
    std::map<std::tuple<uint16_t, uint8_t, uint16_t>, numpy_array<double>>;

using pydgbloc_type = std::map<std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>,
                               numpy_array<double>>;

using pydtbloc_type = std::map<std::tuple<uint16_t, uint8_t, uint8_t, uint16_t>,
                               numpy_array<double>>;

using pydmenvbloc_type = std::map<
    std::tuple<uint16_t, uint8_t, uint16_t, uint16_t, uint8_t, uint16_t>,
    numpy_array<double>>;

using pydmmenvbloc_type =
    std::map<std::tuple<uint16_t, uint8_t, uint8_t, uint16_t, uint16_t, uint8_t,
                        uint8_t, uint16_t>,
             numpy_array<double>>;