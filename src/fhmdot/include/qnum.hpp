#pragma once

#include <cmath>
#include <tuple>

#include "babel_type.hpp"

template <class T> struct quantum_number_crtp {
  static constexpr index_t dim = T::qn_dim;
  inline static index_t sum(index_t q1, index_t q2) { return T::qsum(q1, q2); }
  inline static index_t sub(index_t q1, index_t q2) { return T::qsub(q1, q2); }
};

struct sh_none : quantum_number_crtp<sh_none> {
  static constexpr index_t qn_dim = 1;
  inline static index_t qsum(index_t q1, index_t q2) { return 0; }
  inline static index_t qsub(index_t q1, index_t q2) { return 0; }
};

struct sh_u1 : quantum_number_crtp<sh_u1> {
  static constexpr index_t qn_dim = 2;
  inline static index_t qsum(index_t q1, index_t q2) { return q1 + q2; }
  inline static index_t qsub(index_t q1, index_t q2) { return q1 - q2; }
};

struct sh_su2 : quantum_number_crtp<sh_su2> {
  static constexpr index_t qn_dim = 1;
  inline static index_t qsum(index_t q1, index_t q2) { return q1 + q2; }
  inline static index_t qsub(index_t q1, index_t q2) { return q1 - q2; }
};
