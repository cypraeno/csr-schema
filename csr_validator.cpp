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


bool isComment(const std::string& line) {
    // Check if the first non-whitespace character is '#'
    for (char ch : line) {
        if (std::isspace(ch)) continue; // Skip whitespace
        return ch == '#';
    }
    return false;
}

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

    std::cout << "CSR file validation passed." << std::endl;

    return 0;
}