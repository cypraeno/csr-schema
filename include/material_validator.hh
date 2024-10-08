#ifndef MAT_VALIDATOR
#define MAT_VALIDATOR

#include "helpers.hh"
#include "general_validators.hh"

/**
 * @brief Checks if a file section starting with "Material" is a validly formatted .csr material
 * 
 * @param[in]       _file           The file being validated
 * @param[in]       _materialType   The type of material being validated
 * @param[in]       _textures       A vector of textures to be checked (diffuse surfaces)
 * @param[in, out]  _materials      A vector of materials to be updated if the material is valid
 * 
 * @note exits if material is invalid
 */
void isMaterial(std::ifstream& _file, const std::string& _materialType, const std::vector<std::string>& _textures, std::vector<std::string>& _materials, std::vector<std::string>& _mediums);

#endif
