#ifndef CAM_VALIDATOR
#define CAM_VALIDATOR

#include "helpers.hh"
#include "general_validators.hh"

/**
 * @brief Checks if file camera is valdily formatted
 * 
 * @param[in]   _file   The file being validated
 * 
 * @note throws std::invalid_arguemnt error if camera is invalid
 */
void isCamera(std::ifstream& _file);

#endif
