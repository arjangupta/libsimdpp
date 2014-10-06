/*  Copyright (C) 2013-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_TYPES_FLOAT64X8_H
#define LIBSIMDPP_SIMDPP_TYPES_FLOAT64X8_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/setup_arch.h>
#include <simdpp/types/fwd.h>
#include <simdpp/types/any.h>
#include <simdpp/types/int64x8.h>
#include <simdpp/core/cast.h>
#include <simdpp/detail/construct_eval.h>

namespace simdpp {
#ifndef SIMDPP_DOXYGEN
namespace SIMDPP_ARCH_NAMESPACE {
#endif

#if SIMDPP_USE_AVX512 || SIMDPP_DOXYGEN

/// @ingroup simd_vec_fp
/// @{

/// Class representing float64x8 vector
template<>
class float64<8, void> : public any_float64<8, float64<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_FLOAT;
    using element_type = double;
    using base_vector_type = float64<8,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX512
    using native_type = __m512d;
#endif

    float64<8>() = default;
    float64<8>(const float64<8> &) = default;
    float64<8> &operator=(const float64<8> &) = default;

    template<class E> SIMDPP_INL float64<8>(const float64<8,E>& d) { *this = d.eval(); }
    template<class V> SIMDPP_INL explicit float64<8>(const any_vec<64,V>& d)
    {
        *this = bit_cast<float64<8>>(d.wrapped().eval());
    }
    template<class V> SIMDPP_INL float64<8>& operator=(const any_vec<64,V>& d)
    {
        *this = bit_cast<float64<8>>(d.wrapped().eval()); return *this;
    }

    /// @{
    /// Construct from the underlying vector type
    float64<8>(const native_type& d) : d_(d) {}
    float64<8>& operator=(const native_type& d) { d_ = d; return *this; }
    /// @}

    /// Convert to the underlying vector type
    operator native_type() const { return d_; }

#ifndef SIMDPP_DOXYGEN
    template<class E> SIMDPP_INL float64<8>(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr());
    }
    template<class E> SIMDPP_INL float64<8>& operator=(const expr_vec_construct<E>& e)
    {
        detail::construct_eval_wrapper(*this, e.expr()); return *this;
    }
#endif

    /// @{
    /// Access base vectors
    const float64<8>& vec(unsigned) const { return *this; }
          float64<8>& vec(unsigned)       { return *this; }
    /// @}

    float64<8> eval() const { return *this; }

    /** Creates a float64x2 vector with the contens set to zero

        @code
        r0 = 0.0
        r1 = 0.0
        @endcode
    */
    static float64<8> zero() { return detail::make_zero(); }

private:
    native_type d_;
};


/// Class representing possibly optimized mask data for 8x 64-bit floating point
/// vector
template<>
class mask_float64<8, void> : public any_float64<8, mask_float64<8,void>> {
public:
    static const unsigned type_tag = SIMDPP_TAG_MASK_FLOAT;
    using base_vector_type = mask_float64<8,void>;
    using expr_type = void;

#if SIMDPP_USE_AVX512
    using native_type = __mmask8;
#endif

    mask_float64<8>() = default;
    mask_float64<8>(const mask_float64<8> &) = default;
    mask_float64<8> &operator=(const mask_float64<8> &) = default;

    mask_float64<8>(const native_type& d) : d_(d) {}

    template<class E> SIMDPP_INL explicit mask_float64<8>(const mask_int64<8,E>& d)
    {
        *this = bit_cast<mask_float64<8>>(d.eval());
    }
    template<class E> SIMDPP_INL mask_float64<8>& operator=(const mask_int64<8,E>& d)
    {
        *this = bit_cast<mask_float64<8>>(d.eval()); return *this;
    }

    operator native_type() const { return d_; }

    /// Access the underlying type
    float64<8> unmask() const
    {
    #if SIMDPP_USE_AVX512
        // FIXME: remove cross-domain access
        __m512i bits = _mm512_maskz_set1_epi64(d_, 0xffffffffffffffff);
        // return _mm512_castsi512_pd(bits); GCC BUG
        return (__m512d) bits;
    #endif
    }

    const mask_float64<8>& vec(unsigned) const { return *this; }
          mask_float64<8>& vec(unsigned)       { return *this; }

    mask_float64<8> eval() const { return *this; }

private:
    native_type d_;
};
/// @} -- end ingroup

#endif // SIMDPP_USE_AVX512 || SIMDPP_DOXYGEN

#ifndef SIMDPP_DOXYGEN
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif