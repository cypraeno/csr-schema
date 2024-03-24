#ifndef PRI_VALIDATOR
#define PRI_VALIDATOR

#include "helpers.h"
#include "general_validators.h"

/**
 * @brief Checks if a file section starting with "Quad" is a validly formatted .csr quad
 * 
 * @param[in] _file         The file being validated
 * @param[in] _materials    A vector of materials to be checked
 * @return true if the quad is correctly formatted
 *         false otherwise
 */
bool isQuad(std::ifstream& _file, std::vector<std::string>& _materials);

/**
 * @brief Checks if a file section starting with "Sphere" is a validly formatted .csr quad
 * 
 * @param[in] _file         The file being validated
 * @param[in] _materials    A vector of materials to be checked
 * @return true if the quad is correctly formatted
 *         false otherwise
 */
bool isSphere(std::ifstream& _file, std::vector<std::string>& _materials);

#endif
