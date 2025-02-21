#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
//#include <pybind11/stl_bind.h>

#include "mdot/include/babel_type.hpp"
#include <complex>
#include <exception>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

#include "mdot/include/operators.hpp"
#include "mdot/include/operators_static.hpp"

namespace py = pybind11;

template <typename T> using numpy_array = py::array_t<T, py::array::c_style>;

using pydblocs_type =
    std::map<std::tuple<uint8_t, uint8_t>, numpy_array<double>>;
using pyzblocs_type =
    std::map<std::tuple<uint8_t, uint8_t>, numpy_array<double>>;

pydblocs_type single_operator_re(std::string name, std::string qbasis) {
  // mdot::
  auto test = single_operator_real(name, qbasis);
  dnum_t normalisation = std::get<1>(test);
  auto blocs = std::get<0>(test);
  //
  pydblocs_type output;
  //
  for (auto const &x : blocs) {
    std::tuple<uint8_t, uint8_t> indices = {std::get<0>(x.first),
                                            std::get<1>(x.first)};
    std::vector<dnum_t> vec_arr = x.second;
    //
    std::size_t n = vec_arr.size();
    for (int i = 0; i < 4; i++) {
      std::cout << vec_arr[i] << " " << std::endl;
    }
    // vec_arr.reserve(n);
    dnum_t *ptr = vec_arr.data();
    auto deallocator = py::capsule(&vec_arr, [](void *ptr) {
      auto vec_ptr = reinterpret_cast<std::vector<dnum_t> *>(ptr);
      for (int i = 0; i < 4; i++) {
        std::cout << vec_ptr->at(i) << " " << std::endl;
      }
      vec_ptr->clear();
    });
    numpy_array<dnum_t> np_out(n, ptr, deallocator);
    output[indices] = np_out;
  }

  return output;
}

numpy_array<double> py_single_operator_real(std::string name) {
  py::ssize_t ndim;
  std::vector<py::ssize_t> shape;
  std::vector<double> vec;

  if (name == "sh-id") {
    ndim = mdot::real_sh_operators_crtp<mdot::sh_id_no>::size;
    shape = {mdot::real_sh_operators_crtp<mdot::sh_id_no>::shape[0],
             mdot::real_sh_operators_crtp<mdot::sh_id_no>::shape[1]};
    auto arr = mdot::real_sh_operators_crtp<mdot::sh_id_no>::array;
    vec = std::vector<double>(arr.begin(), arr.end());
  } else if (name == "sh-sp") {
    ndim = mdot::real_sh_operators_crtp<mdot::sh_sp_no>::size;
    shape = {mdot::real_sh_operators_crtp<mdot::sh_sp_no>::shape[0],
             mdot::real_sh_operators_crtp<mdot::sh_sp_no>::shape[1]};
    auto arr = mdot::real_sh_operators_crtp<mdot::sh_sp_no>::array;
    vec = std::vector<double>(arr.begin(), arr.end());
  } else if (name == "sh-sm") {
    ndim = mdot::real_sh_operators_crtp<mdot::sh_sm_no>::size;
    shape = {mdot::real_sh_operators_crtp<mdot::sh_sm_no>::shape[0],
             mdot::real_sh_operators_crtp<mdot::sh_sm_no>::shape[1]};
    auto arr = mdot::real_sh_operators_crtp<mdot::sh_sm_no>::array;
    vec = std::vector<double>(arr.begin(), arr.end());
  } else if (name == "sh-sx") {
    ndim = mdot::real_sh_operators_crtp<mdot::sh_sx_no>::size;
    shape = {mdot::real_sh_operators_crtp<mdot::sh_sx_no>::shape[0],
             mdot::real_sh_operators_crtp<mdot::sh_sx_no>::shape[1]};
    auto arr = mdot::real_sh_operators_crtp<mdot::sh_sx_no>::array;
    vec = std::vector<double>(arr.begin(), arr.end());
  } else if (name == "sh-sz") {
    ndim = mdot::real_sh_operators_crtp<mdot::sh_sz_no>::size;
    shape = {mdot::real_sh_operators_crtp<mdot::sh_sz_no>::shape[0],
             mdot::real_sh_operators_crtp<mdot::sh_sz_no>::shape[1]};
    auto arr = mdot::real_sh_operators_crtp<mdot::sh_sz_no>::array;
    vec = std::vector<double>(arr.begin(), arr.end());
  } else {
    throw std::invalid_argument(std::string("The single operator \"") + name +
                                std::string("\" is not available.\n"
                                            "\t\t- Available operators are "
                                            "sh-id, sh-sp, sh-sm, sh-sx, "
                                            "sh-sz, ..."));
  }
  //
  auto deallocator = py::capsule(&vec, [](void *f) {
    // py::detail::get_internals();
    std::cout << "cleaning!" << std::endl;
    auto vec_ptr = reinterpret_cast<std::vector<dnum_t> *>(f);
    vec_ptr->clear();
  });
  numpy_array<double> np_out(ndim, vec.data(), deallocator);
  np_out.resize(shape);
  return np_out;
}

PYBIND11_MODULE(operators_mdot, m) {
  m.doc() = "a pybind11 for quantum simulations";
  // py::bind_map<std::map<std::tuple<uint8_t, uint8_t>,
  // numpy_array<double>>>(m, "MapBlocsDouble");
  m.def("single_operator_real", &py_single_operator_real,
        py::arg("name") = "sh-id", "return a dense single operator.");
  m.def("single_operator_re", &single_operator_re, "return operators");
}
