#ifndef _BLASR_QUALITY_VALUE_VECTOR_HPP_
#define _BLASR_QUALITY_VALUE_VECTOR_HPP_
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <ostream>
#include "../Types.h"
#include "../utils.hpp"
#include "QualityValue.hpp"

template <typename T_QV>
class QualityValueVector
{
public:
    T_QV *data;
    QVScale qvScale;

    T_QV &operator[](unsigned int pos) const;

    QualityValueVector();

    QualityProbability ToProbability(unsigned int pos);

    T_QV ToPhred(unsigned int pos);

    void Copy(const QualityValueVector<T_QV> &rhs, const DNALength length);

    void Copy(const std::string &rhs);

    void Free();

    void Allocate(unsigned int length);

    /// Fill data with value.
    void Fill(const T_QV &value);

    /// Fill this->data[thisStart...thisStart+fillLength] with
    /// rhs->data[rhsStart...rhsStart+fillLength]
    void Fill(const DNALength thisStart, const DNALength fillLength,
              const QualityValueVector<T_QV> &rhs, const DNALength rhsStart);

    bool Empty() const;

    void ShallowCopy(const QualityValueVector<T_QV> &ref, int pos, const DNALength &length);

    // Reset data pointer to NULL, don't free memory.
    // This should be paired with ShallowCopy.
    void ResetShallowData(void);

    std::string ToString(void);

    // Returns data length
    DNALength Length(void) const;

private:
    DNALength _length;
};

#include "QualityValueVectorImpl.hpp"
#endif  // _BLASR_QUALITY_VALUE_VECTOR_HPP_
