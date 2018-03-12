#ifndef _BLASR_QUALITY_VALUE_HPP_
#define _BLASR_QUALITY_VALUE_HPP_

#include <cstdint>
#include "../ChangeListID.hpp"

typedef unsigned char QualityValue;
typedef float QualityProbability;

#define MIN_QUALITY_VALUE 0
#define MAX_QUALITY_VALUE 255

#ifndef _QVScale_
#define _QVScale_
enum QVScale
{
    POverOneMinusP,  // popularized by Illumina
    PHRED
};
#endif

QualityValue ProbabilityToQualityValue(QualityProbability pErr, QVScale qvScale = POverOneMinusP);

QualityValue PacBioQVToPhred(QualityValue pbQV);

QualityValue ToPhred(QualityValue qv, QVScale qvScale = POverOneMinusP);

QualityProbability QualityValueToProbability(QualityValue qv, QVScale qvScale = POverOneMinusP);

QVScale DetermineQVScaleFromChangeListID(ChangeListID &cl);

#endif  // _BLASR_QUALITY_VALUE_HPP_
