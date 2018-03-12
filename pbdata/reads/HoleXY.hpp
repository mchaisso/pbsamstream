#ifndef _BLASR_HOLE_XY_HPP_
#define _BLASR_HOLE_XY_HPP_

#include <cstdlib>
#ifndef int16_t
#include <cstdint>
#endif

class HoleXY
{
public:
    int16_t xy[2];
    bool operator<(const HoleXY &rhs) const;

    bool operator<(const int16_t xyP[2]) const;
};

#endif  // _BLASR_HOLE_XY_HPP_
