// Author: Yuan Li

#ifndef _PBDATA_READS_REGION_ANNOTATIONS_HPP_
#define _PBDATA_READS_REGION_ANNOTATIONS_HPP_

#include <algorithm>
#include <string>
#include <vector>
#include "ReadInterval.hpp"
#include "RegionAnnotation.hpp"

class RegionAnnotations
{

    /// \name Region Annotations of a single ZMW
    /// \{
private:
    /// \name region table of a zmw
    std::vector<RegionAnnotation> table_;

    /// \name hole number of a zmw
    UInt holeNumber_;

    /// \name region types in order.
    std::vector<RegionType> types_;

public:
    RegionAnnotations(const UInt holeNumber, const std::vector<RegionAnnotation>& annotations,
                      const std::vector<RegionType>& types);

    RegionAnnotations(const RegionAnnotations& rhs);

    ~RegionAnnotations() {}

    /// \returns zmw holeNumber.
    UInt HoleNumber(void) const;

    /// \returns sorted adapters of this zmw
    std::vector<RegionAnnotation> Adapters() const;

    /// \returns whether or not has HQ region specified in table.
    bool HasHQRegion() const;

    /// \returns exactly one HQ region of this zmw.
    /// \note If no HQ region exists, return a RegionAnnotation of length  0.
    ///       If more than one HQ region is found for this zmw, raise an assertion error.
    RegionAnnotation TheHQRegion() const;

    /// \returns HQ start position of this zmw.
    DNALength HQStart() const;

    /// \returns HQ end position of this zmw.
    DNALength HQEnd() const;

    /// \returns HQ score of this zmw.
    int HQScore() const;

    /// \returns sorted insert regions of this zmw.
    std::vector<RegionAnnotation> Inserts() const;

    /// \returns a vector of all adapters
    std::vector<ReadInterval> AdapterIntervals() const;

    /// \returns a vector of all subreads
    /// \param[in] wholeLength     Length of unrolled sequence of this zmw. Note that
    ///                            this piece of info does not exist in region table.
    /// \param[in] byAdapter       false: return inserts in region table directly.
    ///                            true : infer inserts according to adapters.
    /// \param[in] byHQRegion      false: inserts may contain both HQ and LQ regions
    ///                            true : inserts in HQ regions only.
    std::vector<ReadInterval> SubreadIntervals(const DNALength wholeLength,
                                               const bool byAdapter = true,
                                               const bool byHQRegion = true) const;

private:
    /// \returns sorted vector of region annotations of a RegionType.
    std::vector<RegionAnnotation> RegionAnnotationsOfType(RegionType type) const;

    /// \returns HQ regions of this zmw.
    std::vector<RegionAnnotation> HQRegions() const;

    /// \}
};

#endif
