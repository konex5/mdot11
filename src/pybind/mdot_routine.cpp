#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "mdot/include/babel_type.hpp"
#include "mdot/include/routine/interface.hpp"


namespace py = pybind11;

template <typename T> using numpy_array = py::array_t<T, py::array::c_style>;

using pydmbloc_type =
    std::map<std::tuple<uint16_t, uint8_t,uint16_t>, numpy_array<dnum_t>>;

using pydtbloc_type =
    std::map<std::tuple<uint16_t, uint8_t, uint8_t,uint16_t>, numpy_array<dnum_t>>;



void py_mm_to_theta_no_gate(pydtbloc_type dst, pydmbloc_type lhs, pydmbloc_type rhs, bool conserve_left_right = false) {
    // dst
    //mdot::mm_to_theta_no_gate()
}


PYBIND11_MODULE(mdot_routine, m) {
  m.doc() = "routine to speedup code execution";

  m.def("mm_to_theta_no_gate", &py_mm_to_theta_no_gate, py::arg("dst_blocs"), py::arg("lhs_blocs"), py::arg("rhs_blocs"), py::arg("conserve_left_right") = false,
         "execute mm_to_theta_no_gate.");
  
}
