#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "mdot/include/babel_type.hpp"
#include "mdot/include/routine/interface.hpp"
#include "pybind/include/translate.hpp"

namespace py = pybind11;

template <typename T> using numpy_array = py::array_t<T, py::array::c_style>;

using pydmbloc_type =
    std::map<std::tuple<uint16_t, uint8_t, uint16_t>, numpy_array<dnum_t>>;

using pydtbloc_type = std::map<std::tuple<uint16_t, uint8_t, uint8_t, uint16_t>,
                               numpy_array<dnum_t>>;

pydtbloc_type py_mm_to_theta_no_gate(pydmbloc_type lhs,
                            pydmbloc_type rhs,
                            bool conserve_left_right = false) {
  dmbloc_t tmp_lhs, tmp_rhs;
  translate_dmbloc_py2cpp(tmp_lhs, lhs);
  translate_dmbloc_py2cpp(tmp_rhs, rhs);
  dtbloc_t tmp_dst;
  mdot::mm_to_theta_no_gate(tmp_dst, tmp_lhs, tmp_rhs, conserve_left_right);
  pydtbloc_type dst_out;
  translate_dtbloc_cpp2py(dst_out, tmp_dst);
  return dst_out;
}

std::pair<pydmbloc_type,pydmbloc_type> py_routine(pydmbloc_type lhs,
                            pydmbloc_type rhs,
                            bool conserve_left_right = false) {
  dmbloc_t tmp_lhs, tmp_rhs;
  translate_dmbloc_py2cpp(tmp_lhs, lhs);
  translate_dmbloc_py2cpp(tmp_rhs, rhs);
  dtbloc_t tmp_dst;
  mdot::mm_to_theta_no_gate(tmp_dst, tmp_lhs, tmp_rhs, conserve_left_right);
  dnum_t dw = 0;
  index_t chi_max=8;
  dnum_t eps=1e-8;
  std::cout << std::endl <<  std::endl << "okay" << std::endl;
  mdot::theta_to_mm(tmp_dst,tmp_lhs,tmp_rhs,dw,chi_max,true,1, 1,eps);
  std::cout << std::endl <<  std::endl << "okay" << std::endl;
  std::pair<pydmbloc_type,pydmbloc_type> dst_out;
  translate_dmbloc_cpp2py(dst_out.first, tmp_lhs);
  translate_dmbloc_cpp2py(dst_out.second, tmp_rhs);
  return dst_out;
}


PYBIND11_MODULE(mdot_routine, m) {
  m.doc() = "routine to speedup code execution";
  m.def("routine", &py_routine);
  m.def("mm_to_theta_no_gate", &py_mm_to_theta_no_gate,
        py::arg("lhs_blocs"), py::arg("rhs_blocs"),
        py::arg("conserve_left_right") = false, "execute mm_to_theta_no_gate.");
}
