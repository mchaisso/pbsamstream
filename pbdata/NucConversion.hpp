#ifndef _BLASR_NUC_CONVERSION_HPP_
#define _BLASR_NUC_CONVERSION_HPP_

//
// Map from ascii to 2 bit representation.
//
extern int TwoBit[256];

//
// Map from charcter to 3 bit.  Treat all non ACGT IUPAC as N
// IPUAC: ACGT U M R W S Y K V H D N
//
extern int ThreeBit[256];

extern int IsACTG[256];

extern int IsLowerCase[256];

extern int FourBit[256];

extern int FourBitToAscii[10];

extern int ThreeBitToAscii[6];

extern int MaskedFourBit[256];

extern unsigned char AllToUpper[256];

extern char AllToLower[256];

extern unsigned char PreserveCase[256];

extern char TwoBitToAscii[4];

extern unsigned char ReverseComplementNuc[256];

//
// HDF Column Orders: GTAC
// A - column 2; C - column 3;
// G - column 0; T - column 1;
// Ascii code:
// A=65, C=67, G=71,  T=84
// a=97, c=99, g=116, t=103
//
extern int NucToHdfColumnOrder[256];

// Convert a FASTQ character to Quality.
const unsigned int FASTQ_CHAR_TO_QUALITY = 33;

#endif  // _BLASR_NUC_CONVERSION_HPP_
