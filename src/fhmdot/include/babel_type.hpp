#pragma once

#include <vector>

using qn_type = int8_t;
using index_small_t = uint8_t;
using index_t = uint16_t;

#ifndef FLOAT_PRECISION
using data_t = double;
#else
using data_t = float;
#endif

using num_t = data_t;
using arr_t = std::vector<data_t>;

using m_index_t = std::tuple<index_t, index_small_t, index_t>;
using m_shape_t = std::tuple<index_t, index_small_t, index_t>;

using t_index_t = std::tuple<index_t, index_small_t, index_small_t, index_t>;
using t_shape_t = std::tuple<index_t, index_small_t, index_small_t, index_t>;

// using hmat_t = std::map<m_shape_t, arr_t>;
