#ifndef _BLASR_SMRT_READ_UTILS_HPP_
#define _BLASR_SMRT_READ_UTILS_HPP_

#include <cstdlib>

#include "../FASTQSequence.hpp"
#include "../StringUtils.hpp"

void GetSMRTReadCoordinates(FASTQSequence &seq, int &x, int &y);

void GetSpringfieldHoleNumberFromTitle(FASTQSequence &seq, unsigned int &holeNumber);

// Parse a PBIRead name of format movie/holeNumber/s_e, or /movie/holeNumber
// and get movieName, holeNumber.
bool ParsePBIReadName(std::string &readName, std::string &movieName, int &holeNumber);

#endif
