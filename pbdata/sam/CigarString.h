#ifndef _BLASR_SAM_CIGAR_STRING_HPP_
#define _BLASR_SAM_CIGAR_STRING_HPP_

#include <sstream>
#include <string>
#include <vector>

class CigarString : public std::string
{
public:
    void Vectorize(std::vector<int> &lengths, std::vector<char> &operations)
    {
        std::stringstream strm;
        strm.str(*this);
        while (strm) {
            int l;
            char o;
            if ((strm >> l >> o)) {
                lengths.push_back(l);
                operations.push_back(o);
            }
        }
    }
};

#endif
