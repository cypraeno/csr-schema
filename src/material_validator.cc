#include "material_validator.hh"

using materialValidatorFunction = std::function<void(std::ifstream&, std::vector<std::string>&)>;

// Forward declarations
void isDielectric(std::ifstream& _file, std::vector<std::string>& _textures);
void isEmissive(std::ifstream& _file, std::vector<std::string>& _textures);
void isLambertian(std::ifstream& _file, std::vector<std::string>& _textures);
void isMetal(std::ifstream& _file, std::vector<std::string>& _textures);

// UPDATE this list as new materials are defined
std::map<std::string, materialValidatorFunction> materialValidatorMap {
    { "[Dielectric]", isDielectric },
    { "[Emissive]", isEmissive },
    { "[Lambertian]", isLambertian },
    { "[Metal]", isMetal },
};

void isMaterial(std::ifstream& _file, std::string& _materialType, std::vector<std::string>& _textures, std::vector<std::string>& _materials) {

    // Check for valid material type
    auto matIt = materialValidatorMap.find(_materialType);
    if (matIt == materialValidatorMap.end()) outputError("Error: Unknown material type: " + _materialType);

    std::string line, id;
    std::stringstream ss;
    
    // Check for valid ID
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    if (isMember(ss, "id", _materials, id)) outputError("Error: material id taken");

    // Check specific material type
    matIt->second(_file, _textures);

    // Success
    _materials.push_back(id);
}

void isDielectric(std::ifstream& _file, std::vector<std::string>& _textures) {
    
    std::string line;
    std::stringstream ss;

    // Check for valid IR
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isDouble(ss, "ir", 1.0, P_INF);
}

void isEmissive(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line;
    std::stringstream ss;

    // Check for valid RGB
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "rgb", 0.0, 255.0);

    // Check for valid strength
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isDouble(ss, "strength", 0.0, P_INF);
}

void isLambertian(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line;
    std::stringstream ss;

    // Check for valid texture
    std::string texture;
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    if (!isMember(ss, "texture", _textures, texture)) outputError("Error: Unknown texture id");

    // Check for valid albedo
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "albedo", 0.0, 255.0);
}

void isMetal(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line;
    std::stringstream ss;

    // Check for valid albedo
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "albedo", 0.0, 255.0);

    // Check for valid fuzz
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isDouble(ss, "fuzz", 0.0, P_INF);
}
