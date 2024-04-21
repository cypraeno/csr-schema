#ifndef CAM_VALIDATOR
#define CAM_VALIDATOR

#include "helpers.hh"
#include "general_validators.hh"

/**
 * @brief Checks if file camera is valdily formatted
 * 
 * @param[in]   _file The file being validated
 * 
 * @return true if the camera is correctly formatted
 *         false otherwise
 */
bool isCamera(std::ifstream& _file);

#endif
