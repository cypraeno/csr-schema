#include "helpers.hh"
#include "camera_validator.hh"
#include "texture_validator.hh"
#include "material_validator.hh"
#include "primitive_validator.hh"

int main(int argc, char** argv) {

    if (argc < 2) outputError("Usage: " + std::string(argv[0]) + " <CSR_File_Path>");

    std::ifstream csrFile(argv[1]);
    if (!csrFile.is_open()) outputError("Error: Failed to open file: " + std::string(argv[1]));

    std::string line;

    // Check that the version is the first file line
    std::stringstream ss;
    if (!getCSRLine(csrFile, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isVersion(ss, "0.1.3");

    // Check that camera is defined after version but before everything else
    if (!getCSRLine(csrFile, line) || line != "Camera") outputError("Error: Expected Camera");
    isCamera(csrFile);

    std::vector<std::string> materials;
    std::vector<std::string> textures{ "no" };
    std::vector<std::string> quads;
    std::vector<std::string> spheres;

    while(getCSRLine(csrFile, line)) {

        if (line.find("Texture") != std::string::npos) {
            std::string texture_type;
            getType(line, texture_type);
            isTexture(csrFile, texture_type, textures);
        }

        else if (line.find("Material") != std::string::npos) {
            std::string material_type;
            getType(line, material_type);
            isMaterial(csrFile, material_type, textures, materials);  
        }

        else if (line == "Quad") isQuad(csrFile, materials, quads);

        else if (line == "Sphere") isSphere(csrFile, materials, spheres);

        else outputError("Error: Invalid Line <<" + line + ">>");
    }

    std::cerr << "CSR file validation passed." << std::endl;

    return 0;
}