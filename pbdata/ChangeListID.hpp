#ifndef UTILS_CHANGELIST_ID_H_
#define UTILS_CHANGELIST_ID_H_

#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#ifndef _QVScale_
#define _QVScale_
enum QVScale
{
    POverOneMinusP,  // popularized by Illumina
    PHRED
};
#endif

class ChangeListID
{
public:
    std::string idString;
    std::vector<std::string> strVer;
    std::vector<int> intVer;
    ChangeListID();
    ChangeListID(std::string &idStringP);

    void StoreString(std::string &idStringP);

    int LessThan(ChangeListID &rhs, int depth = 0);

    QVScale DetermineQVScaleFromChangeListID();

    /// Get version string from ChangeListID.
    /// changeListID "2.3.0.144058" --> Version "2.3".
    /// \returns version string
    std::string GetVersion();
};

void AppendPerforceChangelist(std::string perforceVersionString, std::string &version);

#endif
