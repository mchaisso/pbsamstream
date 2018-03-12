#ifndef _BLASR_REF_INFO_HPP_
#define _BLASR_REF_INFO_HPP_

#include <cstdint>
#include <string>
#include <vector>

class OneRefInfo
{
public:
    std::string fullName;
    unsigned int id;
    unsigned int length;
    std::string md5;
    OneRefInfo();
};

class RefInfo
{
public:
    std::vector<std::string> fullName;
    std::vector<uint32_t> id;
    std::vector<uint32_t> length;
    std::vector<std::string> md5;
    bool RefIdToIndex(uint32_t qid, int &index);
};
#endif
