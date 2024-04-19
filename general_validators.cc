#include "general_validators.h"

namespace fs = std::experimental::filesystem;

bool isFilePath(std::stringstream& _ss, const std::vector<std::string>& _fileTypes) {

    std::string word;
    if (!(_ss >> word) || word != "path") return outputError("Error: Expected path");

    std::string path;
    if (!(_ss >> path)) return outputError("Error: Invalid path");

    // Check if the file exists
    if (!fs::exists(path)) return outputError("Error: File does not exist");

    // Check if the file is accessible
    std::ifstream file(path);
    if (!file.is_open()) return outputError("Error: Unable to open file");
    file.close();

    // Check if the file is a valid file type
    bool validFileType = outputError("Error: Invalid file type");
    for (const auto& type : _fileTypes) {
        if (path.size() >= type.size() && path.substr(path.size() - type.size(), type.size()) == type) {
            validFileType = true;
            break;
        }
    }

    resetsstream(_ss);

    // Success
    return validFileType; 
}

bool isDouble(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max) {
    
    std::string word;
    if (!(_ss >> word) || word != _keyword) return outputError("Error: Expected " + _keyword);

    double value;
    if(!(_ss >> value)) return outputError("Error: Invalid " + _keyword + " value type");
    if (value < _min || _max < value) return outputError("Error: Value not in range");

    resetsstream(_ss);

    // Success
    return true;
}

bool isXYZ(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max) {

    std::string word;
    if (!(_ss >> word) || word != _keyword) return outputError("Error: Expected " + _keyword);

    double x, y, z;
    if (!(_ss >> x >> y >> z)) return outputError("Error: Invalid " + _keyword + " value type");
    if (x < _min || _max < x) return outputError("Error: First value not in range");
    if (y < _min || _max < y) return outputError("Error: Second value not in range");
    if (z < _min || _max < z) return outputError("Error: Third value not in range");

    resetsstream(_ss);

    // Success
    return true;
}

bool isRatio(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max) {

    std::string word;
    if (!(_ss >> word) || word != _keyword) return outputError("Error: Expected " + _keyword);

    double x, y;
    char slash;

    if (!(_ss >> x >> slash >> y) || slash != '/') return outputError("Error: No " + _keyword + " id found");
    if (y = 0) return outputError("Error: Denominator is 0");
    if (x / y < _min || _max < x / y) return outputError("Error: Ratio not in range");

    resetsstream(_ss);

    // Success
    return true;
}

bool isVersion(std::ifstream& _ss, std::string& _line, std::string& _versionLine) {

    std::string word;
    if (!(_ss >> word) || word != "version") return outputError("Error: Expected path");

    _versionLine = _line;
    return !_versionLine.empty();
}

bool isMember(std::stringstream& _ss, const std::string& _keyword, std::vector<std::string>& _members) {

    std::string word;
    if (!(_ss >> word) || word != _keyword) return outputError("Error: Expected " + _keyword);

    std::string member;
    if (!(_ss >> member)) return outputError("Error: No " + _keyword + " id found");
    const auto it = std::find(_members.begin(), _members.end(), member);
    if (it == _members.end()) return outputError("Error: Invalid " + _keyword + " id");

    resetsstream(_ss);

    // Success
    return true;
}
