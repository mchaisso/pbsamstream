#ifndef _BLASR_SEQ_UTILS_HPP_
#define _BLASR_SEQ_UTILS_HPP_

#include "DNASequence.hpp"

template <typename T_Sequence>
int OnlyACTG(T_Sequence &seq);

template <typename T_Sequence>
DNALength CountMasked(T_Sequence &seq);

template <typename T_Sequence>
int CountNotMasked(T_Sequence &seq);

#include "SeqUtilsImpl.hpp"

#endif  // _BLASR_SEQ_UTILS_HPP_
