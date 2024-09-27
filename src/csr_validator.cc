#include "csr_validator.hh"

void isCSR(std::string& _filePath) {

    std::string line;

    // Check that file can be opened
    std::ifstream file(_filePath);
    if (!file.is_open() || !file.good())                outputError("Error: Failed to open file: " + std::string(_filePath), exitCode::FILE_ERROR);
    
    // Check that the version is the first file line
    std::string version;
    isVersion(file, version);

    // Check that camera is defined after version but before everything else
    std::stringstream ss;
    std::string keyword;
    if (!getCSRLine(file, line) || !(ss << line))       outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    if (!(ss >> keyword) || keyword != "Camera")        outputError("Error: Expected Camera ", exitCode::BAD_INPUT);
    isCamera(file);

    // Initialize ID vectors
    std::vector<std::string> materials;
    std::vector<std::string> textures{ "no" };
    std::vector<std::string> mediums;
    std::vector<std::string> volumes;

    // Initialize map of primitve ID vectors
    std::map<std::string, std::vector<std::string>> primitiveMap {
        { "[QuadPrimitive]", {} },
        { "[SpherePrimitive]", {} },
        { "[BoxPrimitive]", {} },
    };

    // Validate body of CSR file
    while(getCSRLine(file, line)) {

        // Validate textures
        if (line.find("Texture") != std::string::npos) {
            std::string texture_type;
            getType(line, texture_type);
            isTexture(file, texture_type, textures);
        }

        // Validate materials
        else if (line.find("Material") != std::string::npos) {
            std::string material_type;
            getType(line, material_type);
            isMaterial(file, material_type, textures, materials);  
        }

        // Validate instances
        else if (line.find("Instance") != std::string::npos) {
            std::string instance_type;
            getType(line, instance_type);
            isInstance(file, instance_type, primitiveMap);
        }

        // Validate quads
        else if (line == "Quad") isQuad(file, materials, primitiveMap["[QuadPrimitive]"]);

        // Validate spheres
        else if (line == "Sphere") isSphere(file, materials, primitiveMap["[SpherePrimitive]"]);

        // Validate boxes
        else if (line == "Box") isBox(file, materials, primitiveMap["[BoxPrimitive]"]);

        // Validate Sky
        else if (line == "Sky") isSky(file);

        else if (line == "Medium") isMedium(file, mediums);

        else if (line == "Volume") {
            std::vector<std::string> concatenated = primitiveMap["[SpherePrimitive]"]; 
            concatenated.insert(concatenated.end(), primitiveMap["[BoxPrimitive]"].begin(), primitiveMap["[BoxPrimitive]"].end());
            isVolume(file, mediums, concatenated, volumes);
        }

        else outputError("Error: Invalid Line <<" + line + ">>", exitCode::UNKNOWN_INPUT);
    }

    file.close();
}