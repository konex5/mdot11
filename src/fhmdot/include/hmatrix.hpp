/// mps, mpo language for python

#pragma once

#include <vector>

// #include "fhmdot/include/yofi.hpp"

namespace fhmdot {
namespace hmatrix {
template <class Q, typename T> class mps {
public:
  typedef Q qnum_type;
  typedef T value_type;
  typedef uint16_t index_t;
  typedef uint16_t shape_t;
  typedef std::tuple<index_t, index_t, index_t> index_type;
  typedef std::tuple<shape_t, shape_t, shape_t> shape_type;
  typedef std::tuple<index_t, index_t, index_t, index_t, index_t, index_t>
      index_shape_type;

  typedef typename std::pair<index_shape_type, std::vector<T>> hmat_type;

  mps() {}

  void load(std::string filename){};
  void save(std::string filename){};

  void from_std(hmat_type mps_in){};
  hmat_type to_std() { return {{0, 0, 0, 0, 0, 0}, {0, 1, 2, 3, 4}}; };

private:
  hmat_type arr_;
};

template <class Q, typename T> class mpo {

public:
  typedef Q qnum_type;
  typedef T value_type;

private:
  // std::map<std::tuple<4>, std::vector<value_type>> arr_;
};

} // namespace hmatrix
} // namespace fhmdot