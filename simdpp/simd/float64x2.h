/*  libsimdpp
    Copyright (C) 2011  Povilas Kanapickas tir5c3@yahoo.co.uk
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMD_FLOAT64X2_H
#define LIBSIMDPP_SIMD_FLOAT64X2_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/int64x2.h>
#include <simdpp/simd/cast.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

class basic_int64x2;

/// @ingroup simd_vec_fp
/// @{

/// Class representing float64x2 vector
class float64x2 {
public:

    using element_type = double;
    using uint_element_type = uint64_t;
    using int_vector_type = basic_int64x2;

    static constexpr unsigned length = 2;
    static constexpr unsigned num_bits = 64;
    static constexpr uint_element_type all_bits = 0xffffffffffffffff;

    float64x2() = default;
    float64x2(const float64x2&) = default;
    float64x2& operator=(const float64x2&) = default;

    /// Construct from the underlying vector type
#if SIMDPP_USE_SSE2
    float64x2(__m128d d) : d_(d) {}
#endif

    /// Convert to underlying vector type
#if SIMDPP_USE_SSE2
    operator __m128d() const { return d_; }
#endif

    /// @{
    /// Construct from compatible int64x2 integer vector type
#if SIMDPP_USE_SSE2
    explicit float64x2(basic_int64x2 d) : d_(_mm_castsi128_pd(d)) {}
    float64x2& operator=(basic_int64x2 d) { d_ = _mm_castsi128_pd(d); return *this; }
#elif SIMDPP_USE_NEON
    explicit float64x2(basic_int64x2 d)  : di_(vreinterpretq_u64_u32(d)) {}
    float64x2& operator=(basic_int64x2 d) { di_ = vreinterpretq_u64_u32(d); return *this; }
#elif SIMDPP_USE_NULL
    explicit float64x2(basic_int64x2 d)
    {
        d_[0] = bit_cast<double>(d[0]);
        d_[1] = bit_cast<double>(d[1]);
    }
    float64x2& operator=(basic_int64x2 d) { operator=(float64x2(d)); return *this; }
#endif
    /// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON
    /// For internal use only
    const double& operator[](unsigned i) const { return d_[i]; }
          double& operator[](unsigned i)       { return d_[i]; }
#endif
#endif

    /** Creates a float64x2 vector with the contens set to zero

        @code
        r0 = 0.0
        r1 = 0.0
        @endcode
    */
    static float64x2 zero();

    /** Creates a float64x2 vector from a value loaded from memory.

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
    */
    static float64x2 load_broadcast(const double* v0);

    /** Creates a float64x2 vector from a value stored in a core register.

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
        @icost{SSE2-SSE4.1, 2}
    */
    static float64x2 set_broadcast(double v0);

    /** Creates a float64x2 vector from a value known at compile-time

        @code
            | 0  1  |
        r = [ v0 v0 ]
        @endcode
    */
    static float64x2 make_const(double v0);

    /** Creates a float64x2 vector from two values known at compile-time

        @code
            | 0  1  |
        r = [ v0 v1 ]
        @endcode
    */
    static float64x2 make_const(double v0, double v1);

private:
#if SIMDPP_USE_SSE2
    __m128d d_;
#elif SIMDPP_USE_NEON
    union {
        double d_[2];
        uint64x2_t di_;
    };
#elif SIMDPP_USE_NULL
    double d_[2];
#endif
};

/// @} -- end ingroup

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
