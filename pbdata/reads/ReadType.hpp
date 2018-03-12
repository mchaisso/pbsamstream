#ifndef _BLASR_READ_TYPE_HPP
#define _BLASR_READ_TYPE_HPP

#include <string>

class ReadType
{
public:
    enum ReadTypeEnum
    {
        NoReadType = 0,
        Standard = 1,
        CCS = 2,
        RCCS = 3,
        POLYMERASE = 4,
        HQREGION = 5,
        SUBREAD = 6,
        SCRAP = 7,
        UNKNOWN = 8
    };
    static ReadTypeEnum ParseReadType(std::string &readTypeString);
    static std::string ToString(const ReadType::ReadTypeEnum &readType);
};

//The READTYPE values encountered in secondary analysis will be limited to SUBREAD and CCS.
//POLYMERASE, HQREGION, SCRAP, and UNKNOWN will only be encountered in intermediate steps before
//secondary analysis.
//NoReadType, Standard and RCCS were used in CMP.H5 deprecated.
#endif
