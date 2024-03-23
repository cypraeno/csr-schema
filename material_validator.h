#ifndef MAT_VALIDATOR
#define MAT_VALIDATOR
#include "helpers.h"

/**
 * @brief List of available material types (updated regularily)
 */
const enum material_types {
    DIELECTRIC,
    EMISSIVE,
    LAMBERTIAN,
    METAL,
};

/**
 * @brief Checks if a file section starting with "Material" is a validly formatted .csr material
 * 
 * @param[in]   _file           the file being validated
 * @param[in]   _material_type  the type of material being validated
 * @param[in]   _textures       a vector of textures to be checked (lambertian surfaces)
 * @param[out]  _materials      a vector of materials to be updated if the material is valid
 * @return true if the material is correctly formatted
 *         false otherwise
 */
bool isMaterial(std::ifstream& _file, std::string& _material_type, std::vector<std::string>& _textures, std::vector<std::string>& _materials);

#endif
