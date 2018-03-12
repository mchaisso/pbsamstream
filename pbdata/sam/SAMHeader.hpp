#ifndef _BLASR_SAM_HEADER_HPP_
#define _BLASR_SAM_HEADER_HPP_

#include <string>

#include "SAMKeywordValuePair.hpp"

class SAMHeader
{
public:
    std::string formatVersion;
    enum SortingOrder
    {
        unknown,
        sorted,
        queryname,
        coordinate
    };
    SortingOrder sortingOrder;

    void StoreValues(std::vector<SAMKeywordValuePair> &kvPairs, int lineNumber = 0);
};

#endif
