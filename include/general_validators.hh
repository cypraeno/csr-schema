#ifndef GEN_VALIDATOR
#define GEN_VALIDATOR

#include "helpers.hh"

/**
 * @brief Checks if a file line is a valid CSR file path of one of the specified file types
 * 
 * @param[in]   _file             The file of the line being evaluated
 * @param[in]   _inputFileTypes   The list of valid file types
 * @param[out]  _path             The string to assign the file path to
 * 
 * @note throws std::invalid_arguemnt error if file path is invalid
 */
void isFilePath(std::ifstream& _file, const std::vector<std::string>& _inputFileTypes, std::string& _path);

/**
 * @brief Checks if a file line is a valid double between min and max
 * 
 * @param[in]   _file         The file of the line being evaluated
 * @param[in]   _keyword      The keyword that the line must start with
 * @param[in]   _min, _max    The min and max of the double
 * @param[out]  _value        The value to assign the double to
 * 
 * @note throws std::invalid_arguemnt error if double is invalid
 */
void isDouble(std::ifstream& _file, const std::string& _keyword, const double _min, const double _max, double& _value);

/**
 * @brief Checks if a file line is a set of three valid doubles between min and max
 * 
 * @param[in]   _file         The file of the line being evaluated
 * @param[in]   _keyword      The keyword that the line must start with
 * @param[in]   _min, _max    The min and max of the doubles
 * @param[out]  _xyz          The xyz to assign the three doubles to
 * 
 * @note throws std::invalid_arguemnt error if set of three doubles is invalid
 */
void isXYZ(std::ifstream& _file, const std::string& _keyword, const double _min, const double _max, xyz& _xyz);

/**
 * @brief Checks if a file line is a valid ratio that has a value between min and max
 * 
 * @param[in]   _file         The file of the line being evaluated
 * @param[in]   _keyword      The keyword that the line must start with
 * @param[in]   _min, _max    The min and max of the ratio
 * @param[out]  _ratio        The value to assign the ratio to
 * 
 * @note throws std::invalid_arguemnt error if ratio is invalid
 */
void isRatio(std::ifstream& _file, const std::string& _keyword, const double _min, const double _max, ratio& _ratio);

/**
 * @brief Checks if a file line is a valid version
 * 
 * @param[in]   _file       The file of the line being evaluated
 * @param[out]  _version    The string to assign the version to
 * 
 * @note throws std::invalid_arguemnt error if version is invalid
 */
void isVersion(std::ifstream& _file, std::string& _version);

/**
 * @brief Checks if a file line contains a member of the provided vector, and assigns _member that value
 * 
 * @param[in]   _file       The file of the line being evaluated
 * @param[in]   _keyword    The keyword that the line must start with
 * @param[in]   _members    The vector of members to be checked against
 * @param[out]  _member     The string to assign the member to
 * 
 * @return true if line member belongs to _members
 * 
 * @note throws std::invalid_arguemnt error if member is incorrectly formatted
 */
bool isMember(std::ifstream& _file, const std::string& _keyword, const std::vector<std::string>& _members, std::string& _member);

#endif
