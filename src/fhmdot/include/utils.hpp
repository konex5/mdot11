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

template <typename T> constexpr char num_character() {
  if (std::is_same<float, T>::value) {
    return 'F';
  } else if (std::is_same<double, T>::value) {
    return 'D';
  } else if (std::is_same<typename std::complex<float>, T>::value) {
    return 'C';
  } else if (std::is_same<typename std::complex<double>, T>::value) {
    return 'Z';
  } else {
    return '?';
  };
};

} // namespace utils

} // namespace fhmdot
