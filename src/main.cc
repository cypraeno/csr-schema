#include "csr_validator.hh"
#include "helpers.hh"

int main(int argc, char** argv) {

    // Check for correct number of args
    if (argc != 2)                                       outputError("Usage: " + std::string(argv[0]) + " <CSR_File_Path>", exitCode::MISSING_ARG);

    // Check that file can be opened
    std::ifstream csrFile(argv[1]);
    if (!csrFile.is_open())                             outputError("Error: Failed to open file: " + std::string(argv[1]), exitCode::FILE_ERROR);

    // Check if CSR file is valid
    isCSR(csrFile);

    // Success
    std::cerr << "CSR file validation passed." << std::endl;
    csrFile.close();
    return 0;
}