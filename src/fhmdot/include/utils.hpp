#include <boost/type_traits/is_complex.hpp>
#include <complex>

#ifndef FLOAT_PRECISION
using data_t = double;
#else
using data_t = float;
#endif

namespace fhmdot {
namespace utils {

template <typename T> constexpr bool is_complex() {
  return boost::is_complex<T>::value;
}

template <typename T> constexpr bool is_float() {
  if (is_complex<T>()) {
    return std::is_same<typename std::complex<float>, T>::value;
  } else {
    return std::is_same<float, T>::value;
  }
}

} // namespace utils

} // namespace fhmdot
