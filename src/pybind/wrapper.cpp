#include <complex>

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "pybind/pyhmatrix.hpp"
#include "pybind/utils.hpp"

// #include "fhmdot/include/babel_type.hpp"
#include "fhmdot/utils/qnum.hpp"

using namespace fhmdot::qnum;
namespace py = pybind11;

template <typename T> using numpy_array = py::array_t<T, py::array::c_style>;

template <typename QT>
void declare_generic_pymps(py::module &m, std::string typestr) {
  using tclass = QT;
  std::string pyclass_name = std::string("hmat_") + typestr;
  py::class_<tclass>(m, pyclass_name.c_str())
      .def(py::init<>()) // tclass::pyhmat_type
      .def("set",
           [](tclass &self, tclass::pyhmat_type py_in) -> void {
             self.from_python(py_in);
           })
      .def("save",
           [](tclass &self, std::string filename) -> void {
             self.save(filename);
           })
      .def("load",
           [](tclass &self, std::string filename) -> void {
             self.load(filename);
           })
      //.def("get", [](tclass &self) -> tclass::pyhmat_type {
      //  return self.to_python();
      //})
      ;
}

numpy_array<data_t> check(numpy_array<data_t> np_in) {
  py::buffer_info np_in_info = np_in.request();
  // np_in_info.view
  std::size_t n = np_in.size() - 2;
  auto ptr = np_in.data() + 1;
  auto fake_deallocator = py::capsule(ptr, [](void *ptr) { (void)ptr; });
  numpy_array<data_t> np_out(n, ptr, fake_deallocator);
  return np_out;
}

using num_t = double;

using real_mps_sh_none = pyhmatrix::pymps<quantum_number_crtp<sh_none>, num_t>;
using real_mps_sh_u1 = pyhmatrix::pymps<quantum_number_crtp<sh_u1>, num_t>;
using real_mps_sh_su2 = pyhmatrix::pymps<quantum_number_crtp<sh_su2>, num_t>;
using complex_mps_sh_none =
    pyhmatrix::pymps<quantum_number_crtp<sh_none>, std::complex<num_t>>;
using complex_mps_sh_u1 =
    pyhmatrix::pymps<quantum_number_crtp<sh_u1>, std::complex<num_t>>;
using complex_mps_sh_su2 =
    pyhmatrix::pymps<quantum_number_crtp<sh_su2>, std::complex<num_t>>;

PYBIND11_MODULE(fhm, m) {
  m.doc() = "Fast Hilbert Matrix Dot - a matrix representation (single matrix "
            "from MPS)";
  //   m.def("check", &check,
  //         "A numpy view of num_t without first and last element");
  m.def("is_floating_precision", &is_floating_precision,
        "check if library precision is fixed to float 32 (if not, float64 is "
        "used)");
  declare_generic_pymps<real_mps_sh_none>(m, "real_mps_sh_none");
  declare_generic_pymps<real_mps_sh_u1>(m, "real_mps_sh_u1");
  declare_generic_pymps<real_mps_sh_su2>(m, "real_mps_sh_su2");
  declare_generic_pymps<complex_mps_sh_none>(m, "complex_mps_sh_none");
  declare_generic_pymps<complex_mps_sh_u1>(m, "complex_mps_sh_u1");
  declare_generic_pymps<complex_mps_sh_su2>(m, "complex_mps_sh_su2");
  m.def(
      "hmat",
      [](std::string qname = "")
          -> std::variant<real_mps_sh_none, real_mps_sh_u1, real_mps_sh_su2> {
        if (qname == "sh_none") {
          return real_mps_sh_none();
        } else if (qname == "sh_u1") {
          return real_mps_sh_u1();
        } else if (qname == "sh_su2") {
          return real_mps_sh_su2();
        } else {
          throw std::range_error("Model Error.\n\t\t- all models are listed in "
                                 "the python module.");
        }
      },
      py::arg("qname") = "sh_none");
}
