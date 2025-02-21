#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "mdot/include/babel_type.hpp"
#include "mdot/include/routine/interface.hpp"
#include "mdot/include/routine/minimize.hpp"

#include "pybind/include/pybabel_type.hpp"
#include "pybind/include/translate.hpp"

/*
pydtbloc_type py_mm_to_theta_no_gate(pydmbloc_type lhs, pydmbloc_type rhs,
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

pydtbloc_type py_mm_to_theta_with_gate(pydmbloc_type lhs, pydmbloc_type rhs,
                                       pydgbloc_type gate,
                                       bool conserve_left_right = false) {
  dmbloc_t tmp_lhs, tmp_rhs;
  translate_dmbloc_py2cpp(tmp_lhs, lhs);
  translate_dmbloc_py2cpp(tmp_rhs, rhs);
  dgbloc_t tmp_gate;
  translate_dgbloc_py2cpp(tmp_gate, gate);

  dtbloc_t tmp_dst;
  mdot::mm_to_theta_with_gate(tmp_dst, tmp_lhs, tmp_rhs, tmp_gate,
                              conserve_left_right);
  pydtbloc_type dst_out;
  translate_dtbloc_cpp2py(dst_out, tmp_dst);
  return dst_out;
}
*/

std::tuple<pydmbloc_type, pydmbloc_type, dnum_t>
py_apply_mm(pydmbloc_type lhs, pydmbloc_type rhs, const index_t chi_max,
            const dnum_t eps, const bool normalize, const int is_um,
            const int direction_right) {
  dmbloc_t lhs_in, rhs_in;
  translate_dmbloc_py2cpp(lhs_in, lhs);
  translate_dmbloc_py2cpp(rhs_in, rhs);
  dtbloc_t tmp_dst;
  mdot::mm_to_theta_no_gate(tmp_dst, lhs_in, rhs_in, false);
  lhs_in.clear();
  rhs_in.clear();
  dnum_t dw = 0;
  mdot::theta_to_mm(tmp_dst, lhs_in, rhs_in, dw, chi_max, normalize, is_um,
                    direction_right, eps);
  tmp_dst.clear();
  std::tuple<pydmbloc_type, pydmbloc_type, dnum_t> dst_out;
  translate_dmbloc_cpp2py(std::get<0>(dst_out), lhs_in);
  translate_dmbloc_cpp2py(std::get<1>(dst_out), rhs_in);
  std::get<2>(dst_out) = dw;
  return dst_out;
}

std::tuple<pydmbloc_type, pydmbloc_type, dnum_t>
py_apply_gate_on_mm(pydmbloc_type lhs, pydmbloc_type rhs,
                    const pydgbloc_type gate, const index_t chi_max,
                    const dnum_t eps, const bool normalize, const int is_um,
                    const int direction_right) {
  dmbloc_t lhs_in, rhs_in;
  dgbloc_t gate_in;
  translate_dmbloc_py2cpp(lhs_in, lhs);
  translate_dmbloc_py2cpp(rhs_in, rhs);
  translate_dgbloc_py2cpp(gate_in, gate);
  dtbloc_t tmp_dst;
  mdot::mm_to_theta_with_gate(tmp_dst, lhs_in, rhs_in, gate_in, false);
  lhs_in.clear();
  rhs_in.clear();
  dnum_t dw = 0;
  mdot::theta_to_mm(tmp_dst, lhs_in, rhs_in, dw, chi_max, normalize, is_um,
                    direction_right, eps);
  tmp_dst.clear();
  std::tuple<pydmbloc_type, pydmbloc_type, dnum_t> dst_out;
  translate_dmbloc_cpp2py(std::get<0>(dst_out), lhs_in);
  translate_dmbloc_cpp2py(std::get<1>(dst_out), rhs_in);
  std::get<2>(dst_out) = dw;
  return dst_out;
}

pydmbloc_type py_minimize_lanczos_on_m(const pydmenvbloc_type env_bloc,
                                       pydmbloc_type mbloc,
                                       const size_t max_iteration,
                                       const dnum_t tolerance) {
  dmbloc_t mp_in;
  translate_dmbloc_py2cpp(mp_in, mbloc);
  dmenvbloc_t env_bloc_in;
  translate_dmenvbloc_py2cpp(env_bloc_in, env_bloc);
  dmbloc_t mp_out;
  mdot::lanczos_on_m(mp_out, env_bloc_in, mp_in, max_iteration, tolerance);
  pydmbloc_type dst_out;
  translate_dmbloc_cpp2py(dst_out, mp_out);
  return dst_out;
}

pydtbloc_type py_minimize_lanczos_on_mm(const pydmmenvbloc_type env_bloc,
                                       pydtbloc_type mbloc,
                                       const size_t max_iteration,
                                       const dnum_t tolerance) {
  dtbloc_t mp_in;
  translate_dtbloc_py2cpp(mp_in, mbloc);
  dmmenvbloc_t env_bloc_in;
  translate_dmmenvbloc_py2cpp(env_bloc_in, env_bloc);
  dtbloc_t mp_out;
  mdot::lanczos_on_mm(mp_out, env_bloc_in, mp_in, max_iteration, tolerance);
  pydtbloc_type dst_out;
  translate_dtbloc_cpp2py(dst_out, mp_out);
  return dst_out;
}


PYBIND11_MODULE(mdot_routine, m) {
  m.doc() = "routine to speedup code execution";
  m.def("apply_mm", &py_apply_mm, py::arg("mps_left"), py::arg("mps_right"),
        py::arg("chi_max"), py::arg("eps"), py::arg("normalize"),
        py::arg("is_um"), py::arg("direction_right"));
  m.def("apply_gate_on_mm", &py_apply_gate_on_mm, py::arg("mps_left"),
        py::arg("mps_right"), py::arg("gate"), py::arg("chi_max"),
        py::arg("eps"), py::arg("normalize"), py::arg("is_um"),
        py::arg("direction_right"));
  /*
  m.def("mm_to_theta_no_gate", &py_mm_to_theta_no_gate, py::arg("lhs_blocs"),
        py::arg("rhs_blocs"), py::arg("conserve_left_right") = false,
        "execute mm_to_theta_no_gate.");
  m.def("mm_to_theta_with_gate", &py_mm_to_theta_with_gate,
        py::arg("lhs_blocs"), py::arg("rhs_blocs"), py::arg("gate_blocs"),
        py::arg("conserve_left_right") = false, "execute mm_to_theta_no_gate.");
  */
  m.def("minimize_lanczos_on_m", &py_minimize_lanczos_on_m, py::arg("env_bloc"),
        py::arg("mps"), py::arg("max_iteration"), py::arg("error_tolerance"));
  m.def("minimize_lanczos_on_mm", &py_minimize_lanczos_on_mm,
      py::arg("env_bloc"), py::arg("theta"), py::arg("max_iteration"),
      py::arg("error_tolerance"));
}
