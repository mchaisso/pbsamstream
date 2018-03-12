#ifndef DATASTRUCTURES_READS_ACQ_PARAMS_H_
#define DATASTRUCTURES_READS_ACQ_PARAMS_H_

#include "../Types.h"
class ScanData;
class HDFScanDataWriter;

class AcqParams
{
    friend class ScanData;
    friend class HDFScanDataWriter;

private:
    float aduGain_;
    float cameraGain_;
    int cameraType_;
    UInt hotStartFrame_;
    UInt laserOnFrame_;

public:
    AcqParams(const float aduGain = 1.0, const float cameraGain = 1.0, const int cameraType = 0,
              const UInt hotStartFrame = 0, const UInt laserOnFrame = 0);
};

#endif
