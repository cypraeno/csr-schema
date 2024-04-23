#include "csr_validator.hh"
#include "helpers.hh"

int main(int argc, char** argv) {

    // Check for correct number of args
    if (argc != 2) outputError("Usage: " + std::string(argv[0]) + " <CSR_File_Path>", exitCode::MISSING_ARG);

    // Check if CSR file is valid
    std::string filePath = argv[1];
    isCSR(filePath);

    // Success
    std::cerr << "CSR file validation passed." << std::endl;
    return 0;
}