#include "texture_validator.hh"

using textureValidatorFunction = std::function<void(std::ifstream&)>;

// Forward declarations
void isChecker(std::ifstream& _file);
void isImage(std::ifstream& _file);

// UPDATE this list as new materials are defined
std::map<std::string, textureValidatorFunction> textureValidatorMap {
    { "[Checker]", isChecker },
    { "[Image]", isImage },
};

void isTexture(std::ifstream& _file, std::string& _textureType, std::vector<std::string>& _textures) {

    // Check for valid texture type
    auto texIt = textureValidatorMap.find(_textureType);
    if (texIt == textureValidatorMap.end()) outputError("Error: Unknown texture type: " + _textureType);

    std::string line, id;
    std::stringstream ss;

    // Check for valid ID
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    if (isMember(ss, "id", _textures, id)) outputError("Error: texture id taken");
    if (id == "no") outputError("Error: 'no' is reserved");

    // Check specific texture type
    texIt->second(_file);

    // Success
    _textures.push_back(id);
}

void isChecker(std::ifstream& _file) {
    
    std::string line;
    std::stringstream ss;

    // Check for valid scale
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isDouble(ss, "scale", 0.0, P_INF);

    // Check for valid c1
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "c1", 0.0, 255.0);

    // Check for valid c2
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "c2", 0.0, 255.0);
}

void isImage(std::ifstream& _file) {

    std::string line;
    std::stringstream ss;

    // Check for valid path
    std::vector<std::string> fileTypes{ ".png", ".jpg" };
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isFilePath(ss, fileTypes);
}
