#include "general_validators.h"

namespace fs = std::experimental::filesystem;

bool isFilePath(std::istringstream& _iss) {

    std::string word;
    if (!(_iss >> word) || word != "path") return outputError("Error: Expected path");

    std::string path;
    if (!(_iss >> path)) return outputError("Error: Invalid path");

    // Check if the file exists
    if (!fs::exists(path)) outputError("Error: File does not exist");

    // Check if the file is accessible
    std::ifstream file(path);
    if (!file.is_open()) outputError("Error: Unable to open file");
    file.close();

    // Success
    return true; 
}

bool isDouble(std::istringstream& _iss, const std::string& _keyword, const double _min, const double _max) {
    
    std::string word;
    if (!(_iss >> word) || word != _keyword) return outputError("Error: Expected " + _keyword);

    double value;
    if(!(_iss >> value)) return outputError("Error: Invalid " + _keyword + " value type");
    if (value < _min || _max < value) return outputError("Error: value not in range");
}

bool isXYZ(std::istringstream& _iss, const std::string& _keyword, const double _min, const double _max) {

    std::string word;
    if (!(_iss >> word) || word != _keyword) return outputError("Error: Expected " + _keyword);

    double x, y, z;
    if (!(_iss >> x >> y >> z)) return outputError("Error: Invalid " + _keyword + " value type");
    if (x < _min || _max < x) return outputError("Error: first value not in range");
    if (y < _min || _max < y) return outputError("Error: second value not in range");
    if (z < _min || _max < z) return outputError("Error: third value not in range");

    // Success
    return true;
}

bool isMember(std::istringstream& _iss, const std::string& _keyword, std::vector<std::string>& _members) {

    std::string word;
    if (!(_iss >> word) || word != _keyword) return outputError("Error: Expected " + _keyword);

    std::string member;
    if (!(_iss >> member)) return outputError("Error: No " + _keyword + " id found");
    auto it = std::find(_members.begin(), _members.end(), member);
    if (it == _members.end()) return outputError("Error: Invalid " + _keyword + " id");

}
