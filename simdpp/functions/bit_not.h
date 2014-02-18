/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
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

#ifndef LIBSIMDPP_SIMDPP_FUNCTIONS_BIT_NOT_H
#define LIBSIMDPP_SIMDPP_FUNCTIONS_BIT_NOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/simd/types.h>

#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    #include <simdpp/null/foreach.h>
    #include <simdpp/null/bitwise.h>
#endif

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Computes bitwise NOT of an integer vector

    @code
    r = ~a
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 2-3}
    @icost{AVX2, NEON, ALTIVEC, 2}
*/
inline basic_int8x16 bit_not(basic_int8x16 a)
{
#if SIMDPP_USE_NULL
    return null::foreach<basic_int8x16>(a, [](uint64_t a){ return ~a; });
#elif SIMDPP_USE_SSE2
    basic_int8x16 ones = basic_int8x16::ones();
    return bit_xor(a, ones);
#elif SIMDPP_USE_NEON
    return vmvnq_u8(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_nor((__vector uint8_t)a, (__vector uint8_t)a);
#endif
}

inline basic_int16x8 bit_not(basic_int16x8 a) { return bit_not(uint8x16(a)); }
inline basic_int32x4 bit_not(basic_int32x4 a) { return bit_not(uint8x16(a)); }
inline basic_int64x2 bit_not(basic_int64x2 a) { return bit_not(uint8x16(a)); }

inline basic_int8x32 bit_not(basic_int8x32 a)
{
#if SIMDPP_USE_AVX2
    basic_int8x32 ones = basic_int8x32::ones();
    return bit_xor(a, ones);
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline basic_int16x16 bit_not(basic_int16x16 a) { return bit_not(uint8x32(a)); }
inline basic_int32x8 bit_not(basic_int32x8 a)   { return bit_not(uint8x32(a)); }
inline basic_int64x4 bit_not(basic_int64x4 a)   { return bit_not(uint8x32(a)); }

// -----------------------------------------------------------------------------

inline mask_int8x16 bit_not(mask_int8x16 a)
{
#if SIMDPP_USE_NULL
    return null::bit_not_mm(a);
#else
    return bit_not(uint8x16(a));
#endif
}

inline mask_int16x8 bit_not(mask_int16x8 a)
{
#if SIMDPP_USE_NULL
    return null::bit_not_mm(a);
#else
    return bit_not(uint16x8(a));
#endif
}

inline mask_int32x4 bit_not(mask_int32x4 a)
{
#if SIMDPP_USE_NULL
    return null::bit_not_mm(a);
#else
    return bit_not(uint32x4(a));
#endif
}

inline mask_int64x2 bit_not(mask_int64x2 a)
{
#if SIMDPP_USE_NULL
    return null::bit_not_mm(a);
#else
    return bit_not(uint64x2(a));
#endif
}

inline mask_int8x32 bit_not(mask_int8x32 a)
{
#if SIMDPP_USE_AVX2
    return bit_not(uint8x32(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline mask_int16x16 bit_not(mask_int16x16 a)
{
#if SIMDPP_USE_AVX2
    return bit_not(uint16x16(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline mask_int32x8 bit_not(mask_int32x8 a)
{
#if SIMDPP_USE_AVX2
    return bit_not(uint32x8(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline mask_int64x4 bit_not(mask_int64x4 a)
{
#if SIMDPP_USE_AVX2
    return bit_not(uint64x4(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}
/// @}

/// @{
/** Computes bitwise NOT of a floating-point vector

    @code
    r = ~a
    @endcode

    @par 128-bit version:
    @icost{SSE2-SSE4.1, 1-2}

    @par 256-bit version:
    @icost{SSE2-SSE4.1, 2-3}
    @icost{AVX2, NEON, ALTIVEC, 2}
*/
inline float32x4 bit_not(float32x4 a)
{
#if SIMDPP_USE_NULL
    return float32x4(bit_not(uint32x4(a)));
#elif SIMDPP_USE_SSE2
    uint32x4 ones = uint32x4::ones();
    return bit_xor(a, ones);
#elif SIMDPP_USE_NEON
    return (float32x4) vmvnq_u32((uint32x4)a);
#elif SIMDPP_USE_ALTIVEC
    return vec_nor((__vector float)a, (__vector float)a);
#endif
}

inline float64x2 bit_not(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return float64x2(bit_not(uint64x2(a)));
#elif SIMDPP_USE_SSE2
    uint64x2 ones = uint64x2::ones();
    return bit_xor(a, ones);
#endif
}

inline float32x8 bit_not(float32x8 a)
{
#if SIMDPP_USE_AVX
    uint32x8 ones = uint32x8::ones();
    return bit_xor(a, ones);
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline float64x4 bit_not(float64x4 a)
{
#if SIMDPP_USE_AVX
    uint64x4 ones = uint64x4::ones();
    return bit_xor(a, ones);
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

// -----------------------------------------------------------------------------

inline mask_float32x4 bit_not(mask_float32x4 a)
{
#if SIMDPP_USE_NULL
    return null::bit_not_mm(a);
#else
    return bit_not(float32x4(a));
#endif
}

inline mask_float64x2 bit_not(mask_float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return null::bit_not_mm(a);
#else
    return bit_not(float64x2(a));
#endif
}

inline mask_float32x8 bit_not(mask_float32x8 a)
{
#if SIMDPP_USE_AVX
    return bit_not(float32x8(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}

inline mask_float64x4 bit_not(mask_float64x4 a)
{
#if SIMDPP_USE_AVX
    return bit_not(float64x4(a));
#else
    return {bit_not(a[0]), bit_not(a[1])};
#endif
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
