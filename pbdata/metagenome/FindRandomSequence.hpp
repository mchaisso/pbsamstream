#ifndef _FIND_RANDOM_SEQUENCE_HPP_
#define _FIND_RANDOM_SEQUENCE_HPP_

#include <vector>
#include "../DNASequence.hpp"
#include "statistics/StatUtils.hpp"  // Where does this come from? Does this compile anymore?

template <typename T_Sequence>
void FindRandomPos(std::vector<T_Sequence> &sequences, DNALength &seqIndex, DNALength &seqPos,
                   DNALength seqLength = 0)
{
    std::vector<UInt> cumulativeLengths;
    cumulativeLengths.resize(sequences.size());
    if (sequences.size() == 0) {
        return;
    }
    DNALength cumulativeLength;
    cumulativeLengths[0] = sequences[0].length;
    cumulativeLength = cumulativeLengths[0];
    for (unsigned i = 1; i < sequences.size(); i++) {
        cumulativeLengths[i] = cumulativeLength = cumulativeLengths[i - 1] + sequences[i].length;
    }
    bool validPosFound = false;
    int iter = 0;
    int max_iter = 100000;
    while (validPosFound == false and iter < max_iter) {
        ++iter;
        if (seqLength > cumulativeLength) {
            validPosFound = false;
            iter = max_iter;
            break;
        }
        DNALength pos = RandomUnsignedInt(cumulativeLength - seqLength);
        // Make sure this sequence fits
        for (seqIndex = 0; seqIndex < sequences.size(); seqIndex++) {
            if (cumulativeLengths[seqIndex] > pos) break;
        }
        if (cumulativeLengths[seqIndex] - pos < seqLength) {
            continue;
        }
        UInt pi;
        if (seqIndex == 0) {
            seqPos = pos;
        } else {
            seqPos = pos - cumulativeLengths[seqIndex - 1];
        }
        bool seqContainsN = false;
        for (pi = seqPos; pi < seqPos + seqLength; pi++) {
            if (toupper(sequences[seqIndex].seq[pi]) == 'N') {
                seqContainsN = true;
                break;
            }
        }
        if (seqContainsN) {
            continue;
        } else {
            validPosFound = true;
        }
    }
    if (iter == max_iter) {
        std::cout << "ERROR! Unable to generate a random seq/pos pair!, maybe length " << seqLength
             << std::endl
             << " is too high, or there are too many N's in the references." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

#endif
