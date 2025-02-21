#pragma once

#include <string>
#include <tuple>

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <fstream>
#include <iostream>

namespace fhmdot {

namespace fcontent {
int read_tuple();
int write_tuple();
int read_data(ifstream file) {
  // ifstream file("hello.z", ios_base::in | ios_base::binary);
  filtering_streambuf<input> in;
  in.push(zlib_decompressor());
  in.push(file);
  boost::iostreams::copy(in, cout);
};
int write_data();
} // namespace fcontent
} // namespace fhmdot