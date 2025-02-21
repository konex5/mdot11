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
  pydtbloc_type dst;
  translate_dtbloc_cpp2py(dst, tmp_dst);
  return dst;
}

PYBIND11_MODULE(mdot_routine, m) {
  m.doc() = "routine to speedup code execution";

  m.def("mm_to_theta_no_gate", &py_mm_to_theta_no_gate,
        py::arg("lhs_blocs"), py::arg("rhs_blocs"),
        py::arg("conserve_left_right") = false, "execute mm_to_theta_no_gate.");
}
