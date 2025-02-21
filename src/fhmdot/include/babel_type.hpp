#pragma once

using qn_type = int8_t;
using index_t = uint8_t;

#ifndef FLOAT_PRECISION
using data_t = double;
#else
using data_t = float;
#endif

#ifndef CMPLX_PRECISION
using num_t = data_t;
#else
#include <complex>
using num_t = typename std::complex<data_t>;
#endif

using hmat_t = std::map<std::tuple<index_t, index_t>, std::vector<num_t>>;
