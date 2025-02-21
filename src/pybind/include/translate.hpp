#pragma once

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "mdot/include/babel_type.hpp"
#include "mdot/include/routine/interface.hpp"

namespace py = pybind11;

template <typename T> using numpy_array = py::array_t<T, py::array::c_style>;

using pydmbloc_type =
    std::map<std::tuple<uint16_t, uint8_t, uint16_t>, numpy_array<dnum_t>>;

using pydtbloc_type = std::map<std::tuple<uint16_t, uint8_t, uint8_t, uint16_t>,
                               numpy_array<dnum_t>>;

void translate_dmbloc_py2cpp(dmbloc_t &target_cpp, pydmbloc_type src_py) {
  for (auto &[src_key, src_value] : src_py) {
    auto src_shape = src_value.shape();
    m_shape_t target_shape = std::tuple<std::size_t, std::size_t, std::size_t>(
        static_cast<std::size_t>(src_shape[0]),
        static_cast<std::size_t>(src_shape[1]),
        static_cast<std::size_t>(src_shape[2]));
    std::vector<dnum_t> target_array(src_value.data(),
                                     src_value.data() + src_value.size());
    target_cpp[src_key] = {target_shape, target_array};
  }
}

void translate_dmbloc_cpp2py(pydmbloc_type &target_py, dmbloc_t src_cpp) {
  for (auto &[src_key, src_value] : src_cpp) {
    auto src_shape = src_value.first;
    py::ssize_t target_shape[3] = {
        static_cast<py::ssize_t>(std::get<0>(src_shape)),
        static_cast<py::ssize_t>(std::get<1>(src_shape)),
        static_cast<py::ssize_t>(std::get<2>(src_shape))};
    // new is mandatory for python memory usage
    std::vector<dnum_t> *vec_ptr = new std::vector<dnum_t>;
    vec_ptr->swap(src_value.second);
    auto deallocator = py::capsule(vec_ptr, [](void *ptr) {
      auto v_ptr = reinterpret_cast<std::vector<dnum_t> *>(ptr);
      v_ptr->clear();
      delete v_ptr;
    });
    numpy_array<dnum_t> np_target_array(target_shape, vec_ptr->data(),
                                        deallocator);
    target_py[src_key] = np_target_array;
  }
}

void translate_dtbloc_cpp2py(pydtbloc_type &target_py, dtbloc_t src_cpp) {
  for (auto &[src_key, src_value] : src_cpp) {
    auto src_shape = src_value.first;
    py::ssize_t target_shape[4] = {
        static_cast<py::ssize_t>(std::get<0>(src_shape)),
        static_cast<py::ssize_t>(std::get<1>(src_shape)),
        static_cast<py::ssize_t>(std::get<2>(src_shape)),
        static_cast<py::ssize_t>(std::get<3>(src_shape))};
    // new is mandatory for python memory usage
    std::vector<dnum_t> *vec_ptr = new std::vector<dnum_t>;
    vec_ptr->swap(src_value.second);
    auto deallocator = py::capsule(vec_ptr, [](void *ptr) {
      auto v_ptr = reinterpret_cast<std::vector<dnum_t> *>(ptr);
      v_ptr->clear();
      delete v_ptr;
    });
    numpy_array<dnum_t> np_target_array(target_shape, vec_ptr->data(),
                                        deallocator);
    target_py[src_key] = np_target_array;
  }
}
