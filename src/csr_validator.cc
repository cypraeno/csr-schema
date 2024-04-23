#include "csr_validator.hh"

void isCSR(std::ifstream& _file) {
    std::string line;

    // Check that the version is the first file line
    std::string version;
    isVersion(_file, version);

    // Check that camera is defined after version but before everything else
    std::stringstream ss;
    std::string keyword;
    if (!getCSRLine(_file, line) || !(ss << line))    outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    if (!(ss >> keyword) || keyword != "Camera")        outputError("Error: Expected Camera ", exitCode::BAD_INPUT);
    isCamera(_file);

    // Initialize ID vectors
    std::vector<std::string> materials;
    std::vector<std::string> textures{ "no" };

    // Initialize map of primitve ID vectors
    std::map<std::string, std::vector<std::string>> primitiveMap {
        { "[QuadPrimitive]", {} },
        { "[SpherePrimitive]", {} },
    };

    // Validate body of CSR file
    while(getCSRLine(_file, line)) {

        // Validate textures
        if (line.find("Texture") != std::string::npos) {
            std::string texture_type;
            getType(line, texture_type);
            isTexture(_file, texture_type, textures);
        }

        // Validate materials
        else if (line.find("Material") != std::string::npos) {
            std::string material_type;
            getType(line, material_type);
            isMaterial(_file, material_type, textures, materials);  
        }

        // Validate instances
        else if (line.find("Instance") != std::string::npos) {
            std::string instance_type;
            getType(line, instance_type);
            isInstance(_file, instance_type, primitiveMap);
        }

        // Validate quads
        else if (line == "Quad") isQuad(_file, materials, primitiveMap["[QuadPrimitive]"]);

        // Validate spheres
        else if (line == "Sphere") isSphere(_file, materials, primitiveMap["[SpherePrimitive]"]);

        else outputError("Error: Invalid Line <<" + line + ">>", exitCode::UNKNOWN_INPUT);
    }
}