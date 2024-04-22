#include "helpers.hh"
#include "camera_validator.hh"
#include "texture_validator.hh"
#include "material_validator.hh"
#include "primitive_validator.hh"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <CSR_File_Path>" << std::endl;
        return 1;
    }

    std::ifstream csrFile(argv[1]);
    if (!csrFile.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    std::string line;

    // Check that the version is the first file line
    std::stringstream ss;
    if (!getCSRLine(csrFile, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isVersion(ss, "0.1.3");

    // Check that camera is defined after version but before everything else
    if (!getCSRLine(csrFile, line) || line != "Camera") outputError("Error: Expected Camera");
    isCamera(csrFile);

    std::vector<std::string> materials;
    std::vector<std::string> textures;
    std::vector<std::string> quads;
    std::vector<std::string> spheres;

    while(getCSRLine(csrFile, line)) {

        if (line.find("Texture") != std::string::npos) {

            size_t start_pos = line.find_first_of('[');
            if (start_pos == std::string::npos) outputError("Error: Material type indicator <<[>> missing");

            size_t end_pos = line.find_first_of(']', start_pos);
            if (end_pos == std::string::npos) outputError("Error: Material type indicator <<]>> missing");

            std::string texture_type = line.substr(start_pos, end_pos - start_pos + 1);
            isTexture(csrFile, texture_type, textures);
        }

        else if (line.find("Material") != std::string::npos) {

            size_t start_pos = line.find_first_of('[');
            if (start_pos == std::string::npos) outputError("Error: Material type indicator <<[>> missing");

            size_t end_pos = line.find_first_of(']', start_pos);
            if (end_pos == std::string::npos) outputError("Error: Material type indicator <<]>> missing");

            std::string material_type = line.substr(start_pos, end_pos - start_pos + 1);
            isMaterial(csrFile, material_type, textures, materials);  
        }

        else if (line == "Quad") isQuad(csrFile, materials, quads);

        else if (line == "Sphere") isSphere(csrFile, materials, spheres);

        else outputError("Error: Invalid Line <<" + line + ">>");
    }

    std::cerr << "CSR file validation passed." << std::endl;

    return 0;
}