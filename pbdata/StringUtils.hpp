#ifndef UTILS_STRING_UTILS_H_
#define UTILS_STRING_UTILS_H_

#include <cassert>
#include <sstream>
#include <string>
#include <vector>

#include "MD5Utils.hpp"
#include "Types.h"
#include "reads/ReadType.hpp"

int ExactPatternMatch(std::string orig, std::string pattern);

void MakeMD5(const char *data, unsigned int dataLength, std::string &md5Str, int nChars = 0);

void MakeMD5(std::string &data, std::string &md5Str, int nChars = 0);

int IsWhitespace(char c);

int IsSpace(char c);

size_t ToWords(std::string &orig, std::vector<std::string> &words);

int Splice(const std::string &orig, const std::string &pattern, std::vector<std::string> &tokens);

void ParseSeparatedList(const std::string &csl, std::vector<std::string> &values, char delim = ',');

int AssignUntilFirstSpace(char *orig, int origLength, std::string &result);

template <typename T_Value>
void ParseSeparatedList(const std::string &csl, std::vector<T_Value> &values, char delim, int maxVals)
{
    //Parse up to 'maxVals' lines of lists.
    std::stringstream cslStrm(csl);
    T_Value val;
    std::string valString;
    std::string next;
    int valIndex = 0;
    do {
        if (maxVals == 0 or valIndex < maxVals - 1) {
            std::getline(cslStrm, valString, delim);
        } else {
            // If on last value, get the rest of the line.
            std::getline(cslStrm, valString);
        }
        if (cslStrm and valString.size() > 0) {
            std::stringstream valStrm(valString);
            if (!(valStrm >> val)) {
                std::cout << "Error, value " << valString << " is malformatted." << std::endl;
            } else {
                values.push_back(val);
            }
        }
        valIndex++;
    } while (cslStrm);
}

template <typename T_Value>
void ParseSeparatedList(const std::string &csl, std::vector<T_Value> &values, char delim = ',')
{
    ParseSeparatedList(csl, values, delim, 0);
}

std::string RStrip(std::string &fileName);

/// \returns Read Group Id, given movieName and readType.
std::string MakeReadGroupId(const std::string &movieName, const ReadType::ReadTypeEnum &readType);
#endif
