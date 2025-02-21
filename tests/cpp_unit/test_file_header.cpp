#include <boost/test/unit_test.hpp>

#include "fhmdot/utils/file_header.hpp"

BOOST_AUTO_TEST_CASE(unittest_file_header_version) {
  std::string version_header = fhmdot::fheader::version();
  BOOST_CHECK(version_header.at(0) == 'V');
  BOOST_CHECK(version_header.at(1) == ':');
  BOOST_CHECK(version_header.at(3) == '.');
  BOOST_CHECK(version_header.at(5) == '.');
  BOOST_CHECK(version_header.length() == 7);
}

BOOST_AUTO_TEST_CASE(unittest_file_header_float_precision) {
  std::string precision_header = fhmdot::fheader::precision();
#ifndef FLOAT_PRECISION
  BOOST_CHECK(precision_header == "P:T");
#else
  BOOST_CHECK(precision_header == "P:F");
#endif
  BOOST_CHECK(precision_header.length() == 3);
}

BOOST_AUTO_TEST_CASE(unittest_file_header_runtime_complex) {
  BOOST_CHECK(fhmdot::fheader::runtime_complex_number(false) == "C:F");
  BOOST_CHECK(fhmdot::fheader::runtime_complex_number(true) == "C:T");
}

BOOST_AUTO_TEST_CASE(unittest_file_header_compression) {
  BOOST_CHECK(fhmdot::fheader::runtime_compression(fhmdot::fhm_fast) == "L:1");
  BOOST_CHECK(fhmdot::fheader::runtime_compression(fhmdot::fhm_storage) ==
              "L:9");
}

BOOST_AUTO_TEST_CASE(unittest_file_header_text) {
  std::string header_real = fhmdot::fheader::text(false);
  BOOST_CHECK(header_real.at(0) == 'V');
  BOOST_CHECK(header_real.at(7) == ',');
  BOOST_CHECK(header_real.at(8) == 'P');
  BOOST_CHECK(header_real.at(11) == ',');
  BOOST_CHECK(header_real.at(12) == 'C');
  BOOST_CHECK(header_real.at(15) == ',');
  BOOST_CHECK(header_real.at(16) == 'L');
  BOOST_CHECK(header_real.length() == 19);
}