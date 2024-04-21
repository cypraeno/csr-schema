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
    if (!getCSRLine(csrFile, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isVersion(ss)) return 1;

    // Check that camera is defined after version but before everything else
    if (!getCSRLine(csrFile, line) || line != "Camera") {
        outputError("Error: Expected Camera");
        return 1;
    }
    if (!isCamera(csrFile)) return 2;

    std::vector<std::string> materials;
    std::vector<std::string> textures;
    std::vector<std::string> quads;
    std::vector<std::string> spheres;

    // EDGE CASE: if the user names a Material as Material[Texture]
    while(getCSRLine(csrFile, line)) {

        if (line.find("Texture") != std::string::npos) {

            size_t start_pos = line.find_first_of('[');
            if (start_pos == std::string::npos) {
                outputError("Error: Texture type indicator <<[>> missing");
                return 2;
            }
            size_t end_pos = line.find_first_of(']', start_pos);
            if (end_pos == std::string::npos) {
                outputError("Error: Texture type indicator <<]>> missing");
                return 2;
            }

            std::string texture_type = line.substr(start_pos, end_pos - start_pos + 1);
            if (!isTexture(csrFile, texture_type, textures)) return 2;
        }

        else if (line.find("Material") != std::string::npos) {

            size_t start_pos = line.find_first_of('[');
            if (start_pos == std::string::npos) {
                outputError("Error: Material type indicator <<[>> missing");
                return 2;
            }
            size_t end_pos = line.find_first_of(']', start_pos);
            if (end_pos == std::string::npos) {
                outputError("Error: Material type indicator <<]>> missing");
                return 2;
            }

            std::string material_type = line.substr(start_pos, end_pos - start_pos + 1);
            if (!isMaterial(csrFile, material_type, textures, materials)) return 2;   
        }

        else if (line == "Quad") { 
            if (!isQuad(csrFile, materials, quads)) return 2; 
        }

        else if (line == "Sphere") { 
            if (!isSphere(csrFile, materials, spheres)) return 2; 
        }

        else {
            outputError("Error: Invalid Line <<" + line + ">>");
            return 2;
        }
    }

    std::cerr << "CSR file validation passed." << std::endl;

    return 0;
}