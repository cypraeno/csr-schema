#include "helpers.hh"
#include "camera_validator.hh"
#include "texture_validator.hh"
#include "material_validator.hh"
#include "primitive_validator.hh"

int main(int argc, char** argv) {

    // Check for correct number of args
    if (argc != 2)                                       outputError("Usage: " + std::string(argv[0]) + " <CSR_File_Path>", exitCode::MISSING_ARG);

    // Check that file can be opened
    std::ifstream csrFile(argv[1]);
    if (!csrFile.is_open())                             outputError("Error: Failed to open file: " + std::string(argv[1]), exitCode::FILE_ERROR);

    std::string line;

    // Check that the version is the first file line
    std::string version;
    isVersion(csrFile, version);

    // Check that camera is defined after version but before everything else
    std::stringstream ss;
    std::string keyword;
    if (!getCSRLine(csrFile, line) || !(ss << line))    outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    if (!(ss >> keyword) || keyword != "Camera")        outputError("Error: Expected Camera", exitCode::BAD_INPUT);
    isCamera(csrFile);

    // Initialize ID vectors
    std::vector<std::string> materials;
    std::vector<std::string> textures{ "no" };
    std::vector<std::string> quads;
    std::vector<std::string> spheres;

    // Validate body of CSR file
    while(getCSRLine(csrFile, line)) {

        // Validate textures
        if (line.find("Texture") != std::string::npos) {
            std::string texture_type;
            getType(line, texture_type);
            isTexture(csrFile, texture_type, textures);
        }

        // Validate materials
        else if (line.find("Material") != std::string::npos) {
            std::string material_type;
            getType(line, material_type);
            isMaterial(csrFile, material_type, textures, materials);  
        }

        // Validate quads
        else if (line == "Quad") isQuad(csrFile, materials, quads);

        // Validate spheres
        else if (line == "Sphere") isSphere(csrFile, materials, spheres);

        else outputError("Error: Invalid Line <<" + line + ">>", exitCode::UNKNOWN_INPUT);
    }

    std::cerr << "CSR file validation passed." << std::endl;

    return 0;
}