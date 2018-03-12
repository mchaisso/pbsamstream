#ifndef _BLASR_SAM_KVPAIR_HPP_
#define _BLASR_SAM_KVPAIR_HPP_

#include <cstdlib>

#include <iostream>
#include <string>
#include <vector>

#include "../StringUtils.hpp"

class SAMKeywordValuePair
{
public:
    std::string key;
    std::string value;
};

bool SplitSAMKeyValuePair(std::string &kvPair, std::string &key, std::string &value);

bool SplitSAMTypedKeyValuePair(std::string kvPair, std::string &key, std::string &kvType,
                               std::string &value);

template <typename T>
void StoreValue(std::string &valueStr, T &value);

void KeywordValueStringsToPairs(std::vector<std::string> &kvStrings,
                                std::vector<SAMKeywordValuePair> &kvPairs);

class TypedKeywordValuePair
{
public:
    static bool Separate(std::string &kvPair, std::string &kvKey, std::string &kvType,
                         std::string &kvValue);
};

template <typename T_Value>
class KeywordValuePair
{
public:
    static bool Parse(std::string &kvPair, const char *key, T_Value &result);

    static bool Store(std::string &valueStr, T_Value &value);
};

#include "SAMKeywordValuePairImpl.hpp"

#endif
