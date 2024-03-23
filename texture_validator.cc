#include "texture_validator.h"

using textureValidatorFunction = std::function<bool(std::ifstream&)>;

// Forward declarations
bool isChecker(std::ifstream& _file);
bool isImage(std::ifstream& _file);

// UPDATE this list as new materials are defined
std::map<std::string, textureValidatorFunction> textureValidatorMap {
    { "[Checker]", isChecker },
    { "[Image]", isImage },
};

bool isTexture(std::ifstream& _file, std::string& _texture_type, std::vector<std::string>& _textures) {

    // Check for valid texture type
    auto texIt = textureValidatorMap.find(_texture_type);
    if (texIt == textureValidatorMap.end()) outputError("Error: Unknown texture type: " + _texture_type);

    std::string _line, id;

    // Check for valid ID
    if (!std::getline(_file, _line)) return outputError("Error: Unexpected EOF");
    if (!isId(_line, id)) return outputError("Error: Expected id");

    // Success
    if (texIt->second(_file)) {
        _textures.push_back(id);
        return true;
    }
}

bool isChecker(std::ifstream& _file) {
    
    std::string line, keyword;
    std::istringstream iss;

    // Check for valid scale
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isDouble(iss, "scale", 0.0, P_INF)) return false;

    // Check for valid c1
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isXYZ(iss, "c1", 0.0, 255.0)) return false;

    // Check for valid c1
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isXYZ(iss, "c2", 0.0, 255.0)) return false;
}

bool isImage(std::ifstream& _file) {

    std::string line, keyword;
    std::istringstream iss;

    // Check for valid path
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isFilePath(iss)) return false;

    // Success
    return true;
}
