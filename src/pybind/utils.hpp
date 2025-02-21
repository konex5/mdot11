#pragma once

#include "fhmdot/include/babel_type.hpp"

constexpr bool is_floating_precision() {
  return std::is_same<float, data_t>::value;
}
