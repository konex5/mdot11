/// mps, mpo language for python

#pragma once

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
//#include <vector>

// #include "fhmdot/include/hmatrix.hpp"

// using namespace fhmdot::hmatrix;

namespace pyhmatrix {
template <class Q, typename T> class pymps : public fhmdot::hmatrix::mps<Q, T> {
public:
  typedef Q qnum_type;
  typedef T value_type;
  // using namespace fhmdot::hmatrix::mps<Q, T>;
  typedef typename fhmdot::hmatrix::mps<Q, T>::index_t index_t;
  typedef typename fhmdot::hmatrix::mps<Q, T>::shape_t shape_t;
  typedef typename fhmdot::hmatrix::mps<Q, T>::index_type index_type;
  typedef typename fhmdot::hmatrix::mps<Q, T>::shape_type shape_type;
  typedef typename fhmdot::hmatrix::mps<Q, T>::index_shape_type index_shape_type;

  typedef pybind11::array_t<value_type, pybind11::array::c_style> numpy_array;
  typedef typename std::pair<index_shape_type, numpy_array> pyhmat_type;

  pymps(){
      // pyhmat_type pymps_in
      // pyhmat_type pymps_in
      // from_python(pymps_in);
  };

  void from_python(pyhmat_type mps_in) { (void)mps_in; };
  pyhmat_type to_python(){};
};

// template <class Q, typename T> class pympo {

// public:
//   typedef Q qnum_type;
//   typedef T value_type;
// };

} // namespace pyhmatrix
