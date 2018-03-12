// Author: Mark Chaisson

#ifndef DATASTRUCTURES_READS_SCAN_DATA_H_
#define DATASTRUCTURES_READS_SCAN_DATA_H_

#include <map>
#include <string>
#include "../Enumerations.h"
#include "../PacBioDefs.h"
#include "AcqParams.hpp"

class HDFScanDataReader;
class HDFScanDataWriter;

class ScanData
{
    friend class HDFScanDataReader;
    friend class HDFScanDataWriter;

public:
    // Convert base map from a std::map<char, size_t> to a std::string.
    // e.g., {{'A', 2}, {'C', 1}, {'T', 0}, {'G', 3}} --> TCAG
    static std::string BaseMapToStr(const std::map<char, size_t>& baseMap);

    // Convert base map from a std::string to a std::map<char, size_t>.
    // e.g., TCAG --> {{'A', 2}, {'C', 1}, {'T', 0}, {'G', 3}}
    static std::map<char, size_t> StrToBaseMap(const std::string& baseMapStr);

    // A baseMap must contain maps from bases (e.g., ACGT) to indices (e.g., 0, 1, 2, 3).
    static bool IsValidBaseMap(const std::map<char, size_t>& baseMap);

public:
    PlatformId platformId;
    float frameRate;
    unsigned int numFrames;
    std::string movieName, runCode;
    std::string whenStarted;
    std::map<char, size_t> baseMap;

    ScanData(const AcqParams& acqParams = AcqParams());
    std::string GetMovieName();

    ScanData& PlatformID(const PlatformId& id);
    ScanData& FrameRate(const float& rate);
    ScanData& NumFrames(const unsigned int& num);
    ScanData& MovieName(const std::string& name);
    ScanData& RunCode(const std::string& code);
    ScanData& WhenStarted(const std::string& when);
    ScanData& BaseMap(const std::map<char, size_t>& bmp);
    ScanData& BaseMap(const std::string& baseMapStr);
    ScanData& SequencingKit(const std::string sequencingKit);
    ScanData& BindingKit(const std::string bindingKit);
    ScanData& SetAcqParams(const AcqParams& acqParams);

    PlatformId PlatformID(void) const;
    float FrameRate(void) const;
    unsigned int NumFrames(void) const;
    std::string MovieName(void) const;
    std::string RunCode(void) const;
    std::string WhenStarted(void) const;
    std::map<char, size_t> BaseMap(void) const;
    std::string BaseMapStr(void) const;
    std::string SequencingKit(void) const;
    std::string BindingKit(void) const;
    AcqParams GetAcqParams(void) const;

private:
    std::string sequencingKit_;
    std::string bindingKit_;
    AcqParams acqParams_;
};

#endif
