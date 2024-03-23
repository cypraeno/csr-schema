#ifndef GEN_VALIDATOR
#define GEN_VALIDATOR

#include "helpers.h"
#include <experimental/filesystem>

bool isFilePath(std::istringstream& iss);

bool isDouble(std::istringstream& iss, const std::string& keyword, const double min, const double max);

bool isXYZ(std::istringstream& iss, const std::string& keyword, const double min, const double max);

#endif
