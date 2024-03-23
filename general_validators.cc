#include "general_validators.h"

namespace fs = std::experimental::filesystem;

bool isFilePath(std::istringstream& iss) {

    std::string word;
    if (!(iss >> word) || word != "path") return outputError("Error: Expected path");

    std::string path;
    if (!(iss >> path)) return outputError("Error: Invalid path");

    // Check if the file exists
    if (!fs::exists(path)) outputError("Error: File does not exist");

    // Check if the file is accessible
    std::ifstream file(path);
    if (!file.is_open()) outputError("Error: Unable to open file");
    file.close();

    // Success
    return true; 
}

bool isDouble(std::istringstream& iss, const std::string& keyword, const double min, const double max) {
    
    std::string word;
    if (!(iss >> word) || word != keyword) return outputError("Error: Expected " + keyword);

    double value;
    if(!(iss >> value)) return outputError("Error: Invalid " + keyword + " value type");
    if (value < min || max < value) return outputError("Error: value not in range");
}

bool isXYZ(std::istringstream& iss, const std::string& keyword, const double min, const double max) {

    std::string word;
    if (!(iss >> word) || word != keyword) return outputError("Error: Expected " + keyword);

    double x, y, z;
    if (!(iss >> x >> y >> z)) return outputError("Error: Invalid " + keyword + " value type");
    if (x < min || max < x) return outputError("Error: first value not in range");
    if (y < min || max < y) return outputError("Error: second value not in range");
    if (z < min || max < z) return outputError("Error: third value not in range");

    // Success
    return true;
}
