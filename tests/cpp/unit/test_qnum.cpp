#include <boost/test/unit_test.hpp>
// #include "boost/list.hpp"

#include "fhmdot/include/qnum.hpp"

// using namespace qnum;

BOOST_AUTO_TEST_CASE(unittest_qnum_sh) {
  BOOST_CHECK(quantum_number_crtp<sh_none>::sum(2, 3) == 0);
  BOOST_CHECK(quantum_number_crtp<sh_none>::sum(7, 2) == 0);

  BOOST_CHECK(quantum_number_crtp<sh_uone>::sum(0, 0) == 0);
  BOOST_CHECK(quantum_number_crtp<sh_uone>::sum(1, 7) == 8);
  BOOST_CHECK(quantum_number_crtp<sh_uone>::sum(4, 9) == 13);
}
