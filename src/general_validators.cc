#include "general_validators.hh"

void isFilePath(std::stringstream& _ss, const std::vector<std::string>& _fileTypes) {

    std::string word;
    if (!(_ss >> word) || word != "path") outputError("Error: Expected path", exitCode::BAD_INPUT);

    std::string path;
    if (!(_ss >> path)) outputError("Error: Invalid path", exitCode::BAD_INPUT);

    // Check if the file is accessible
    std::ifstream file(path);
    if (!file.is_open()) outputError("Error: Unable to open file", exitCode::FILE_ERROR);
    file.close();

    // Check if the file is a valid file type
    bool validFileType = false;
    for (const auto& type : _fileTypes) {
        if (path.size() >= type.size() && path.substr(path.size() - type.size(), type.size()) == type) {
            validFileType = true;
            break;
        }
    }

    if (!validFileType) outputError("Error: Invalid file type", exitCode::BAD_INPUT);

    resetsstream(_ss);
}

void isDouble(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max) {
    
    std::string word;
    if (!(_ss >> word) || word != _keyword) outputError("Error: Expected " + _keyword, exitCode::BAD_INPUT);

    double value;
    if(!(_ss >> value)) outputError("Error: No " + _keyword + " found", exitCode::BAD_INPUT);
    if (value < _min || _max < value) outputError("Error: " + _keyword + " not in range", exitCode::BAD_INPUT);

    resetsstream(_ss);
}

void isXYZ(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max) {

    std::string word;
    if (!(_ss >> word) || word != _keyword) outputError("Error: Expected " + _keyword, exitCode::BAD_INPUT);

    double x, y, z;
    if (!(_ss >> x >> y >> z)) outputError("Error: No " + _keyword + " found", exitCode::BAD_INPUT);
    if (x < _min || _max < x) outputError("Error: First value not in range", exitCode::BAD_INPUT);
    if (y < _min || _max < y) outputError("Error: Second value not in range", exitCode::BAD_INPUT);
    if (z < _min || _max < z) outputError("Error: Third value not in range", exitCode::BAD_INPUT);

    resetsstream(_ss);
}

void isRatio(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max) {

    std::string word;
    if (!(_ss >> word) || word != _keyword) outputError("Error: Expected " + _keyword, exitCode::BAD_INPUT);

    double x, y;
    char slash;

    if (!(_ss >> x >> slash >> y) || slash != '/') outputError("Error: No " + _keyword + " found", exitCode::BAD_INPUT);
    if (y = 0) outputError("Error: Denominator is 0", exitCode::BAD_INPUT);
    if (x / y < _min || _max < x / y) outputError("Error: Ratio not in range", exitCode::BAD_INPUT);

    resetsstream(_ss);
}

void isVersion(std::stringstream& _ss, const std::string& _version) {

    std::string word;
    if (!(_ss >> word) || word != "version") outputError("Error: Expected version", exitCode::BAD_INPUT);

    std::string version;
    if (!(_ss >> version) || version.empty()) outputError("Error: No version found", exitCode::BAD_INPUT);
    if (version != _version) outputError("Error: Unsupported version <<" + version + ">>. Must use <<" + _version + ">>", exitCode::BAD_INPUT);

    resetsstream(_ss);
}

bool isMember(std::stringstream& _ss, const std::string& _keyword, const std::vector<std::string>& _members, std::string& _member) {

    std::string word;
    if (!(_ss >> word) || word != _keyword) outputError("Error: Expected " + _keyword, exitCode::BAD_INPUT);
    if (!(_ss >> _member)) outputError("Error: No " + _keyword + " found", exitCode::BAD_INPUT);

    resetsstream(_ss);

    // No Errors
    const auto it = std::find(_members.begin(), _members.end(), _member);
    return it != _members.end();
}