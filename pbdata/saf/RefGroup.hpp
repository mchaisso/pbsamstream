#ifndef _BLASR_REF_GROUP_HPP_
#define _BLASR_REF_GROUP_HPP_

#include <string>
#include <vector>
#include <cstdint>

class RefGroup
{
public:
    std::vector<uint32_t> id;
    std::vector<std::string> path;
    std::vector<std::string> refGroupName;
    std::vector<uint32_t> refInfoId;

    bool IdToIndex(uint32_t idKey, uint32_t &idIndex);
    int FindPath(uint32_t idKey, std::string &pathVal, std::string &groupNameVal);
};

#endif
