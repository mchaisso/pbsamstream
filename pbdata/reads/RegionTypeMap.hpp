// Author: Yuan Li

#ifndef _BLASR_REGION_TYPE_MAP_HPP_
#define _BLASR_REGION_TYPE_MAP_HPP_

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../Enumerations.h"
#include "../Types.h"

class RegionTypeMap
{
public:
    /// \name Map region type to/from string and index
    /// \{
    static std::string ToString(RegionType rt);

    static RegionType ToRegionType(const std::string& str);

    /// \params[in] typeStr - query region type as a string
    /// \params[in] typeStrs - a vector region type strings in order
    /// \returns index of a region type as string in a vector of region type strings
    static int ToIndex(const std::string& typeStr, const std::vector<std::string>& typeStrs);

    /// \params[in] rt - query region type
    /// \params[in] typeStrs - a vector region type strings in order
    /// \returns index of the query region type in a vector of region type strings
    static int ToIndex(RegionType rt, const std::vector<std::string>& typeStrs);

    /// \params[in] rt - query region type
    /// \params[in] regionTypes - a vector region type strings in order
    /// \returns index of the query region type in a vector of region type enums
    static int ToIndex(RegionType rt, const std::vector<RegionType>& regionTypes);

private:
    // Map region type to string
    static const std::map<RegionType, std::string> RegionTypeToString;

    // Map string to region type
    static const std::map<std::string, RegionType> StringToRegionType;
    /// \}
};

#endif  // _BLASR_REGION_TYPE_MAP_HPP_
