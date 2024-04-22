#include "material_validator.hh"

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

bool isMaterial(std::ifstream& _file, std::string& _materialType, std::vector<std::string>& _textures, std::vector<std::string>& _materials) {

    // Check for valid material type
    auto matIt = materialValidatorMap.find(_materialType);
    if (matIt == materialValidatorMap.end()) outputError("Error: Unknown material type: " + _materialType);

    std::string line, id;
    std::stringstream ss;
    
    // Check for valid ID
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    if (isMember(ss, "id", _materials, id)) outputError("Error: material id taken");

    // Success
    if (matIt->second(_file, _textures)) {
        _materials.push_back(id);
        return true;
    }

    return false;
}

bool isDielectric(std::ifstream& _file, std::vector<std::string>& _textures) {
    
    std::string line;
    std::stringstream ss;

    // Check for valid IR
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isDouble(ss, "ir", 1.0, P_INF);

    // Success
    return true;
}

bool isEmissive(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line;
    std::stringstream ss;

    // Check for valid RGB
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "rgb", 0.0, 255.0);

    // Check for valid strength
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isDouble(ss, "strength", 0.0, P_INF);

    // Success
    return true;
}

bool isLambertian(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line;
    std::stringstream ss;

    // Check for valid texture
    std::string texture;
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    if (!isMember(ss, "texture", _textures, texture)) outputError("Error: Unknown texture id");

    // Check for valid albedo
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "albedo", 0.0, 255.0);

    // Success
    return true;
}

bool isMetal(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line;
    std::stringstream ss;

    // Check for valid albedo
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "albedo", 0.0, 255.0);

    // Check for valid fuzz
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isDouble(ss, "fuzz", 0.0, P_INF);

    // Success
    return true;
}
