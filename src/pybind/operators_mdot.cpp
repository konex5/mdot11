#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>


#include <string>
#include <map>
#include <tuple>
#include <complex>
#include "mdot/include/babel_type.hpp"


#include "mdot/include/operators.hpp"

namespace py = pybind11;

template <typename T>
using numpy_array = py::array_t<T, py::array::c_style>;

using pydblocs_type = std::map<std::tuple<uint8_t, uint8_t>, numpy_array<double>>;
using pyzblocs_type = std::map<std::tuple<uint8_t, uint8_t>, numpy_array<double>>;


pydblocs_type single_operator_re(std::string name, std::string qbasis) {
    //mdot::
    auto test = single_operator_real(name,qbasis);
    dnum_t normalisation = std::get<1>(test);
    auto blocs = std::get<0>(test);
    //
    pydblocs_type output;
    std::tuple<uint8_t, uint8_t> indices;
    std::vector<dnum_t> vec_arr;
    //
    
    for (auto const& x : blocs) {
        indices = {std::get<0>(x.first),std::get<1>(x.first)};
        vec_arr = x.second;
        std::size_t n = vec_arr.size();
        auto ptr = vec_arr.data();
        auto deallocator = py::capsule(&vec_arr, [](void* ptr) { auto vec_ptr = reinterpret_cast<std::vector<dnum_t> *>(ptr); vec_ptr->clear(); });
        numpy_array<dnum_t> np_out(n, ptr, deallocator);
        output[indices] = np_out;
    }
    
    return output;
}

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
    m.def("single_operator_re", &single_operator_re, "return operators");
}
