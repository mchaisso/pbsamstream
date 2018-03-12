#ifndef _BLASR_GFF_FILE_HPP_
#define _BLASR_GFF_FILE_HPP_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Types.h"
#include "utils.hpp"

class GFFEntry
{
public:
    std::string name, type, source;
    UInt start, end;
    char strand;
    float score;
    std::string frame;
    std::string attributes;
    GFFEntry(std::string& _name, std::string& _source, std::string& _type, UInt& _start, UInt& _end,
             float& _score, char& _strand, std::string& _frame, std::string _attributes);
};

class GFFFile
{
public:
    std::vector<GFFEntry> entries;
    void ReadAll(std::string& gffFileName);
};

#endif
