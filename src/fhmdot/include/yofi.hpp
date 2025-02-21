/// yet other file I/O

#include <fstream>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <vector>

#include "fhmdot/include/babel_type.hpp"

namespace fhmdot {

namespace yofi {

// printing tuple
template <std::size_t I = 0, typename... Tp>
typename std::enable_if<I == sizeof...(Tp), void>::type
print_tuple(std::tuple<Tp...> &) {}

template <std::size_t I = 0, typename... Tp>
    typename std::enable_if <
    I<sizeof...(Tp), void>::type print_tuple(std::tuple<Tp...> &t) {
  std::cout << std::get<I>(t) << ", ";
  print_tuple<I + 1, Tp...>(t);
}

// writing tuple to a file
template <std::size_t I = 0, typename... Tp>
typename std::enable_if<I == sizeof...(Tp), void>::type
write_tuple(std::ofstream &, std::tuple<Tp...> &) {}

template <std::size_t I = 0, typename... Tp>
    typename std::enable_if <
    I<sizeof...(Tp), void>::type write_tuple(std::ofstream &ofs,
                                             std::tuple<Tp...> &t) {
  ofs.write((char *)&std::get<I>(t),
            sizeof(typename std::tuple_element<I, std::tuple<Tp...>>::type));
  write_tuple<I + 1, Tp...>(ofs, t);
}

// reading tuple from a file
template <std::size_t I = 0, typename... Tp>
typename std::enable_if<I == sizeof...(Tp), void>::type
read_tuple(std::ifstream &, std::tuple<Tp...> &) {}

template <std::size_t I = 0, typename... Tp>
    typename std::enable_if <
    I<sizeof...(Tp), void>::type read_tuple(std::ifstream &ifs,
                                            std::tuple<Tp...> &t) {
  ifs.read((char *)&std::get<I>(t),
           sizeof(typename std::tuple_element<I, std::tuple<Tp...>>::type));
  read_tuple<I + 1, Tp...>(ifs, t);
}

// printing vector
template <typename T> void print_array(std::vector<T> &arr) {
  for (const auto &item : arr) {
    std::cout << item << ",";
  }
  std::cout << std::endl;
}

// writing vector to a file
template <typename T>
void write_array(std::ofstream &ofs, std::vector<T> &arr) {
  // std::copy(arr.begin(), arr.end(), std::ostreambuf_iterator<char>(ofs));
  for (const auto &item : arr) {
    ofs.write((char *)&item, sizeof(T));
  }
}

// reading vector to a file
template <typename T> void read_array(std::ifstream &ifs, std::vector<T> &arr) {
  // ifs.read((char *)&std::get<I>(t), sizeof(typename std::tuple_element<I,
  // std::tuple<Tp...>>::type));
}

} // namespace yofi

} // namespace fhmdot