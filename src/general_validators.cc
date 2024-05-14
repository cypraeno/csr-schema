#include "general_validators.hh"

void isFilePath(std::ifstream& _file, const std::vector<std::string>& _inputFileTypes, std::string& _path) {

    std::string line;
    std::stringstream ss;

    if (!getCSRLine(_file, line) || !(ss << line))  outputError("Error: Unexpected EOF", exitCode::NO_INPUT);

    std::string word;
    if (!(ss >> word) || word != "path")            outputError("Error: Expected path", exitCode::BAD_INPUT);
    
    if (!(ss >> _path))                             outputError("Error: Invalid path", exitCode::BAD_INPUT);

    // Check if the file is accessible
    std::ifstream file(_path);
    if (!file.is_open())                            outputError("Error: Unable to open file", exitCode::FILE_ERROR);
    file.close();

    // Check if the file is a valid file type
    bool validFileType = false;
    for (const auto& type : _inputFileTypes) {
        if (_path.size() >= type.size() && _path.substr(_path.size() - type.size(), type.size()) == type) {
            validFileType = true;
            break;
        }
    }

    if (!validFileType)                             outputError("Error: Invalid file type", exitCode::BAD_INPUT);
}

void isBoolean(std::ifstream& _file, const std::string& _keyword, bool& _value) {
    
        std::string line;
        std::stringstream ss;
    
        if (!getCSRLine(_file, line) || !(ss << line))  outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    
        std::string word;
        if (!(ss >> word) || word != _keyword)          outputError("Error: Expected " + _keyword, exitCode::BAD_INPUT);

        if(!(ss >> std::boolalpha >> _value))           outputError("Error: No " + _keyword + " found. Valid inputs are [true/false]", exitCode::BAD_INPUT);
}

void isDouble(std::ifstream& _file, const std::string& _keyword, const double _min, const double _max, double& _value) {
    
    std::string line;
    std::stringstream ss;

    if (!getCSRLine(_file, line) || !(ss << line))  outputError("Error: Unexpected EOF", exitCode::NO_INPUT);

    std::string word;
    if (!(ss >> word) || word != _keyword)          outputError("Error: Expected " + _keyword, exitCode::BAD_INPUT);

    if(!(ss >> _value))                             outputError("Error: No " + _keyword + " found", exitCode::BAD_INPUT);
    if (_value < _min || _max < _value)             outputError("Error: " + _keyword + " not in range", exitCode::BAD_INPUT);
}

void isXYZ(std::ifstream& _file, const std::string& _keyword, const double _min, const double _max, xyz& _xyz) {

    std::string line;
    std::stringstream ss;

    if (!getCSRLine(_file, line) || !(ss << line))  outputError("Error: Unexpected EOF", exitCode::NO_INPUT);

    std::string word;
    if (!(ss >> word) || word != _keyword)          outputError("Error: Expected " + _keyword, exitCode::BAD_INPUT);
    
    if (!(ss >> _xyz.x >> _xyz.y >> _xyz.z))        outputError("Error: No " + _keyword + " found", exitCode::BAD_INPUT);
    if (_xyz.x < _min || _max < _xyz.x)             outputError("Error: First value not in range", exitCode::BAD_INPUT);
    if (_xyz.y < _min || _max < _xyz.y)             outputError("Error: Second value not in range", exitCode::BAD_INPUT);
    if (_xyz.z < _min || _max < _xyz.z)             outputError("Error: Third value not in range", exitCode::BAD_INPUT);
}

void isRatio(std::ifstream& _file, const std::string& _keyword, const double _min, const double _max, ratio& _ratio) {

    std::string line;
    std::stringstream ss;

    if (!getCSRLine(_file, line) || !(ss << line))                              outputError("Error: Unexpected EOF", exitCode::NO_INPUT);

    std::string keyword;
    if (!(ss >> keyword) || keyword != _keyword)                                outputError("Error: Expected " + _keyword, exitCode::BAD_INPUT);

    char slash;
    if (!(ss >> _ratio.num >> slash >> _ratio.denom) || slash != '/')           outputError("Error: No " + _keyword + " found", exitCode::BAD_INPUT);
    if (_ratio.denom == 0)                                                      outputError("Error: Denominator is 0", exitCode::BAD_INPUT);
    if (_ratio.num / _ratio.denom < _min || _max < _ratio.num / _ratio.denom)   outputError("Error: Ratio not in range", exitCode::BAD_INPUT);
}

void isVersion(std::ifstream& _file, std::string& _version) {

    std::string line;
    std::stringstream ss;

    if (!getCSRLine(_file, line) || !(ss << line))  outputError("Error: Unexpected EOF", exitCode::NO_INPUT);

    std::string keyword;
    if (!(ss >> keyword) || keyword != "version")   outputError("Error: Expected version", exitCode::BAD_INPUT);
    
    if (!(ss >> _version) || _version.empty())      outputError("Error: No version found", exitCode::BAD_INPUT);
    if (_version != CURRENT_VERSION)                outputError("Error: Unsupported version <<" + _version + ">>. Must use <<" + CURRENT_VERSION + ">>", exitCode::BAD_INPUT);
}

bool isMember(std::ifstream& _file, const std::string& _keyword, const std::vector<std::string>& _members, std::string& _member) {

    std::string line;
    std::stringstream ss;

    if (!getCSRLine(_file, line) || !(ss << line))  outputError("Error: Unexpected EOF", exitCode::NO_INPUT);

    std::string keyword;
    if (!(ss >> keyword) || keyword != _keyword)    outputError("Error: Expected " + _keyword, exitCode::BAD_INPUT);
    
    if (!(ss >> _member))                           outputError("Error: No " + _keyword + " found", exitCode::BAD_INPUT);

    // No Errors
    const auto it = std::find(_members.begin(), _members.end(), _member);
    return it != _members.end();
}