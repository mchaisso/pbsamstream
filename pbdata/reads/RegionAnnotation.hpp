// Author: Mark Chaisson

#ifndef _BLASR_REGION_ANNOTATION_HPP_
#define _BLASR_REGION_ANNOTATION_HPP_

#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>
#include "../Enumerations.h"
#include "../PacBioDefs.h"
#include "../Types.h"
#include "RegionTypeMap.hpp"

class HDFRegionTableReader;
class HDFRegionTableWriter;
class HDFRegionsWriter;

class RegionAnnotation
{
    friend class HDFRegionTableReader;
    friend class HDFRegionTableWriter;
    friend class HDFRegionsWriter;

public:
    static const int HOLENUMBERCOL = 0;
    static const int REGIONTYPEINDEXCOL = 1;
    static const int REGIONSTARTCOL = 2;
    static const int REGIONENDCOL = 3;
    static const int REGIONSCORECOL = 4;
    static const int NCOLS = 5;

    // Notice the discrepencies between Region and other hdf datasets!!
    // Region annotation is defined as int32_t * 5, while
    // holeNumber is defined as type UInt in other datasets (e.g., majorly ZMW),
    // start and end are defined as type DNALength in other datasets.
    int row[NCOLS];

public:
    // FIXME: use regionType as a member varaible instead of regionTypeIndex
    inline RegionAnnotation(UInt holeNumber = 0, int typeIndex = 0, int start = 0, int end = 0,
                            int score = -1);

    inline bool operator<(const RegionAnnotation &rhs) const;

    inline bool operator<(int holeNumber) const;

    inline RegionAnnotation &operator=(const RegionAnnotation &rhs);

    inline bool operator==(const RegionAnnotation &rhs) const;

    inline int GetHoleNumber(void) const;

    inline RegionAnnotation &SetHoleNumber(int holeNumber);

    inline int GetTypeIndex(void) const;

    inline std::string GetTypeString(const std::vector<RegionType> &types) const;

    inline RegionAnnotation &SetTypeIndex(int typeIndex);

    inline int GetStart(void) const;

    inline RegionAnnotation &SetStart(int start);

    inline int GetEnd(void) const;

    inline RegionAnnotation &SetEnd(int end);

    inline int GetScore(void) const;

    inline RegionAnnotation &SetScore(int score);

public:
    friend std::ostream &operator<<(std::ostream &os, const RegionAnnotation &ra);
};

inline bool compare_region_annotation_by_type(const RegionAnnotation &lhs,
                                              const RegionAnnotation &rhs);

inline RegionAnnotation::RegionAnnotation(UInt holeNumber, int typeIndex, int start, int end,
                                          int score)
{
    SetHoleNumber(static_cast<int>(holeNumber));
    SetTypeIndex(typeIndex);
    SetStart(start);
    SetEnd(end);
    SetScore(score);
}

inline bool RegionAnnotation::operator<(const RegionAnnotation &rhs) const
{
    if (GetHoleNumber() == rhs.GetHoleNumber())
        if (GetStart() == rhs.GetStart()) {
            if (GetEnd() == rhs.GetEnd())
                return GetScore() < rhs.GetScore();
            else
                return GetEnd() > rhs.GetEnd();
        } else {
            return GetStart() < rhs.GetStart();
        }
    else
        return GetHoleNumber() < rhs.GetHoleNumber();
}

inline bool RegionAnnotation::operator<(int holeNumber) const
{
    return GetHoleNumber() < holeNumber;
}

inline RegionAnnotation &RegionAnnotation::operator=(const RegionAnnotation &rhs)
{
    memcpy(row, rhs.row, sizeof(int) * NCOLS);
    return *this;
}

inline bool RegionAnnotation::operator==(const RegionAnnotation &rhs) const
{
    return (GetHoleNumber() == rhs.GetHoleNumber() and GetTypeIndex() == rhs.GetTypeIndex() and
            GetStart() == rhs.GetStart() and GetEnd() == rhs.GetEnd() and
            GetScore() == rhs.GetScore());
}

inline int RegionAnnotation::GetHoleNumber(void) const { return row[HOLENUMBERCOL]; }

inline RegionAnnotation &RegionAnnotation::SetHoleNumber(int holeNumber)
{
    row[HOLENUMBERCOL] = holeNumber;
    return *this;
}

inline int RegionAnnotation::GetTypeIndex(void) const { return row[REGIONTYPEINDEXCOL]; }

inline std::string RegionAnnotation::GetTypeString(const std::vector<RegionType> &typesTable) const
{
    assert(GetTypeIndex() >= 0 and GetTypeIndex() < static_cast<int>(typesTable.size()));
    return RegionTypeMap::ToString(typesTable[GetTypeIndex()]);
}

inline RegionAnnotation &RegionAnnotation::SetTypeIndex(int regionTypeIndex)
{
    row[REGIONTYPEINDEXCOL] = regionTypeIndex;
    return *this;
}

inline int RegionAnnotation::GetStart(void) const { return row[REGIONSTARTCOL]; }

inline RegionAnnotation &RegionAnnotation::SetStart(int start)
{
    row[REGIONSTARTCOL] = start;
    return *this;
}

inline int RegionAnnotation::GetEnd(void) const { return row[REGIONENDCOL]; }

inline RegionAnnotation &RegionAnnotation::SetEnd(int end)
{
    row[REGIONENDCOL] = end;
    return *this;
}

inline int RegionAnnotation::GetScore(void) const { return row[REGIONSCORECOL]; }

inline RegionAnnotation &RegionAnnotation::SetScore(int score)
{
    row[REGIONSCORECOL] = score;
    return *this;
}

inline bool compare_region_annotation_by_type(const RegionAnnotation &lhs,
                                              const RegionAnnotation &rhs)
{
    if (lhs.GetHoleNumber() == rhs.GetHoleNumber()) {
        if (lhs.GetTypeIndex() == rhs.GetTypeIndex()) {
            if (lhs.GetStart() == rhs.GetStart()) {
                if (lhs.GetEnd() == rhs.GetEnd())
                    return lhs.GetScore() < rhs.GetScore();
                else
                    return lhs.GetEnd() > rhs.GetEnd();
            } else
                return lhs.GetStart() < rhs.GetStart();
        } else
            return lhs.GetTypeIndex() < rhs.GetTypeIndex();
    } else {
        return lhs.GetHoleNumber() < rhs.GetHoleNumber();
    }
}

#endif  // _BLASR_REGION_ANNOTATION_HPP_
