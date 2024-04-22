#ifndef PRI_VALIDATOR
#define PRI_VALIDATOR

#include "helpers.hh"
#include "general_validators.hh"

/**
 * @brief Checks if a file section starting with "Quad" is a validly formatted .csr quad
 * 
 * @param[in]   _file       The file being validated
 * @param[in]   _materials  A vector of materials to be checked
 * @param[out]  _quads      A vector of quad ids to be updated if the quad is valid
 * 
 * @note throws std::invalid_arguemnt error if quad is invalid
 */
void isQuad(std::ifstream& _file, std::vector<std::string>& _materials, std::vector<std::string>& _quads);

/**
 * @brief Checks if a file section starting with "Sphere" is a validly formatted .csr quad
 * 
 * @param[in]   _file       The file being validated
 * @param[in]   _materials  A vector of materials to be checked
 * @param[out]  _spheres    A vector of sphere ids to be updated if the quad is valid
 * 
 * @note throws std::invalid_arguemnt error if sphere is invalid
 */
void isSphere(std::ifstream& _file, std::vector<std::string>& _materials, std::vector<std::string>& _spheres);

#endif