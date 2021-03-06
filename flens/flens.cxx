/*
 *   Copyright (c) 2010, Michael Lehn
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

#ifndef FLENS_FLENS_CXX
#define FLENS_FLENS_CXX 1

#ifdef __INTEL_COMPILER
     static_assert(__INTEL_COMPILER>=1200,
                   "Intel icc Version 12 or higher required!");
#    if __INTEL_COMPILER<1300
#        define STD_HACK
#    endif
#elif __clang__
//#    define STD_HACK
#elif __GNUC__
     static_assert((__GNUG__==4 && __GNUC_MINOR__>=7) || __GNUG__>=5,
                   "GNU GCC Version 4.7 or higher required!");
#    define GCC_HACK
#    define INCLUDE_TYPE_TRAITS
#endif

#if defined(STD_HACK) && !(defined(NO_STD_HACK))
#   include <flens/hacks/std.h>
#endif

#ifdef FLENS_DEBUG_CLOSURES
#   include <flens/debug/auxiliary/auxiliary.h>
#endif

#include <flens/flens.h>
#include <flens/flens.tcc>
#include <cxxblas/cxxblas.cxx>

#ifdef USE_CXXLAPACK
#   include <cxxlapack/cxxlapack.cxx>
#endif


#ifdef FLENS_DEBUG_CLOSURES
#   include <flens/debug/auxiliary/auxiliary.tcc>
#endif

#endif // FLENS_FLENS_CXX
