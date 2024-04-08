#ifndef GEN_VALIDATOR
#define GEN_VALIDATOR

#include "helpers.h"
#include <experimental/filesystem>

bool isFilePath(std::stringstream& _ss);

bool isDouble(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max);

bool isXYZ(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max);

bool isRatio(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max);

// WIP need to consider abstraction when there is special cases (i.e. texture cannot have "no" as an id)
// bool isMember(std::stringstream& _ss, const std::string& _keyword, std::vector<std::string>& _members);

#endif
