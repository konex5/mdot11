#pragma once

#include <tuple>

#include "babel_type.hpp"

template <class T> struct quantum_number_crtp {
  inline static index_t sum(index_t q1, index_t q2) { return T::qsum(q1, q2); }
  inline static index_t sub(index_t q1, index_t q2) { return T::qsub(q1, q2); }
};

struct sh_none : quantum_number_crtp<sh_none> {
  inline static index_t qsum(index_t q1, index_t q2) { return 0; }

  inline static index_t qsub(index_t q1, index_t q2) { return 0; }
};

struct sh_uone : quantum_number_crtp<sh_uone> {
  inline static index_t qsum(index_t q1, index_t q2) { return q1 + q2; }

  inline static index_t qsub(index_t q1, index_t q2) { return q1 - q2; }

  // inline static index_t combine()
};

// struct sh_sutwo : quantum_number_crtp<sh_sutwo>
// {
//   static index_t sum(index_t q1, index_t q2) {
//     return q1+q2;
//   }
//
// };

#if QNAME == QNUM_SPIN_HALF_NONE
// local quantum number : 0
constexpr index_t qn_total = 1;
constexpr index_t qsum(index_t q1, index_t q2) { return 0; }
constexpr index_t qsub(index_t q1, index_t q2) { return 0; }
// qmap : qdeg, qn_left, qn_right, qn_combined, qn_combined_offset
// constexpr std::array<std::tuple<index_t, index_t, index_t, index_t>,
// qn_total> qmap[1] = { {2, 0, 0, 0, 0} };
#elif QNAME == QNUM_SPIN_HALF_U1
// local quantum number
// q1 = 0 is sz=-1/2
// q2 = 1 is sz=+1/2
/* 'sh-U1'   : {'zero' : [(0,)], 'qn' : [(-1,),(1,)], 'deg' : [1,1], '2qn' :
   [(-2,),(0,),(2,)], '2deg' : [1,2,1],
   'map'     : [[(0,0),(0,1),(1,0),(1,1)] , [1,0,2,1],
   [slice(0,1),slice(0,1),slice(0,1),slice(1,2)]] }, # S^z_tot*/

constexpr index_t qn_total = 2;

constexpr index_t static inline qsum(constexpr index_t q1,
                                     constexpr index_t q2) {
  return q1 + q2;
}
constexpr index_t static inline qsub(constexpr index_t q1,
                                     constexpr index_t q2) {
  return q1 - q2;
}
// qmap : qdeg, qn_left, qn_right, qn_combined, qn_combined_offset
constexpr std::array<std::tuple<index_t, index_t, index_t, index_t>, qn_total>
    qmap[4] = {{1, 0, 0, 1, 0}, // deg=1, down, down => 0
               {1, 1, 1, 1, 1},
               {1, 1, 1, 1, 1},
               {1, 1, 1, 1, 1}};

#elif QNAME == QNUM_SPIN_HALF_SU2

#endif

// constexpr index_t static inline
// local_qnum(constexpr index_t left_index, constexpr index_t right_index) {
// return
//
//     if (right_index == index_t::max_value) {
//       return
//     } else if (left_index == index_t::max_value) {
//
//     } else {
//       return right_index - left_index;
//     }
