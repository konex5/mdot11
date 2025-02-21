/// mps, mpo language for python

#pragma once

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
//#include <vector>

// #include "fhmdot/include/yofi.hpp"

namespace hmatrix {
template <class Q, typename T> class mps {
public:
  typedef Q qnum_type;
  typedef T value_type;
  typedef std::tuple<int, int, int> index_type;

  typedef pybind11::array_t<value_type, pybind11::array::c_style> numpy_array;
  typedef typename std::list<std::pair<index_type, numpy_array>> hmat_type;

  mps() {}

  // void from_python(hmat_type mps_in){};
  // hmat_type to_python(){};

  // void load(std::string filename){};
  // void save(std::string filename){};

private:
  hmat_type arr_;
};

template <class Q, typename T> class mpo {

public:
  typedef Q qnum_type;
  typedef T value_type;

  // void from_python(std::list<std::tuple<>>)  {};
  // void to_python(std::list<std::pair<>>) {};

  // void load(std::string filename){};
  // void save(std::string filename){};

private:
  // std::map<std::tuple<4>, std::vector<value_type>> arr_;
};

} // namespace hmatrix
