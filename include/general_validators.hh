#ifndef GEN_VALIDATOR
#define GEN_VALIDATOR

#include "helpers.hh"
#include <experimental/filesystem>

/**
 * @brief Checks if a file line is a valid id, and assign the id if it is
 * 
 * @param[in]   _ss     The line being evaluated
 * @param[in]   _ids    The vector of IDs that have already been takens
 * @param[out]  _id     The id being assigned
 * 
 * @return true if id is valid
 *         false otherwise
 */
bool isId(std::stringstream& _ss, std::vector<std::string>& _ids, std::string& _id);

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

// WIP need to consider abstraction when there is special cases (i.e. texture cannot have "no" as an id)
// bool isMember(std::stringstream& _ss, const std::string& _keyword, std::vector<std::string>& _members);

#endif
