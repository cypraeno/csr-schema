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

void isTexture(std::ifstream& _file, const std::string& _textureType, std::vector<std::string>& _textures) {

    std::string id;

    // Check for valid texture type
    auto texIt = textureValidatorMap.find(_textureType);
    if (texIt == textureValidatorMap.end()) outputError("Error: Unknown texture type: " + _textureType, exitCode::UNKNOWN_INPUT);

    // Check for valid ID
    if (isMember(_file, "id", _textures, id)) outputError("Error: texture id taken", exitCode::ID_TAKEN);
    if (id == "no") outputError("Error: 'no' is reserved", exitCode::BAD_INPUT);

    // Check specific texture type
    texIt->second(_file);

    // Success
    _textures.push_back(id);
}

void isChecker(std::ifstream& _file) {

    double scale;
    xyz c1, c2;
    
    isDouble(_file, "scale", 0.0, P_INF, scale);    // Check for valid scale
    isXYZ(_file, "c1", 0.0, 255.0, c1);             // Check for valid c1
    isXYZ(_file, "c2", 0.0, 255.0, c2);             // Check for valid c2
}

void isImage(std::ifstream& _file) {

    std::string path;
    std::stringstream ss;

    // Check for valid path
    std::vector<std::string> imageFileTypes{ ".png", ".jpg", ".hdr", ".pic", ".ppm", ".pgm", ".psd", ".bmp" };
    isFilePath(_file, imageFileTypes, path);
}
