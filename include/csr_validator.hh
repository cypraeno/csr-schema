#ifndef CSR_VALIDATOR
#define CSR_VALIDATOR

#include "helpers.hh"
#include "camera_validator.hh"
#include "texture_validator.hh"
#include "material_validator.hh"
#include "primitive_validator.hh"
#include "instance_validator.hh"
#include "sky_validator.hh"
#include "medium_validator.hh"

/**
 * @brief Checks if a CSR file is correctly formatted
 * 
 * @param[in]   _file   The path of the file
 * 
 * @note exits if CSR file is invalid
 */
void isCSR(std::string& _file);

#endif
