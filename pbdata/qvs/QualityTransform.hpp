#ifndef _BLASR_QVS_QUALITY_TRANSFORM_HPP_
#define _BLASR_QVS_QUALITY_TRANSFORM_HPP_

#include <cmath>
#include "QualityValue.hpp"

/*
 * Base lookup table class for quality values.
 */
class QualityToProb
{
public:
    float prob[MAX_QUALITY_VALUE - MIN_QUALITY_VALUE + 1];
    float operator()(int index);
};

/*
 * Create a lookup table for transforming from quality value
 * to p-value using Patrick Marks' low-end expand qv = -100*log10(p/(1-p))
 */
class LowEndExpandQualityTransform
{
public:
    void operator()(QualityToProb &qt);
};

#endif  // _BLASR_QVS_QUALITY_TRANSFORM_HPP_
