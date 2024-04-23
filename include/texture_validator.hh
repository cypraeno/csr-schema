#ifndef TEX_VALIDATOR
#define TEX_VALIDATOR

#include "helpers.hh"
#include "general_validators.hh"

/**
 * @brief Checks if a file section starting with "Texture" is a validly formatted .csr texture
 * 
 * @param[in]   _file             the file being validated
 * @param[in]   _material_type    the type of texture being validated
 * @param[out]  _textures         a vector of textures to be updated if the texture is valid
 * 
 * @note exits if texture is invalid
 */
void isTexture(std::ifstream& _file, std::string& _texture_type, std::vector<std::string>& _textures);

#endif
