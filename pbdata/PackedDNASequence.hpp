#ifndef _BLASR_PACKED_DNA_SEQUENCE_HPP_
#define _BLASR_PACKED_DNA_SEQUENCE_HPP_

#include <fstream>
#include "DNASequence.hpp"
#include "NucConversion.hpp"
#include "utils/BitUtils.hpp"

/*
 * Implement a structure to maintain DNA as 3 bits per nucleotide.
 * The extra bit is required for N's in the sequence.  A key is that
 * this structure is read-only through the operator[].  It may be set
 * with the PackedDNASequence::Set(pos,value) command.
 */

typedef unsigned int PackedDNAWord;

class PackedDNASequence
{
public:
    static const PackedDNAWord Mask2All = 613566756;  //100100100...
    static const PackedDNAWord Mask1All = 306783378;  //010010010...
    static const PackedDNAWord Mask0All = 153391689;  //001001001...
    static const PackedDNAWord xorMask[];
    static const PackedDNAWord NucPosMask[];
    static const PackedDNAWord NegMask[];
    static const PackedDNAWord MaskRL[];
    static const PackedDNAWord MaskLR[];
    static const PackedDNAWord NucMask = 7;
    static const DNALength NucsPerWord = 10;
    PackedDNAWord *seq;
    int nCountInWord;
    int nCountNuc;
    DNALength length;
    DNALength arrayLength;

    Nucleotide Get(DNALength pos);

    Nucleotide operator[](DNALength pos);

    PackedDNASequence();
    ~PackedDNASequence();

    void Allocate(DNALength numberOfNucleotides);

    void CreateFromDNASequence(DNASequence &dnaSeq);

    void Set(DNALength pos, Nucleotide threeBitValue);

    DNALength CountInWord(PackedDNAWord word, PackedDNAWord wordMask, Nucleotide nuc);

    DNALength CountNuc(DNALength start, DNALength end, Nucleotide nuc);

    void Write(std::ostream &out);

    void Read(std::istream &in);

    void PrintUnpacked(std::ostream &out, int lineLength = 50);
};

#endif  // _BLASR_PACKED_DNA_SEQUENCE_HPP_
