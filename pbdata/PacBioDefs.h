// Author: Yuan Li

#ifndef _PBDATA_PACBIO_DEFS_H_
#define _PBDATA_PACBIO_DEFS_H_
#include <string>
#include <vector>

namespace PacBio {
namespace GroupNames {
///PulseData
static const std::string pulsedata = "PulseData";

///PulseData/BaseCalls
static const std::string basecalls = "BaseCalls";
///PulseData/Regions
static const std::string regions = "Regions";

///PulseData/BaseCalls/BaseCall
static const std::string basecall = "Basecall";

static const std::string qualityvalue = "QualityValue";
static const std::string deletionqv = "DeletionQV";
static const std::string deletiontag = "DeletionTag";
static const std::string insertionqv = "InsertionQV";
static const std::string mergeqv = "MergeQV";
static const std::string substitutionqv = "SubstitutionQV";
static const std::string substitutiontag = "SubstitutionTag";
static const std::string prebaseframes = "PreBaseFrames";
static const std::string widthinframes = "WidthInFrames";
static const std::string pulseindex = "PulseIndex";

///PulseData/BaseCalls/ZMW
static const std::string zmw = "ZMW";
static const std::string zmwmetrics = "ZMWMetrics";

///PulseData/BaseCalls/ZMW/HoleNumber
static const std::string holenumber = "HoleNumber";
static const std::string holestatus = "HoleStatus";
static const std::string holexy = "HoleXY";
static const std::string numevent = "NumEvent";
static const std::string baselinesigma = "BaselineSigma";
static const std::string baselinelevel = "BaselineLevel";
static const std::string signallevel = "SignalLevel";
static const std::string signalsigma = "SignalSigma";

///PulseData/BaseCalls/ZMWMetrics/HQRegionSNR
static const std::string hqregionsnr = "HQRegionSNR";
static const std::string readscore = "ReadScore";
static const std::string productivity = "Productivity";

///PulseData/PulseCalls/*
static const std::string pulsecalls = "PulseCalls";

static const std::string channel = "Channel";
static const std::string ispulse = "IsPulse";
static const std::string labelqv = "LabelQV";
static const std::string meansignal = "MeanSignal";
static const std::string midsignal = "MidSignal";
static const std::string maxsignal = "MaxSignal";
static const std::string startframe = "StartFrame";
static const std::string altlabel = "AltLabel";
static const std::string altlabelqv = "AltLabelQV";
static const std::string chi2 = "Chi2";
static const std::string midstddev = "MidStdDev";

}  // namespace Group

namespace AttributeNames {
namespace Common {
static const std::string changelistid = "ChangeListID";
static const std::string description = "Description";
static const std::string content = "Content";
static const std::string contentstored = "ContentStored";
static const std::string datacreated = "DataCreated";
static const std::string schemarevision = "SchemaRevision";
}  // Common

namespace ZMW {
namespace HoleStatus {
static const std::string lookuptable = "LookupTable";
}
}

namespace Regions {
static const std::string columnnames = "ColumnNames";
static const std::string regiontypes = "RegionTypes";
static const std::string regiondescriptions = "RegionDescriptions";
static const std::string regionsources = "RegionSources";
}  // Regions

namespace ScanData {
namespace DyeSet {
static const std::string basemap = "BaseMap";
}
}  // ScanData

}  // namespace AttributeNames

namespace AttributeValues {
namespace Common {
static const std::string schemarevision = "1.1";
}

namespace ZMW {
namespace HoleNumber {
static const std::string description = "Hole number on chip array";
}  //namespace HoleNumber

namespace HoleStatus {
static const std::string description = "Type of data coming from ZMW";
static const std::vector<std::string> lookuptable = {"SEQUENCING", "ANTIHOLE",    "FIDUCIAL",
                                                     "SUSPECT",    "ANTIMIRROR",  "FDZMW",
                                                     "FBZMW",      "ANTIBEAMLET", "OUTSIDEFOV"};

static const unsigned char sequencingzmw = 0;  // not '0'
static const unsigned char outsidefov = 8;     // not '8'
}  // namespace HoleStatus

namespace HoleXY {
static const std::string description = "Coordinates of ZMW on Chip";
}  // namespace HoleXY

namespace BaseLineSigma {
static const std::string description = "Estimated baseline sigma (std dev) over trace";
}  // namespace BaseLineSigma

}  // namespace ZMW

namespace Regions {
static const std::vector<std::string> columnnames = {"HoleNumber", "Region type index",
                                                     "Region start in bases", "Region end in bases",
                                                     "Region score"};
static const std::vector<std::string> regiontypes = {"Adapter", "Insert", "HQRegion"};
static const std::vector<std::string> regiondescriptions = {"Adapter Hit", "Insert Region",
                                                            "High Quality bases region. Score is "
                                                            "1000 * predicted accuracy, where "
                                                            "predicted accuary is 0 to 1.0"};
static const std::vector<std::string> regionsources = {"AdapterFinding", "AdapterFinding",
                                                       "PulseToBase Region classifer"};
}

namespace ZMWMetrics {
namespace HQRegionSNR {
static const std::string description = "HQRegion average signal to noise ratio";
}
namespace ReadScore {
static const std::string description = "Read raw accuracy prediction";
}
namespace Productivity {
static const std::string description = "ZMW productivity classification";
}
}  // ZMWMetrics

namespace ScanData {
namespace DyeSet {
static const std::string basemap = "TGCA";  // default, order matters!
}
}  // ScanData

}  // namespace AttributeValues

}  // namespace PacBio

#endif
