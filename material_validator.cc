#include "material_validator.h"

using materialValidatorFunction = std::function<bool(std::ifstream&, std::vector<std::string>&)>;

// Forward declarations
bool isDielectric(std::ifstream& _file, std::vector<std::string>& _textures);
bool isEmissive(std::ifstream& _file, std::vector<std::string>& _textures);
bool isLambertian(std::ifstream& _file, std::vector<std::string>& _textures);
bool isMetal(std::ifstream& _file, std::vector<std::string>& _textures);

// UPDATE this list as new materials are defined
std::map<std::string, materialValidatorFunction> materialValidatorMap {
    { "[Dielectric]", isDielectric },
    { "[Emissive]", isEmissive },
    { "[Lambertian]", isLambertian },
    { "[Metal]", isMetal },
};

bool isMaterial(std::ifstream& _file, std::string& _material_type, std::vector<std::string>& _textures, std::vector<std::string>& _materials) {

    // Check for valid material type
    auto matIt = materialValidatorMap.find(_material_type);
    if (matIt == materialValidatorMap.end()) outputError("Error: Unknown material type: " + _material_type);

    std::string line, id;
    
    // Check for valid ID
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    if (!isId(line, id)) return outputError("Error: Expected id");

    // Success
    if (matIt->second(_file, _textures)) {
        _materials.push_back(id);
        return true;
    }

    return false;
}

bool isDielectric(std::ifstream& _file, std::vector<std::string>& _textures) {
    
    std::string line;
    std::istringstream iss;

    // Check for valid IR
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    
    iss.str(line);
    if (!isDouble(iss, "ir", 1.0, P_INF)) return false;

    // Success
    return true;
}

bool isEmissive(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line;
    std::istringstream iss;

    // Check for valid RGB
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isXYZ(iss, "rgb", 0.0, 255.0)) return false;

    // Check for valid strength
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isDouble(iss, "strength", 0.0, P_INF)) return false;

    // Success
    return true;
}

bool isLambertian(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line, keyword;
    std::istringstream iss;

    // Check for valid texture
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!(iss >> keyword) || keyword != "texture") return outputError("Error: Expected texture");

    std::string texture;
    if (!(iss >> texture)) return outputError("Error: No texture id found");
    if (texture != "no") {
        auto it = std::find(_textures.begin(), _textures.end(), texture);
        if (it == _textures.end()) return outputError("Error: Invalid texture id");
    }

    // Check for valid albedo
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    iss.str(line);
    if (!isXYZ(iss, "albedo", 0.0, 255.0)) return false;

    // Success
    return true;
}

bool isMetal(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line;
    std::istringstream iss;

    // Check for valid albedo
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isXYZ(iss, "albedo", 0.0, 255.0)) return false;

    // Check for valid fuzz
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isDouble(iss, "fuzz", 0.0, P_INF)) return false;

    // Success
    return true;
}
