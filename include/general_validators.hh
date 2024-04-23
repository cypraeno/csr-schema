#ifndef GEN_VALIDATOR
#define GEN_VALIDATOR

#include "helpers.hh"

/**
 * @brief Checks if a file line is a valid CSR file path of one of the specified file types
 * 
 * @param[in] _ss           The line being evaluated
 * @param[in] _fileTypes    The list of valid file types
 * 
 * @note throws std::invalid_arguemnt error if file path is invalid
 */
void isFilePath(std::stringstream& _ss, const std::vector<std::string>& _fileTypes);

/**
 * @brief Checks if a file line is a valid double between min and max
 * 
 * @param[in] _ss           The line being evaluated
 * @param[in] _keyword      The keyword that the line must start with
 * @param[in] _min, _max    The min and max of the double
 * 
 * @note throws std::invalid_arguemnt error if double is invalid
 */
void isDouble(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max);

/**
 * @brief Checks if a file line is a set of three valid doubles between min and max
 * 
 * @param[in] _ss           The line being evaluated
 * @param[in] _keyword      The keyword that the line must start with
 * @param[in] _min, _max    The min and max of the doubles
 * 
 * @note throws std::invalid_arguemnt error if set of three doubles is invalid
 */
void isXYZ(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max);

/**
 * @brief Checks if a file line is a valid ratio that has a value between min and max
 * 
 * @param _ss               The line being evaluated
 * @param[in] _keyword      The keyword that the line must start with
 * @param[in] _min, _max    The min and max of the ratio
 * 
 * @note throws std::invalid_arguemnt error if ratio is invalid
 */
void isRatio(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max);

/**
 * @brief Checks if a file line is a valid version
 * 
 * @param[in] _ss The line being evaluated
 * 
 * @note throws std::invalid_arguemnt error if version is invalid
 */
void isVersion(std::stringstream& _ss, const std::string& _version);

/**
 * @brief Checks if a file line contains a member of the provided vector, and assigns _member that value
 * 
 * @param[in]   _ss         The line being evaluated
 * @param[in]   _keyword    The keyword that the line must start with
 * @param[in]   _members    The vector of members to be checked against
 * @param[out]  _member     The string to assign the member to
 * 
 * @return true if line member belongs to _members
 * 
 * @note throws std::invalid_arguemnt error if member is incorrectly formatted
 */
bool isMember(std::stringstream& _ss, const std::string& _keyword, const std::vector<std::string>& _members, std::string& _member);

#endif
