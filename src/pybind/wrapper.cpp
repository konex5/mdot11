#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "pybind/pyhmatrix.hpp"
#include "pybind/utils.hpp"

#include "fhmdot/include/babel_type.hpp"
#include "fhmdot/include/qnum.hpp"

namespace py = pybind11;

template <typename T> using numpy_array = py::array_t<T, py::array::c_style>;

template <typename T>
void declare_generic_mps(py::module &m, std::string typestr) {
  using tclass = T;
  std::string pyclass_name = std::string("hmat_") + typestr;
  py::class_<tclass>(m, pyclass_name.c_str()).def(py::init<>())
      // .def("set_defaults",
      //      [](tclass &self, std::vector<std::string> &keys,
      //      numpy_array<py_std::value_type> np_values) -> void {
      //        py_std::size_type k =
      //        py_std::size_type(np_values.request().shape[0]); if (k !=
      //        keys.size())
      //        {
      //          throw
      //          std::range_error(msg_pybind_dimension_mismatch_for({"keys",
      //          "values.shape[0]"}));
      //        }
      //        auto *values = const_cast<py_std::value_type
      //        *>(np_values.data()); self.py_set_defaults(k, values, keys);
      //      })
      ;
}

numpy_array<data_t> check(numpy_array<data_t> np_in) {
  py::buffer_info np_in_info = np_in.request();
  // np_in_info.view
  std::size_t n = np_in.size() - 2;
  auto ptr = np_in.data() + 1;
  auto fake_deallocator = py::capsule(ptr, [](void *ptr) {});
  numpy_array<data_t> np_out(n, ptr, fake_deallocator);
  return np_out;
}

using mps_sh_none = pyhmatrix::pymps<quantum_number_crtp<sh_none>, data_t>;
using mps_sh_u1 = pyhmatrix::pymps<quantum_number_crtp<sh_u1>, data_t>;
using mps_sh_su2 = pyhmatrix::pymps<quantum_number_crtp<sh_su2>, data_t>;

PYBIND11_MODULE(fhm, m) {
  m.doc() = "Fast Hilbert Matrix Dot - a matrix representation (single matrix "
            "from MPS)";
  //   m.def("check", &check,
  //         "A numpy view of num_t without first and last element");
  m.def("is_floating_precision", &is_floating_precision,
        "check if library precision is fixed to float 32 (if not, float64 is "
        "used)");
  declare_generic_mps<mps_sh_none>(m, "sh_none");
  declare_generic_mps<mps_sh_u1>(m, "sh_u1");
  declare_generic_mps<mps_sh_su2>(m, "sh_su2");
  m.def(
      "hmat",
      [](std::string qname =
             "") -> std::variant<mps_sh_none, mps_sh_u1, mps_sh_su2> {
        if (qname == "sh_none") {
          return mps_sh_none();
        } else if (qname == "sh_u1") {
          return mps_sh_u1();
        } else if (qname == "sh_su2") {
          return mps_sh_su2();
        } else {
          throw std::range_error("Model Error.\n\t\t- all models are listed in "
                                 "the python module.");
        }
      },
      py::arg("qname") = "sh_none");
}
