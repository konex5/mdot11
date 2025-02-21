#ifndef FG_MULTIPLY
#define FG_MULTIPLY

// #include <oneapi/mkl/lapack.hpp>
#include <vector>
#include "tbb/tbb.h"
// #include "oneapi/mkl.hpp"

void multiply_nondeg(int lmat, int rmat) {
    //oneapi::mkl::lapack::gesvd()
}

void multiply_deg(std::vector<int> lmat, int rmat, bool isLeft) {
    
}


#endif
