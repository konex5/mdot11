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

#include "mdot/include/blocs_static.hpp"
#include "mdot/include/operators_static.hpp"

namespace py = pybind11;

template <typename T> using numpy_array = py::array_t<T, py::array::c_style>;

using pydblocs_type =
    std::map<std::tuple<uint8_t, uint8_t>, numpy_array<dnum_t>>;
using pyzblocs_type =
    std::map<std::tuple<uint8_t, uint8_t>, numpy_array<znum_t>>;

pydblocs_type py_single_operator_blocs_real(std::string name) {
  index_t nb_blocs;
  std::vector<std::tuple<index_t, index_t>> indices;
  std::vector<index_t> sizes;
  std::vector<std::tuple<index_t, index_t>> shapes;
  std::vector<std::vector<double>> vecs;

  if (name == "sh-id") {
    nb_blocs = mdot::real_sh_blocs_crtp<mdot::sh_id_u1>::nb_blocs;
    indices = mdot::real_sh_blocs_crtp<mdot::sh_id_u1>::get_indices();
    sizes = mdot::real_sh_blocs_crtp<mdot::sh_id_u1>::get_sizes();
    shapes = mdot::real_sh_blocs_crtp<mdot::sh_id_u1>::get_shapes();
    auto arrs = mdot::real_sh_blocs_crtp<mdot::sh_id_u1>::get_arrays();
    for (index_t i = 0; i < nb_blocs; i++)
      vecs.push_back(std::vector<double>(arrs[i].begin(), arrs[i].end()));
  } else if (name == "sh-sm") {
    nb_blocs = mdot::real_sh_blocs_crtp<mdot::sh_sm_u1>::nb_blocs;
    indices = mdot::real_sh_blocs_crtp<mdot::sh_sm_u1>::get_indices();
    sizes = mdot::real_sh_blocs_crtp<mdot::sh_sm_u1>::get_sizes();
    shapes = mdot::real_sh_blocs_crtp<mdot::sh_sm_u1>::get_shapes();
    auto arrs = mdot::real_sh_blocs_crtp<mdot::sh_sm_u1>::get_arrays();
    for (index_t i = 0; i < nb_blocs; i++)
      vecs.push_back(std::vector<double>(arrs[i].begin(), arrs[i].end()));
  } else if (name == "sh-sp") {
    nb_blocs = mdot::real_sh_blocs_crtp<mdot::sh_sp_u1>::nb_blocs;
    indices = mdot::real_sh_blocs_crtp<mdot::sh_sp_u1>::get_indices();
    sizes = mdot::real_sh_blocs_crtp<mdot::sh_sp_u1>::get_sizes();
    shapes = mdot::real_sh_blocs_crtp<mdot::sh_sp_u1>::get_shapes();
    auto arrs = mdot::real_sh_blocs_crtp<mdot::sh_sp_u1>::get_arrays();
    for (index_t i = 0; i < nb_blocs; i++)
      vecs.push_back(std::vector<double>(arrs[i].begin(), arrs[i].end()));
  } else if (name == "sh-sx") {
    nb_blocs = mdot::real_sh_blocs_crtp<mdot::sh_sx_u1>::nb_blocs;
    indices = mdot::real_sh_blocs_crtp<mdot::sh_sx_u1>::get_indices();
    sizes = mdot::real_sh_blocs_crtp<mdot::sh_sx_u1>::get_sizes();
    shapes = mdot::real_sh_blocs_crtp<mdot::sh_sx_u1>::get_shapes();
    auto arrs = mdot::real_sh_blocs_crtp<mdot::sh_sx_u1>::get_arrays();
    for (index_t i = 0; i < nb_blocs; i++)
      vecs.push_back(std::vector<double>(arrs[i].begin(), arrs[i].end()));
  } else if (name == "sh-sz") {
    nb_blocs = mdot::real_sh_blocs_crtp<mdot::sh_sz_u1>::nb_blocs;
    indices = mdot::real_sh_blocs_crtp<mdot::sh_sz_u1>::get_indices();
    sizes = mdot::real_sh_blocs_crtp<mdot::sh_sz_u1>::get_sizes();
    shapes = mdot::real_sh_blocs_crtp<mdot::sh_sz_u1>::get_shapes();
    auto arrs = mdot::real_sh_blocs_crtp<mdot::sh_sz_u1>::get_arrays();
    for (index_t i = 0; i < nb_blocs; i++)
      vecs.push_back(std::vector<double>(arrs[i].begin(), arrs[i].end()));
  } else {
    throw std::invalid_argument(std::string("The single operator (blocs) \"") +
                                name +
                                std::string("\" is not available.\n"
                                            "\t\t- Available operators are "
                                            "sh-id, sh-sp, sh-sm, sh-sx, "
                                            "sh-sz, ..."));
  }

  pydblocs_type output;

  for (index_t i = 0; i < nb_blocs; i++) {
    auto deallocator = py::capsule(&vecs[i], [](void *ptr) {
      auto vec_ptr = reinterpret_cast<std::vector<dnum_t> *>(ptr);
      vec_ptr->clear();
    });
    numpy_array<dnum_t> np_out(sizes[i], vecs[i].data(), deallocator);
    np_out.resize({std::get<0>(shapes[i]), std::get<1>(shapes[i])});
    output[{std::get<0>(indices[i]), std::get<1>(indices[i])}] = np_out;
  }
  return output;
}

pyzblocs_type py_single_operator_blocs_cplx(std::string name) {
  index_t nb_blocs;
  std::vector<std::tuple<index_t, index_t>> indices;
  std::vector<index_t> sizes;
  std::vector<std::tuple<index_t, index_t>> shapes;
  std::vector<std::vector<znum_t>> vecs;

  if (name == "sh-id") {
    nb_blocs = mdot::cplx_sh_blocs_crtp<mdot::sh_id_cplx_u1>::nb_blocs;
    indices = mdot::cplx_sh_blocs_crtp<mdot::sh_id_cplx_u1>::get_indices();
    sizes = mdot::cplx_sh_blocs_crtp<mdot::sh_id_cplx_u1>::get_sizes();
    shapes = mdot::cplx_sh_blocs_crtp<mdot::sh_id_cplx_u1>::get_shapes();
    auto arrs = mdot::cplx_sh_blocs_crtp<mdot::sh_id_cplx_u1>::get_arrays();
    for (index_t i = 0; i < nb_blocs; i++)
      vecs.push_back(std::vector<znum_t>(arrs[i].begin(), arrs[i].end()));
  } else if (name == "sh-sy") {
    nb_blocs = mdot::cplx_sh_blocs_crtp<mdot::sh_sy_u1>::nb_blocs;
    indices = mdot::cplx_sh_blocs_crtp<mdot::sh_sy_u1>::get_indices();
    sizes = mdot::cplx_sh_blocs_crtp<mdot::sh_sy_u1>::get_sizes();
    shapes = mdot::cplx_sh_blocs_crtp<mdot::sh_sy_u1>::get_shapes();
    auto arrs = mdot::cplx_sh_blocs_crtp<mdot::sh_sy_u1>::get_arrays();
    for (index_t i = 0; i < nb_blocs; i++)
      vecs.push_back(std::vector<znum_t>(arrs[i].begin(), arrs[i].end()));
  } else {
    throw std::invalid_argument(std::string("The single operator (blocs) \"") +
                                name +
                                std::string("\" is not available.\n"
                                            "\t\t- Available operators are "
                                            "sh-id, sh-sy, ..."));
  }

  pyzblocs_type output;

  for (index_t i = 0; i < nb_blocs; i++) {
    auto deallocator = py::capsule(&vecs[i], [](void *ptr) {
      auto vec_ptr = reinterpret_cast<std::vector<znum_t> *>(ptr);
      vec_ptr->clear();
    });
    numpy_array<znum_t> np_out(sizes[i], vecs[i].data(), deallocator);
    np_out.resize({std::get<0>(shapes[i]), std::get<1>(shapes[i])});
    output[{std::get<0>(indices[i]), std::get<1>(indices[i])}] = np_out;
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
  } else if (name == "sh-sm") {
    ndim = mdot::real_sh_operators_crtp<mdot::sh_sm_no>::size;
    shape = {mdot::real_sh_operators_crtp<mdot::sh_sm_no>::shape[0],
             mdot::real_sh_operators_crtp<mdot::sh_sm_no>::shape[1]};
    auto arr = mdot::real_sh_operators_crtp<mdot::sh_sm_no>::array;
    vec = std::vector<double>(arr.begin(), arr.end());
  } else if (name == "sh-sp") {
    ndim = mdot::real_sh_operators_crtp<mdot::sh_sp_no>::size;
    shape = {mdot::real_sh_operators_crtp<mdot::sh_sp_no>::shape[0],
             mdot::real_sh_operators_crtp<mdot::sh_sp_no>::shape[1]};
    auto arr = mdot::real_sh_operators_crtp<mdot::sh_sp_no>::array;
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

numpy_array<znum_t> py_single_operator_cplx(std::string name) {
  py::ssize_t ndim;
  std::vector<py::ssize_t> shape;
  std::vector<znum_t> vec;

  if (name == "sh-id") {
    ndim = mdot::cplx_sh_operators_crtp<mdot::sh_id_cplx_no>::size;
    shape = {mdot::cplx_sh_operators_crtp<mdot::sh_id_cplx_no>::shape[0],
             mdot::cplx_sh_operators_crtp<mdot::sh_id_cplx_no>::shape[1]};
    auto arr = mdot::cplx_sh_operators_crtp<mdot::sh_id_cplx_no>::array;
    vec = std::vector<znum_t>(arr.begin(), arr.end());
  } else if (name == "sh-sy") {
    ndim = mdot::cplx_sh_operators_crtp<mdot::sh_sy_no>::size;
    shape = {mdot::cplx_sh_operators_crtp<mdot::sh_sy_no>::shape[0],
             mdot::cplx_sh_operators_crtp<mdot::sh_sy_no>::shape[1]};
    auto arr = mdot::cplx_sh_operators_crtp<mdot::sh_sy_no>::array;
    vec = std::vector<znum_t>(arr.begin(), arr.end());
  } else {
    throw std::invalid_argument(std::string("The single operator \"") + name +
                                std::string("\" is not available.\n"
                                            "\t\t- Available operators are "
                                            "sh-id, sh-sy, ..."));
  }
  //
  auto deallocator = py::capsule(&vec, [](void *f) {
    // py::detail::get_internals();
    std::cout << "cleaning!" << std::endl;
    auto vec_ptr = reinterpret_cast<std::vector<znum_t> *>(f);
    vec_ptr->clear();
  });
  numpy_array<znum_t> np_out(ndim, vec.data(), deallocator);
  np_out.resize(shape);
  return np_out;
}

PYBIND11_MODULE(operators_mdot, m) {
  m.doc() = "a pybind11 for quantum simulations";

  m.def("single_operator_blocs_real", &py_single_operator_blocs_real,
        py::arg("name") = "sh-id", "return a dictionary of blocs.");
  m.def("single_operator_blocs_cplx", &py_single_operator_blocs_cplx,
        py::arg("name") = "sh-id", "return a dictionary of blocs.");
  m.def("single_operator_real", &py_single_operator_real,
        py::arg("name") = "sh-id", "return a dense single operator.");
  m.def("single_operator_cplx", &py_single_operator_cplx,
        py::arg("name") = "sh-id", "return a dense single operator.");
}
