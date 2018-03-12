#ifndef _BLASR_REVERSE_COMPRESS_INDEX_HPP_
#define _BLASR_REVERSE_COMPRESS_INDEX_HPP_

#include <fstream>

class ReverseCompressIndex
{
public:
    int *index;
    int indexLength;
    int binSize;
    int maxRun;
    int size() { return indexLength; }

    ReverseCompressIndex();
    ~ReverseCompressIndex();

    void Write(std::ofstream &out);

    void Read(std::ifstream &in);

    void ShallowCopy(ReverseCompressIndex &rhs);

    void Free();
};

#endif  // _BLASR_REVERSE_COMPRESS_INDEX_HPP_
