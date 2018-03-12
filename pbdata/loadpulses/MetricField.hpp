#ifndef _LOADPULSES_METRICFIELD_HPP_
#define _LOADPULSES_METRICFIELD_HPP_

#include <iostream>
#include <string>
#include <vector>

#include <cstdlib>

#include "../Types.h"

enum FieldType
{
    BasField,
    PlsField
};

class Field
{
public:
    std::string name;
    FieldType type;
    Field(std::string n, FieldType t);
    bool operator==(const Field &another) const;
};

class FieldsRequirement
{
public:
    std::string metric;
    std::vector<Field> fieldsUseBasFile;
    std::vector<Field> fieldsUsePlsFile;

    // Return fields that are required for computing this metric.
    // Eighteen metrics are supported in total.
    // [1/18] metric requires only an attribute (not a field):
    //     WhenStarted
    //
    // [9/18] metrics require exactly one BaseCall field
    //     QualityValue InsertionQV     MergeQV           DeletionQV
    //     DeletionTag  SubstitutionTag SubstitutionQV    PreBaseFrames
    //     PulseIndex
    //
    // [4/18] metrics require more than one field and can be computed using
    // only one method:
    //                         BaseCall         PulseCall
    //     ----------------------------------------------------
    //     ClassifierQV        PulseIndex       NumEvent
    //                                          ClassifierQV
    //     ----------------------------------------------------
    //     pkmid               PulseIndex       NumEvent
    //                                          MidSignal
    //     ----------------------------------------------------
    //     Light               PulseIndex       NumEvent
    //                                          WidthInFrames
    //                                          MeanSignal
    //     ----------------------------------------------------
    //     StartTimeOffset     PulseIndex       NumEvent
    //                                          StartFrame
    //     ----------------------------------------------------
    // [4/18] metrics can be computed from both BaseCalls and PulseCalls.
    // But sometimes the value computed from BaseCalls can be wrong,
    // because the value of BaseCalls/PreBaseFrames may exceed 2^16-1.
    //                Method   BaseCall         PulseCall
    //     ----------------------------------------------------
    //     PulseWidth  (1)     WidthInFrames
    //                  =======================================
    //                 (2)     PulseIndex       NumEvent
    //                                          WidthInFrames
    //     ----------------------------------------------------
    //     WidthInFrames  : The same as PulseWidth
    //     ----------------------------------------------------
    //     StartFrame  (1)     PreBaseFrames
    //                         WidthInFrames
    //                  =======================================
    //                 (2)     PulseIndex       NumEvent
    //                                          StartFrame
    //     ----------------------------------------------------
    //     IPD         (1)     PreBaseFrames
    //                  =======================================
    //                 (2)     PulseIndex       NumEvent
    //                                          StartFrame
    //                                          WidthInFrames
    //     ----------------------------------------------------
    // Note: PulseWidth and WidthInFrames have the same meaning and are
    // computed in the same way.
    //
    // Note: StartFrame can be loaded for both bas.h5 and pls.h5 files
    //       for bas.h5, StartFrame is computed from PreBaseFrames and WidthInFrames
    //           Let x = PreBaseFrames for bases 0 ... n-1, where x[0] is 0 and
    //                   x[i] is the inter-pulse distance between start of pulse
    //                   for base i and end of pulse for base i-1
    //           Let y = WidthInFrames for bases 0 ... n-1, where y[i] is the
    //                   number of pulses within base i
    //       Then,
    //           StartFrame[0] = x[0]
    //           StartFrame[i] = sum(x[0] ... x[i]) + sum(y[0] ... y[i-1])
    //                           for i in [1 ... n-1]
    //       for pls.h5, StartFrame can be directly read from dataset
    //       /PulseData/PulseCalls/StartFrame
    //
    // Note: StartTimeOffset is the StartFrame for the very first base of a read, it
    //       can only be computed from PulseCalls
    //
    // Note: IPD has the same meaning as PreBaseFrames:
    //           = the inter-pulse distance between this base and end of last base,
    //           = the number of Frames between the ending pulse of the last base and
    //           the starting pulse of this base.
    //       However, PreBaseFrames can only be read directly from BaseCalls, while
    //       IPD can also be computed from PulseCalls
    //           If use BaseCalls,
    //               IPD[i] = PreBaseFrames[i]        for i in [0 ... n-1]
    //           If use PulseCalls,
    //               IPD[0] = 0
    //               IPD[i] = StartFrame[i] - StartFrame[i-1] - WidthInFrames[i-1]
    //                                                for i in [1 ... n-1]
    //
    //void GetRequiredFieldsForMetric(const std::string & metric, FieldType & field){
    FieldsRequirement(const std::string &m);
};

#endif
