#ifndef GEN_VALIDATOR
#define GEN_VALIDATOR

#include "helpers.hh"
#include <experimental/filesystem>

/**
 * @brief Checks if a file line is a valid CSR file path of one of the specified file types
 * 
 * @param[in] _ss           The line being evaluated
 * @param[in] _fileTypes    The list of valid file types
 * 
 * @return true if the string is a valid file path and type
 *         false otherwise
 * 
 */
bool isFilePath(std::stringstream& _ss, const std::vector<std::string>& _fileTypes);

/**
 * @brief Checks if a file line is a valid double between min and max
 * 
 * @param[in] _ss           The line being evaluated
 * @param[in] _keyword      The keyword that the line must start with
 * @param[in] _min, _max    The min and max of the double
 * 
 * @return true if line is a valid double between min and max
 *         false otherwise
 */
bool isDouble(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max);

/**
 * @brief Checks if a file line is a set of three valid doubles between min and max
 * 
 * @param[in] _ss           The line being evaluated
 * @param[in] _keyword      The keyword that the line must start with
 * @param[in] _min, _max    The min and max of the doubles
 * 
 * @return true if line is a set of three valid doubles between min and max
 *         false otherwise
 */
bool isXYZ(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max);

/**
 * @brief Checks if a file line is a valid ratio that has a value between min and max
 * 
 * @param _ss               The line being evaluated
 * @param[in] _keyword      The keyword that the line must start with
 * @param[in] _min, _max    The min and max of the ratio
 * 
 * @return true if line is a valid ratio between min and max (e.g. 16/9)
 *         false otherwise
 */
bool isRatio(std::stringstream& _ss, const std::string& _keyword, const double _min, const double _max);

/**
 * @brief Checks if a file line is a valid version
 * 
 * @param[in] _ss The line being evaluated
 * 
 * @return true if line is a valid version
 *         false otherwise
 */
bool isVersion(std::stringstream& _ss);

/**
 * @brief Checks if a file line contains a member of the provided vector, and assigns _member that value whether it is/is not
 * 
 * @param[in]   _ss         The line being evaluated
 * @param[in]   _keyword    The keyword that the line must start with
 * @param[in]   _members    The vector of members to be checked against
 * @param[out]  _member     The string to assign the member to
 * 
 * @return true if line is a valid member
 *         false otherwise 
 */
bool isMember(std::stringstream& _ss, const std::string& _keyword, const std::vector<std::string>& _members, std::string& _member);

#endif
