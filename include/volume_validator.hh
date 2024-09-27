#ifndef VOL_VALIDATOR
#define VOL_VALIDATOR

#include "helpers.hh"
#include "general_validators.hh"

/**
 * @brief Checks if a file section starting with "Volume" is a validly formatted .csr volume
 * 
 * @param[in]       _file          The file being validated
 * @param[in]       _mediums       A vector of mediums to be checked
 * @param[in]       _primitives    A vector of all valid typed primitives' ids (e.g Sphere, but not Quad)
 * @param[in, out]  _volumes       A vector of volumes to be updated if the volume is valid
 * 
 * @note exits if volume is invalid
 */
void isVolume(std::ifstream& _file, const std::vector<std::string>& _mediums, const std::vector<std::string>& _primitives, std::vector<std::string>& _volumes);

#endif