#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>


#include <string>
#include "mdot/include/babel_type.hpp"
#include "mdot/include/operators.hpp"

namespace py = pybind11;

template <typename T>
using numpy_array = py::array_t<T, py::array::c_style>;

numpy_array<dnum_t> single_operator_r(std::string name, std::string qbasis) {
    //mdot::
    auto test = single_operator_real(name,qbasis);
    auto op = std::get<0>(test)[{0,0}];
    std::size_t n = op.size();
    auto ptr = op.data();
    auto deallocator = py::capsule(ptr, [](void *f) { auto foo = reinterpret_cast<std::vector<dnum_t> *>(f);  delete foo; });
    numpy_array<dnum_t> np_out(n, ptr, deallocator);
    
    return np_out;
}

PYBIND11_MODULE(operators_mdot, m) {
    m.doc() = "a pybind11 for quantum simulations";
    m.def("single_operator_r", &single_operator_r, "return operators");
}
