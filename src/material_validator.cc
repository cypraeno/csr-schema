#include "material_validator.hh"

using materialValidatorFunction = std::function<void(std::ifstream&, const std::vector<std::string>&, std::vector<std::string>& _materials)>;

// Forward declarations
void isDielectric(std::ifstream& _file, const std::vector<std::string>& _textures, std::vector<std::string>& _materials);
void isEmissive(std::ifstream& _file, const std::vector<std::string>& _textures, std::vector<std::string>& _materials);
void isDiffuse(std::ifstream& _file, const std::vector<std::string>& _textures, std::vector<std::string>& _materials);
void isMetal(std::ifstream& _file, const std::vector<std::string>& _textures, std::vector<std::string>& _materials);
void isMixture(std::ifstream& _file, const std::vector<std::string>& _textures, std::vector<std::string>& _materials);

// UPDATE this list as new materials are defined
std::map<std::string, materialValidatorFunction> materialValidatorMap {
    { "[Dielectric]", isDielectric },
    { "[Emissive]", isEmissive },
    { "[Diffuse]", isDiffuse },
    { "[Metal]", isMetal },
    { "[Mixture]", isMixture }
};

void isMaterial(std::ifstream& _file, const std::string& _materialType, const std::vector<std::string>& _textures, std::vector<std::string>& _materials) {

    std::string id;

    // Check for valid material type
    auto matIt = materialValidatorMap.find(_materialType);
    if (matIt == materialValidatorMap.end()) outputError("Error: Unknown material type: " + _materialType, exitCode::UNKNOWN_INPUT); 

    // Check for valid ID
    if (isMember(_file, "id", _materials, id)) outputError("Error: material id taken", exitCode::ID_TAKEN);                            

    // Check specific material type  
    matIt->second(_file, _textures, _materials);                                                              

    // No Errors
    _materials.push_back(id);
}

void isDielectric(std::ifstream& _file, const std::vector<std::string>& _textures, std::vector<std::string>& _materials) {
    xyz albedo;
    double eta, roughness, sheen;

    isXYZ(_file, "albedo", 0.0, 255.0, albedo); // Check for valid albedo
    isDouble(_file, "eta", 1.0, P_INF, eta);  // Check for valid IR
    isDouble(_file, "roughness", 0.0, 1.0, roughness);  // Check for valid roughness
    isDouble(_file, "sheen", 0.0, P_INF, sheen); // Check for valid sheen

    if (sheen != static_cast<int>(sheen)) { outputError("Error: sheen must be an integer.", exitCode::INCORRECT_ARG); }
}

void isEmissive(std::ifstream& _file, const std::vector<std::string>& _textures, std::vector<std::string>& _materials) {

    xyz rgb;
    double strength;
    
    isXYZ(_file, "rgb", 0.0, 255.0, rgb);               // Check for valid RGB
    isDouble(_file, "strength", 0.0, P_INF, strength);  // Check for valid strength
}

void isDiffuse(std::ifstream& _file, const std::vector<std::string>& _textures, std::vector<std::string>& _materials) {

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

void isMetal(std::ifstream& _file, const std::vector<std::string>& _textures, std::vector<std::string>& _materials) {

    xyz albedo;
    double roughness;

    isXYZ(_file, "albedo", 0.0, 255.0, albedo);     // Check for valid albedo
    isDouble(_file, "roughness", 0.0, P_INF, roughness);      // Check for valid roughness
}

void isMixture(std::ifstream& _file, const std::vector<std::string>& _textures, std::vector<std::string>& _materials) {

    double num;

    isDouble(_file, "num", 0, P_INF, num); // check for valid number of materials
    if (num != static_cast<int>(num)) { outputError("Error: num must be an integer.", exitCode::INCORRECT_ARG); } // check num is integer

    double weight_remaining = 1.0;
    for (int i=0; i < (int)num; i++) { // for each material, validate weight and material id is provided
        double weight;
        std::string material;

        // Check for valid material
        if (!isMember(_file, "mixed", _materials, material)) outputError("Error: Unknown material id", exitCode::UNKNOWN_ID); 
        
        // Check for valid weight, and that the sum of all weights does not exceed 1.0
        isDouble(_file, "weight", 0.0, weight_remaining, weight);

        // Subtract from weight remaining
        weight_remaining -= weight;
    }
}