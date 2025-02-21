/// mps, mpo language for python

#pragma once

#include "fhmdot/include/yofi.hpp"

namespace pybind {
template <class Q, typename T> class mps {
public:
  typedef Q qnum_type;
  typedef T value_type;

  // void from_python(std::list<std::tuple<>>){};
  // void to_python(std::list<std::pair<>>){};

  void load(std::string filename){

  };
  void save(std::string filename){

  };

private:
  // std::map<std::tuple<3>, std::vector<value_type>> arr_;
}

template <class Q, typename T>
class mpo {

public:
  typedef Q qnum_type;
  typedef T value_type;

  // void from_python(std::list<std::tuple<>>)  {};
  // void to_python(std::list<std::pair<>>) {};

  void load(std::string filename){

  };
  void save(std::string filename){

  };

private:
  // std::map<std::tuple<4>, std::vector<value_type>> arr_;
}

} // namespace pybind
