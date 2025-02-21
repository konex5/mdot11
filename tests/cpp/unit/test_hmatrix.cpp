#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>
#include <complex>

#include "fhmdot/include/hmatrix.hpp"
#include "fhmdot/include/qnum.hpp"

using namespace fhmdot::hmatrix;
using namespace fhmdot::qnum;

typedef boost::mpl::list<float, double, typename std::complex<float>,
                         typename std::complex<double>>
    values;
typedef boost::mpl::list<sh_none, sh_u1, sh_su2> Q;

BOOST_AUTO_TEST_CASE_TEMPLATE(unittest_hmatrix, T, values) {
  mps<Q, T> mps_a();
  mps<Q, T> mps_b();
}
