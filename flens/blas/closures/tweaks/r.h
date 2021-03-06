/*
 *   Copyright (c) 2011, Michael Lehn
 *
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2) Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *   3) Neither the name of the FLENS development group nor the names of
 *      its contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FLENS_BLAS_CLOSURES_TWEAKS_R_H
#define FLENS_BLAS_CLOSURES_TWEAKS_R_H 1

#include <cxxblas/cxxblas.h>
#include <flens/blas/closures/tweaks/defaulteval.h>
#include <flens/blas/operators/operators.h>
#include <flens/matrixtypes/matrixtypes.h>
#include <flens/typedefs.h>
#include <flens/vectortypes/vectortypes.h>

namespace flens { namespace blas {

//
//  Matrix closure of form: VX*transpose(VY)
//
template <typename VX, typename VY>
using MatrixClosureRU =

    MatrixClosure<OpMult,
                  VX,
                  VectorClosureOpTrans<VY>
                 >;

//
//  Matrix closure of form: VX*conjTrans(VY)
//
template <typename VX, typename VY>
using MatrixClosureRC =

    MatrixClosure<OpMult,
                  VX,
                  VectorClosureOpConjTrans<VY>
                 >;


//-- GeneralMatrix -------------------------------------------------------------
//
//  A += alpha*x*transpose(y)
//
template <typename ALPHA, typename VX, typename VY, typename MA>
    typename RestrictTo<DefaultEval<MatrixClosureRU<VX, VY> >::value
                     && IsVector<VX>::value
                     && IsVector<VY>::value
                     && IsGeneralMatrix<MA>::value,
             void>::Type
    axpy(Transpose trans, const ALPHA &alpha,
         const MatrixClosureRU<VX, VY> &xyt, MA &A);

//
//  A += alpha*x*conjTrans(y)
//
template <typename ALPHA, typename VX, typename VY, typename MA>
    typename RestrictTo<DefaultEval<MatrixClosureRC<VX, VY> >::value
                     && IsVector<VX>::value
                     && IsVector<VY>::value
                     && IsGeneralMatrix<MA>::value,
             void>::Type
    axpy(Transpose trans, const ALPHA &alpha,
         const MatrixClosureRC<VX, VY> &xyt, MA &A);

//-- SymmetricMatrix -----------------------------------------------------------
//
//  A += alpha*x*transpose(x)
//
template <typename ALPHA, typename VX, typename VY, typename MA>
    typename RestrictTo<DefaultEval<MatrixClosureRU<VX, VY> >::value
                     && IsVector<VX>::value
                     && IsVector<VY>::value
                     && IsSymmetricMatrix<MA>::value,
             void>::Type
    axpy(Transpose trans, const ALPHA &alpha,
         const MatrixClosureRU<VX, VY> &xxt, MA &A);

//-- HermitianMatrix -----------------------------------------------------------
//
//  A += alpha*x*conjTrans(x)
//
template <typename ALPHA, typename VX, typename VY, typename MA>
    typename RestrictTo<DefaultEval<MatrixClosureRC<VX, VY> >::value
                     && IsVector<VX>::value
                     && IsVector<VY>::value
                     && IsHermitianMatrix<MA>::value,
             void>::Type
    axpy(Transpose trans, const ALPHA &alpha,
         const MatrixClosureRC<VX, VY> &xxh, MA &A);

} } // namespace blas, flens

#endif // FLENS_BLAS_CLOSURES_TWEAKS_R_H
