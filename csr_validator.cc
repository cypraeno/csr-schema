#include "helpers.h"
#include "camera_validator.h"
#include "texture_validator.h"
#include "material_validator.h"
#include "primitive_validator.h"

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

    // Version must come first in the file.
    std::string versionLine;
    if (!getCSRLine(csrFile, line) || !parseVersion(csrFile, line, versionLine)) {
        outputError("Error: Unsupported version or version line missing <<" + versionLine + ">>");
        return 1;
    }

    if (!getCSRLine(csrFile, line) || line != "Camera") {
        outputError("Error: Expected Camera");
        return 1;
    }
    if (!isCamera(csrFile)) return 2;

    std::vector<std::string> materials;
    std::vector<std::string> textures;
    // std::vector<std::string> primitives;         USE IN FUTURE IF PRIMITIVES CAN BE ASSIGNED TO MESHES

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
            if (!isQuad(csrFile, materials)) return 2; 
        }

        else if (line == "Sphere") { 
            if (!isSphere(csrFile, materials)) return 2; 
        }

        else {
            outputError("Error: Invalid Line <<" + line + ">>");
            return 2;
        }
    }

    std::cerr << "CSR file validation passed." << std::endl;

    return 0;
}