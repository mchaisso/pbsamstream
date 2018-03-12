#ifndef _BLASR_MD5_UTILS_IMPL_HPP_
#define _BLASR_MD5_UTILS_IMPL_HPP_
// ROTATE_LEFT rotates x left n bits.

inline unsigned int MD5::rotate_left(uint4 x, uint4 n) { return (x << n) | (x >> (32 - n)); }

// F, G, H and I are basic MD5 functions.

inline unsigned int MD5::F(uint4 x, uint4 y, uint4 z) { return (x & y) | (~x & z); }

inline unsigned int MD5::G(uint4 x, uint4 y, uint4 z) { return (x & z) | (y & ~z); }

inline unsigned int MD5::H(uint4 x, uint4 y, uint4 z) { return x ^ y ^ z; }

inline unsigned int MD5::I(uint4 x, uint4 y, uint4 z) { return y ^ (x | ~z); }

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.

inline void MD5::FF(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{
    a += F(b, c, d) + x + ac;
    a = rotate_left(a, s) + b;
}

inline void MD5::GG(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{
    a += G(b, c, d) + x + ac;
    a = rotate_left(a, s) + b;
}

inline void MD5::HH(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{
    a += H(b, c, d) + x + ac;
    a = rotate_left(a, s) + b;
}

inline void MD5::II(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac)
{
    a += I(b, c, d) + x + ac;
    a = rotate_left(a, s) + b;
}

#endif
