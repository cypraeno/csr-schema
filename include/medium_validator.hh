#ifndef MED_VALIDATOR
#define MED_VALIDATOR

#include "helpers.hh"
#include "general_validators.hh"

/**
 * @brief Checks if a file section starting with "Medium" is a validly formatted .csr medium
 * 
 * @param[in]       _file           The file being validated
 * @param[in, out]  _mediums        A vector of mediums to be updated if the medium is valid
 * 
 * @note exits if medium is invalid
 */
void isMedium(std::ifstream& _file, std::vector<std::string>& _mediums);

#endif