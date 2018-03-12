#ifndef DATASTRUCTURES_SAF_HDF_MOVIE_INFO_H_
#define DATASTRUCTURES_SAF_HDF_MOVIE_INFO_H_

#include <string>
#include <vector>

#include "../Types.h"

class MovieInfo
{
public:
    std::vector<std::string> name;
    std::vector<UInt> run;
    std::vector<UInt> experiment;
    std::vector<UInt> id;
    int FindMovie(UInt idKey, std::string &nameVal);
};

#endif
