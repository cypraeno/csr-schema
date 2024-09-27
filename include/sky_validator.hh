#ifndef SKY_VALIDATOR
#define SKY_VALIDATOR

#include "helpers.hh"
#include "general_validators.hh"

/**
 * @brief Checks if a file section starting with "Sky" is a validly structured sky specification.
 * 
 * @note exits if Sky section is invalid
 */
void isSky(std::ifstream& _file);

#endif