#ifndef TEX_VALIDATOR
#define TEX_VALIDATOR

#include "helpers.h"
#include "general_validators.h"

/**
 * @brief List of available texture types (updated regularily)
 */
const enum texture_types {
    CHECKER,
    IMAGE,
};

/**
 * @brief Checks if a file section starting with "Texture" is a validly formatted .csr texture
 * 
 * @param[in]   _file             the file being validated
 * @param[in]   _material_type    the type of texture being validated
 * @param[out]  _textures         a vector of textures to be updated if the texture is valid
 * 
 * @return true if the texture is correctly formatted 
 *         false otherwise
 */
bool isTexture(std::ifstream& _file, std::string& _texture_type, std::vector<std::string>& _textures);

#endif
