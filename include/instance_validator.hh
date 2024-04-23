#ifndef INS_VALIDATOR
#define INS_VALIDATOR

#include "helpers.hh"
#include "general_validators.hh"

/**
 * @brief Checks if a file section starting with "Quad" is a validly formatted .csr quad
 * 
 * @param[in]   _file           The file being validated
 * @param[in]   _instanceType   The type of instance being validated
 * @param[in]   _primitiveMap   A map of vectors of primitives to be checked
 * 
 * @note exits if instance is invalid
 */
void isInstance(std::ifstream& _file, const std::string& _instanceType, const std::map<std::string, std::vector<std::string>>& _primitiveMap);

#endif
