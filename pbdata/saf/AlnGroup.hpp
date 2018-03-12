#ifndef _BLASR_ALN_GROUP_HPP_
#define _BLASR_ALN_GROUP_HPP_

#include <string>
#include <vector>

class AlnGroup
{
public:
    std::vector<unsigned int> id;
    std::vector<std::string> path;
    int FindPath(unsigned int idKey, std::string &val);
};

#endif  // _BLASR_ALN_GROUP_HPP_
