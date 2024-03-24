#ifndef GEN_VALIDATOR
#define GEN_VALIDATOR

#include "helpers.h"
#include <experimental/filesystem>

bool isFilePath(std::istringstream& _iss);

bool isDouble(std::istringstream& _iss, const std::string& _keyword, const double _min, const double _max);

bool isXYZ(std::istringstream& _iss, const std::string& _keyword, const double _min, const double _max);

// WIP need to consider abstraction when there is special cases (i.e. texture cannot have "no" as an id)
// bool isMember(std::istringstream& _iss, const std::string& _keyword, std::vector<std::string>& _members);

#endif
