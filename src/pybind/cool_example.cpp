#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(cool_example, m) {
  m.def("f", []() {
    constexpr size_t elsize = sizeof(double);
    size_t shape[3]{100, 1000, 1000};
    size_t strides[3]{1000 * 1000 * elsize, 1000 * elsize, elsize};
    auto a = py::array_t<double>(shape, strides);
    auto view = a.mutable_unchecked<3>();

    for (size_t i = 0; i < a.shape(0); i++) {
      for (size_t j = 0; j < a.shape(1); j++) {
        for (size_t k = 0; k < a.shape(2); k++) {
          view(i, j, k) = i + j + k;
        }
      }
    }
    return a;
  });
}