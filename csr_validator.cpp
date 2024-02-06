#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string trim(const std::string& str) {
    std::string whitespace = " \t\r\n"; // Include carriage return and tab
    size_t first = str.find_first_not_of(whitespace);
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, (last - first + 1));
}

bool parseVersion(std::ifstream& file) {
    std::string line;
    std::getline(file, line); // Read the comment line
    if (!std::getline(file, line)) {
        std::cerr << "Failed to read version line." << std::endl;
        return false;
    }
    line = trim(line); // Trim whitespace
    if (line != "version 0.1.0") {
        std::cerr << "Unsupported version or version line missing: " << line << std::endl;
        return false;
    }
    return true;
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

    if (!parseVersion(csrFile)) {
        return 1; // Version parsing failed
    }

    std::cout << "CSR file validation passed." << std::endl;

    return 0;
}