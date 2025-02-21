#include <boost/test/unit_test.hpp>

#include "fhmdot/include/file_header.hpp"

BOOST_AUTO_TEST_CASE(unittest_file_header_version)
{
  std::string version_header = fhmdot::fheader::version();
  BOOST_CHECK(version_header.at(0) == 'V');
  BOOST_CHECK(version_header.at(1) == ':');
  BOOST_CHECK(version_header.at(3) == '.');
  BOOST_CHECK(version_header.at(5) == '.');
  BOOST_CHECK(version_header.length() == 7);
}

BOOST_AUTO_TEST_CASE(unittest_file_header_float_precision)
{
  std::string precision_header = fhmdot::fheader::precision();
#ifndef FLOAT_PRECISION
  BOOST_CHECK(precision_header == "P:T");
#else
  BOOST_CHECK(precision_header == "P:F");
#endif
  BOOST_CHECK(precision_header.length() == 3);
}

BOOST_AUTO_TEST_CASE(unittest_file_header_runtime)
{
  std::string header_real = fhmdot::fheader::text(false);
  BOOST_CHECK(header_real.at(0) == 'V');
  BOOST_CHECK(header_real.at(8) == 'P');
  BOOST_CHECK(header_real.at(12) == 'C');
  BOOST_CHECK(header_real.length() == 15);

  std::string header_cmpx = fhmdot::fheader::text(true);
  BOOST_CHECK(header_cmpx.at(0) == 'V');
  BOOST_CHECK(header_cmpx.at(8) == 'P');
  BOOST_CHECK(header_cmpx.at(12) == 'C');
  BOOST_CHECK(header_cmpx.length() == 15);

  BOOST_CHECK(header_real.at(13) == ':');
  BOOST_CHECK(header_real.at(14) == 'F');
  BOOST_CHECK(header_cmpx.at(13) == ':');
  BOOST_CHECK(header_cmpx.at(14) == 'T');
}