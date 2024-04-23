#include "general_validators.hh"

void isFilePath(std::stringstream& _ss, const std::vector<std::string>& _fileTypes) {

    std::string word;
    if (!(_ss >> word) || word != "path") outputError("Error: Expected path");

    std::string path;
    if (!(_ss >> path)) outputError("Error: Invalid path");

    // Check if the file is accessible
    std::ifstream file(path);
    if (!file.is_open()) outputError("Error: Unable to open file");
    file.close();

    // Check if the file is a valid file type
    bool validFileType = false;
    for (const auto& type : _fileTypes) {
        if (path.size() >= type.size() && path.substr(path.size() - type.size(), type.size()) == type) {
            validFileType = true;
            break;
        }
    }

    if (!validFileType) outputError("Error: Invalid file type");

    resetsstream(_ss);
}

void isDouble(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max) {
    
    std::string word;
    if (!(_ss >> word) || word != _keyword) outputError("Error: Expected " + _keyword);

    double value;
    if(!(_ss >> value)) outputError("Error: Invalid " + _keyword + " value type");
    if (value < _min || _max < value) outputError("Error: Value not in range");

    resetsstream(_ss);
}

void isXYZ(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max) {

    std::string word;
    if (!(_ss >> word) || word != _keyword) outputError("Error: Expected " + _keyword);

    double x, y, z;
    if (!(_ss >> x >> y >> z)) outputError("Error: Invalid " + _keyword + " value type");
    if (x < _min || _max < x) outputError("Error: First value not in range");
    if (y < _min || _max < y) outputError("Error: Second value not in range");
    if (z < _min || _max < z) outputError("Error: Third value not in range");

    resetsstream(_ss);
}

void isRatio(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max) {

    std::string word;
    if (!(_ss >> word) || word != _keyword) outputError("Error: Expected " + _keyword);

    double x, y;
    char slash;

    if (!(_ss >> x >> slash >> y) || slash != '/') outputError("Error: No " + _keyword + " id found");
    if (y = 0) outputError("Error: Denominator is 0");
    if (x / y < _min || _max < x / y) outputError("Error: Ratio not in range");

    resetsstream(_ss);
}

void isVersion(std::stringstream& _ss, const std::string& _version) {

    std::string word;
    if (!(_ss >> word) || word != "version") outputError("Error: Expected version");

    std::string version;
    if (!(_ss >> version) || version.empty()) outputError("Error: No version found");
    if (version != _version) outputError("Error: Unsupported version <<" + version + ">>. Must use <<" + _version + ">>");

    resetsstream(_ss);
}

bool isMember(std::stringstream& _ss, const std::string& _keyword, const std::vector<std::string>& _members, std::string& _member) {

    std::string word;
    if (!(_ss >> word) || word != _keyword) outputError("Error: Expected " + _keyword);
    if (!(_ss >> _member)) outputError("Error: No " + _keyword + " found");

    resetsstream(_ss);

    // No Errors
    const auto it = std::find(_members.begin(), _members.end(), _member);
    return it != _members.end();
}