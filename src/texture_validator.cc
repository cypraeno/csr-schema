#include "texture_validator.hh"

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
    if (!getCSRLine(_file, _line)) return outputError("Error: Unexpected EOF");
    if (!isId(_line, id)) return outputError("Error: Expected id");
    if (id == "no") return outputError("Error: 'no' is reserved");

    // Success
    if (texIt->second(_file)) {
        _textures.push_back(id);
        return true;
    }
    
    return false;
}

bool isChecker(std::ifstream& _file) {
    
    std::string line, keyword;
    std::stringstream ss;

    // Check for valid scale
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isDouble(ss, "scale", 0.0, P_INF)) return false;

    // Check for valid c1
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isXYZ(ss, "c1", 0.0, 255.0)) return false;

    // Check for valid c2
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isXYZ(ss, "c2", 0.0, 255.0)) return false;

    // Success
    return true;
}

bool isImage(std::ifstream& _file) {

    std::string line, keyword;
    std::stringstream ss;

    // Check for valid path
    std::vector<std::string> fileTypes{ ".png", ".jpg"};
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isFilePath(ss, fileTypes)) return false;

    // Success
    return true;
}
