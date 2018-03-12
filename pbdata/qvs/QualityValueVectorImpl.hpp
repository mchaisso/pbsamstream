#ifndef _BLASR_QUALITY_VALUE_VECTOR_IMPL_HPP_
#define _BLASR_QUALITY_VALUE_VECTOR_IMPL_HPP_
#include "../NucConversion.hpp"

template <typename T_QV>
T_QV &QualityValueVector<T_QV>::operator[](unsigned int pos) const
{
    return data[pos];
}

template <typename T_QV>
QualityValueVector<T_QV>::QualityValueVector()
{
    data = NULL;
    // Default to phred.
    qvScale = PHRED;
    _length = 0;
}

template <typename T_QV>
QualityProbability QualityValueVector<T_QV>::ToProbability(unsigned int pos)
{
    return QualityValueToProbability(data[pos], qvScale);
}

template <typename T_QV>
T_QV QualityValueVector<T_QV>::ToPhred(unsigned int pos)
{
    if (qvScale == PHRED) {
        return data[pos];
    } else {
        return PacBioQVToPhred(data[pos]);
    }
}

template <typename T_QV>
void QualityValueVector<T_QV>::Copy(const QualityValueVector<T_QV> &rhs, const DNALength length)
{
    Free();
    if (rhs.Empty()) {
        return;
    }
    Allocate(length);
    std::memcpy(data, rhs.data, length * sizeof(T_QV));
}

template <typename T_QV>
void QualityValueVector<T_QV>::Copy(const std::string &rhs)
{
    // Char to QualityValue
    Free();
    if (rhs.size() == 0) return;
    Allocate(static_cast<DNALength>(rhs.size()));
    for (size_t i = 0; i < rhs.size(); i++) {
        data[i] = static_cast<T_QV>(rhs[i] - FASTQ_CHAR_TO_QUALITY);
    }
}

template <typename T_QV>
void QualityValueVector<T_QV>::Free()
{
    if (data != NULL) {
        delete[] data;
        data = NULL;
    }
    _length = 0;
}

template <typename T_QV>
void QualityValueVector<T_QV>::Allocate(unsigned int length)
{
    Free();
    data = ProtectedNew<T_QV>(length);
    _length = static_cast<DNALength>(length);
}

template <typename T_QV>
void QualityValueVector<T_QV>::Fill(const T_QV &value)
{
    memset(data, value, sizeof(T_QV) * _length);
}

template <typename T_QV>
void QualityValueVector<T_QV>::Fill(const DNALength thisStart, const DNALength fillLength,
                                    const QualityValueVector<T_QV> &rhs, const DNALength rhsStart)
{
    assert(this->_length >= thisStart + fillLength);
    assert(rhs.Length() >= rhsStart + fillLength);
    memcpy(&this->data[thisStart], &rhs.data[rhsStart], sizeof(T_QV) * fillLength);
}

template <typename T_QV>
bool QualityValueVector<T_QV>::Empty() const
{
    return data == NULL;
}

template <typename T_QV>
void QualityValueVector<T_QV>::ShallowCopy(const QualityValueVector<T_QV> &ref, int pos,
                                           const DNALength &length)
{
    data = &ref.data[pos];
    qvScale = ref.qvScale;
    _length = static_cast<DNALength>(length);
}

template <typename T_QV>
void QualityValueVector<T_QV>::ResetShallowData(void)
{
    data = NULL;
    qvScale = PHRED;
    _length = 0;
}

template <typename T_QV>
std::string QualityValueVector<T_QV>::ToString(void)
{
    if (data == NULL) {
        return "";
    }

    std::string str(static_cast<size_t>(_length), '0');
    for (DNALength i = 0; i < _length; i++) {
        str[i] = static_cast<char>(data[i] + FASTQ_CHAR_TO_QUALITY);
    }
    return str;
}

template <typename T_QV>
DNALength QualityValueVector<T_QV>::Length(void) const
{
    return _length;
}

template class QualityValueVector<QualityValue>;

#endif
