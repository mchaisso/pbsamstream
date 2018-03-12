#ifndef DATASTRUCTURES_SAF_ALN_INFO_H_
#define DATASTRUCTURES_SAF_ALN_INFO_H_

#include <cstdint>
#include <vector>
#include "../Types.h"
#include "../alignment/CmpAlignment.hpp"

class AlnInfo
{
public:
    std::vector<CmpAlignment> alignments;
    UInt nAlignments;
    uint64_t lastRow;
};

#endif
