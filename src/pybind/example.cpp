#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using dnum_t = double;
namespace py = pybind11;
template <typename T> using numpy_array = py::array_t<T, py::array::c_style>;
using pydblocs_type =
    std::map<std::tuple<uint8_t, uint8_t>, numpy_array<dnum_t>>;

pydblocs_type py_simple() {
  pydblocs_type output;
  std::vector<double> vec({1, 2, 3, 4, 5});

  // new is mandatory for python memory usage
  std::vector<dnum_t> *vec_ptr = new std::vector<dnum_t>;
  vec_ptr->swap(vec);

  auto deallocator = py::capsule(vec_ptr, [](void *ptr) {
    auto v_ptr = reinterpret_cast<std::vector<dnum_t> *>(ptr);
    v_ptr->clear();
    delete v_ptr;
  });
  // constexpr size_t elsize = sizeof(dnum_t);
  py::ssize_t shape[2]{1, 5};
  // py::ssize_t strides[2]{5*elsize, elsize};

  numpy_array<double> np_out(shape, vec_ptr->data(), deallocator);
  np_out.owndata();

  output[{0, 0}] = np_out;
  return output;
}

PYBIND11_MODULE(example, m) {
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
  m.def("simple", &py_simple);
}