/// mps, mpo language for python

#pragma once

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
//#include <vector>

#include "fhmdot/include/hmatrix.hpp"

// using namespace fhmdot::hmatrix;

namespace pyhmatrix {
template <class Q, typename T> class pymps : fhmdot::hmatrix::mps<Q, T> {
public:
  typedef Q qnum_type;
  typedef T value_type;
  typedef uint16_t index_t;
  typedef uint16_t shape_t;
  typedef std::tuple<index_t, index_t, index_t> index_type;
  typedef std::tuple<shape_t, shape_t, shape_t> shape_type;
  typedef std::tuple<index_t, index_t, index_t, index_t, index_t, index_t>
      index_shape_type;

  typedef pybind11::array_t<value_type, pybind11::array::c_style> numpy_array;
  typedef typename std::pair<index_shape_type, numpy_array> pyhmat_type;

  pymps() {}

  // void from_python(hmat_type mps_in){};
  // hmat_type to_python(){};
};

template <class Q, typename T> class pympo {

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

} // namespace pyhmatrix
