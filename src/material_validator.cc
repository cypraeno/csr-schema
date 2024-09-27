#include "material_validator.hh"

using materialValidatorFunction = std::function<void(std::ifstream&, const std::vector<std::string>&)>;

// Forward declarations
void isDielectric(std::ifstream& _file, const std::vector<std::string>& _textures);
void isEmissive(std::ifstream& _file, const std::vector<std::string>& _textures);
void isDiffuse(std::ifstream& _file, const std::vector<std::string>& _textures);
void isMetal(std::ifstream& _file, const std::vector<std::string>& _textures);

// UPDATE this list as new materials are defined
std::map<std::string, materialValidatorFunction> materialValidatorMap {
    { "[Dielectric]", isDielectric },
    { "[Emissive]", isEmissive },
    { "[Diffuse]", isDiffuse },
    { "[Metal]", isMetal },
};

void isMaterial(std::ifstream& _file, const std::string& _materialType, const std::vector<std::string>& _textures, std::vector<std::string>& _materials) {

    std::string id;

    // Check for valid material type
    auto matIt = materialValidatorMap.find(_materialType);
    if (matIt == materialValidatorMap.end()) outputError("Error: Unknown material type: " + _materialType, exitCode::UNKNOWN_INPUT); 

    // Check for valid ID
    if (isMember(_file, "id", _materials, id)) outputError("Error: material id taken", exitCode::ID_TAKEN);                            

    // Check specific material type  
    matIt->second(_file, _textures);                                                              

    // No Errors
    _materials.push_back(id);
}

void isDielectric(std::ifstream& _file, const std::vector<std::string>& _textures) {
    xyz albedo;
    double eta, roughness, sheen;

    isXYZ(_file, "albedo", 0.0, 255.0, albedo); // Check for valid albedo
    isDouble(_file, "eta", 1.0, P_INF, eta);  // Check for valid IR
    isDouble(_file, "roughness", 0.0, 1.0, roughness);  // Check for valid roughness
    isDouble(_file, "sheen", 0.0, P_INF, sheen); // Check for valid sheen
}

void isEmissive(std::ifstream& _file, const std::vector<std::string>& _textures) {

    xyz rgb;
    double strength;
    
    isXYZ(_file, "rgb", 0.0, 255.0, rgb);               // Check for valid RGB
    isDouble(_file, "strength", 0.0, P_INF, strength);  // Check for valid strength
}

void isDiffuse(std::ifstream& _file, const std::vector<std::string>& _textures) {

    std::string texture;
    xyz albedo;
    double roughness;
    
    // Check for valid texture
    if (!isMember(_file, "texture", _textures, texture)) outputError("Error: Unknown texture id", exitCode::UNKNOWN_ID);     

    // Check for valid albedo (only if texture is "no")
    if (texture == "no") {
        isXYZ(_file, "albedo", 0.0, 255.0, albedo);
        isDouble(_file, "roughness", 0.0, 1.0, roughness);
    }
}

void isMetal(std::ifstream& _file, const std::vector<std::string>& _textures) {

    xyz albedo;
    double roughness;

    isXYZ(_file, "albedo", 0.0, 255.0, albedo);     // Check for valid albedo
    isDouble(_file, "roughness", 0.0, P_INF, roughness);      // Check for valid roughness
}
