#ifndef _BLASR_BIT_UTILS_HPP_
#define _BLASR_BIT_UTILS_HPP_

#include <cstdint>
#include <bitset>
#include "../Types.h"

int32_t CountBits(uint32_t v);

int GetSetBitPosition64(uint64_t v);

unsigned int GetSetBitPosition32(UInt v);

#endif  // _BLASR_BIT_UTILS_HPP_
