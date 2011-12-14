//#define CXXBLAS_DEBUG_OUT(x)      std::cerr << x << std::endl;

#define STR(x)      #x
#define STRING(x)   STR(x)

#define FLENS_DEFAULT_INDEXTYPE int

#include <flens/lapack/interface/include/config.h>


namespace flens { namespace lapack {

extern "C" {

//-- dlatrs --------------------------------------------------------------------
void
LAPACK_DECL(dgecon)(const char       *NORM,
                    const INTEGER    *N,
                    const DOUBLE     *A,
                    const INTEGER    *LDA,
                    const DOUBLE     *ANORM,
                    DOUBLE           *RCOND,
                    DOUBLE           *WORK,
                    INTEGER          *IWORK,
                    INTEGER          *INFO)
{
    DEBUG_FLENS_LAPACK("dgecon");
//
//  Test the input parameters so that we pass LAPACK error checks
//
    *INFO = 0;
    if (*NORM!='1' && *NORM!='O' && *NORM!='I') {
        *INFO = -1;
    } else if (*N<0) {
        *INFO = -2;
    } else if (*LDA<std::max(INTEGER(1), *N)) {
        *INFO = -4;
    } else if (*ANORM<0) {
        *INFO = -5;
    }
    if (*INFO!=0) {
        *INFO = -(*INFO);
        LAPACK_ERROR("DGECON", INFO);
        *INFO = -(*INFO);
        return;
    }
//
//  Call FLENS implementation
//
    Norm                norm = getFlensLapackEnum<Norm>(*NORM);
    DConstGeMatrixView  _A    = DConstFSView(*N, *N, A, *LDA);
    DDenseVectorView    work  = DArrayView(*N*4, WORK, 1);
    IDenseVectorView    iwork = IArrayView(*N, IWORK, 1);

    con(norm, _A, *ANORM, *RCOND, work, iwork);
}

} // extern "C"

} } // namespace lapack, flens
