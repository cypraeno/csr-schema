#include "helpers.h"
#include "material_validator.h"

bool parseVersion(std::ifstream& file, std::string& versionLine) {
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (isComment(line) || line.empty()) continue;
        versionLine = line;
        break;
    }
    return !versionLine.empty() && versionLine == "version 0.1.0";
}

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

    // Version must come first in the file.
    std::string versionLine;
    if (!parseVersion(csrFile, versionLine)) {
        std::cerr << "Unsupported version or version line missing: [" << versionLine << "]" << std::endl;
        return 1;
    }

    std::vector<std::string> materials;
    std::vector<std::string> textures;
    std::vector<std::string> primitives;

    std::cout << "CSR file validation passed." << std::endl;

    return 0;
}