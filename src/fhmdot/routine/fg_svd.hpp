
#ifndef LAPACK_WRAPPER_HPP
#define LAPACK_WRAPPER_HPP

#include <complex>

#define size_t typename std::size_t
#define snum_t float
#define dnum_t double
#define cnum_t typename std::complex<float>
#define znum_t typename std::complex<double>

extern "C" {
/*
/// --------------------
/// --- BLAS level 3 ---
/// --------------------
/// general matrix multiplication
/// C := a*op( A )*op( B ) + b*C,
void sgemm_(const char *transa, const char *transb, const size_t *m, const
size_t *n, const size_t *k, const snum_t *alpha, const snum_t *a, const size_t
*lda, const snum_t *b, const size_t *ldb, const snum_t *beta, snum_t *c, const
size_t *ldc); void dgemm_(const char *transa, const char *transb, const size_t
*m, const size_t *n, const size_t *k, const dnum_t *alpha, const dnum_t *a,
const size_t *lda, const dnum_t *b, const size_t *ldb, const dnum_t *beta,
dnum_t *c, const size_t *ldc); void cgemm_(const char *transa, const char
*transb, const size_t *m, const size_t *n, const size_t *k, const cnum_t *alpha,
const cnum_t *a, const size_t *lda, const cnum_t *b, const size_t *ldb, const
cnum_t *beta, cnum_t *c, const size_t *ldc); void zgemm_(const char *transa,
const char *transb, const size_t *m, const size_t *n, const size_t *k, const
znum_t *alpha, const znum_t *a, const size_t *lda, const znum_t *b, const size_t
*ldb, const znum_t *beta, znum_t *c, const size_t *ldc);
/// --------------------
/// --- LAPACK level ---
/// --------------------
/// SVD general matrix
void sgesvd_( const char* jobu, const char* jobvt, const size_t *m, const size_t
*n, const snum_t *a, const size_t *lda, snum_t *s, snum_t *u, const size_t *ldu,
snum_t *vt, const size_t *ldvt, snum_t *work, int *lwork, int *info ); void
dgesvd_( const char* jobu, const char* jobvt, const size_t *m, const size_t *n,
const dnum_t *a, const size_t *lda, dnum_t *s, dnum_t *u, const size_t *ldu,
dnum_t *vt, const size_t *ldvt, dnum_t *work, int *lwork, int *info ); void
cgesvd_( const char* jobu, const char* jobvt, const size_t *m, const size_t *n,
const cnum_t *a, const size_t *lda, snum_t *s, cnum_t *u, const size_t *ldu,
cnum_t *vt, const size_t *ldvt, cnum_t *work, int *lwork, snum_t *rwork , int
*info ); void zgesvd_( const char* jobu, const char* jobvt, const size_t *m,
const size_t *n, const znum_t *a, const size_t *lda, dnum_t *s, znum_t *u, const
size_t *ldu, znum_t *vt, const size_t *ldvt, znum_t *work, int *lwork, dnum_t
*rwork , int *info );
/// SVD general matrix D&C
void sgesdd_( const char *jobz, const size_t *m, const size_t *n, snum_t *a,
const size_t *lda, snum_t *s, snum_t *u, const size_t *ldu, snum_t *vt, const
size_t *ldvt, snum_t *work, int *lwork, int *iwork, int *info ); void dgesdd_(
const char *jobz, const size_t *m, const size_t *n, dnum_t *a, const size_t
*lda, dnum_t *s, dnum_t *u, const size_t *ldu, dnum_t *vt, const size_t *ldvt,
dnum_t *work, int *lwork, int *iwork, int *info ); void cgesdd_( const char
*jobz, const size_t *m, const size_t *n, cnum_t *a, const size_t *lda, snum_t
*s, cnum_t *u, const size_t *ldu, cnum_t *vt, const size_t *ldvt, cnum_t *work,
int *lwork, int *iwork, int *info ); void zgesdd_( const char *jobz, const
size_t *m, const size_t *n, znum_t *a, const size_t *lda, dnum_t *s, znum_t *u,
const size_t *ldu, znum_t *vt, const size_t *ldvt, znum_t *work, int *lwork, int
*iwork, int *info );
*/
}

#undef size_t
#undef snum_t
#undef dnum_t
#undef cnum_t
#undef znum_t

template <typename num_t> void svd(num_t *A, num_t *U, double S, num_t *Vd) {
  // dgesdd(A,U,S,Vd,);
}

void MatrixSVD(const dnum_t *A, const size_t &N, const size_t &M, dnum_t *U,
               dnum_t *S, dnum_t *VT) {
  size_t ldA = M, ldu = M, ldvT = M < N ? M : N;
  dnum_t worktest;
  int info, lwork = -1;

  // //!!!TODO!!!
  // dgesdd_((char*)"S", &N, &M, A, &ldA, S, VT, &ldu, U, &ldvT,work, size_t
  // *lwork, size_t *iwork, size_t *info );

  dgesvd_((char *)"S", (char *)"S", &M, &N, A, &ldA, S, VT, &ldu, U, &ldvT,
          &worktest, &lwork, &info);
#ifndef RM_ERROR_HANDLER
  if (info != 0) {
    throw std::runtime_error(
        "Error in Lapack function 'dgesvd': Lapack INFO = " +
        std::to_string(info));
  }
#endif
  lwork = (int)worktest;
  dnum_t work[lwork];

  dgesvd_((char *)"S", (char *)"S", &M, &N, A, &ldA, S, VT, &ldu, U, &ldvT,
          work, &lwork, &info);
#ifndef RM_ERROR_HANDLER
  if (info != 0) {
    throw std::runtime_error(
        "Error in Lapack function 'dgesvd': Lapack INFO = " +
        std::to_string(info));
  }
#endif
  return;
}

#endif