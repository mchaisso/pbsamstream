// Author: Mark Chaisson

#ifndef DATASTRUCTURES_READS_PULSE_BASE_COMMON_H_
#define DATASTRUCTURES_READS_PULSE_BASE_COMMON_H_

//
// This includes values that both pulse and base files must have.
//
#include <cstdint>
#include "ScanData.hpp"

class PulseBaseCommon
{
public:
    ScanData scanData;
    std::vector<uint32_t> holeNumbers;

    float GetFrameRate();

    unsigned int GetNumFrames();

    std::string GetMovieName();

    std::map<char, size_t> GetBaseMap();

    bool LookupReadIndexByHoleNumber(uint32_t holeNumber, int &readIndex);
};

#endif
