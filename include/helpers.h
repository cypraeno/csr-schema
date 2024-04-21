#ifndef HELPERS
#define HELPERS

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <limits>

// Constants
const double P_INF = std::numeric_limits<double>::infinity();
const double N_INF = -std::numeric_limits<double>::infinity();

/**
 * @brief Trims a string of leading and trailing whitespace
 * 
 * @param[in] _str The string to be stripped
 * 
 * @return _str with whitespace removed
 * 
 * @note Whitespace is [" ", "\\t", "\\r", "\\n"]
 */
std::string trim(const std::string& _str);

/**
 * @brief Checks if a line in a .csr file is a comment
 * 
 * @param[in] line The line to be checked
 * 
 * @return true if line is a comment
 *         false otherwise
 * 
 * @note A line is a comment if the first non-whitespace character is "#"
 */
bool isComment(const std::string& _line);

/**
 * @brief Wrapper function that outputs the error passed through and returns false
 * 
 * @param[in] _error The error string to be output in std::err stream
 * 
 * @return false
 */
bool outputError(const std::string& _error);

/**
 * @brief Wrapper function to check if a line is a valid id, and assign the id if it is
 * 
 * @param[in]   _line The line being validatted
 * @param[out]  _id   The id being assigned
 * 
 * @return true if id is valid
 *         false otherwise
 */
bool isId(const std::string& _line, std::string& _id);

/**
 * @brief Gets the next line that is non-empty and not a comment, and trims it
 * 
 * @param[in]   _istream the input stream
 * @param[out]  _line the string being written to
 * 
 * @return A reference to _istream
 */
std::istream& getCSRLine(std::istream& _istream, std::string& _line);

/**
 * @brief Resets a stringstream (wipes content ) so that it can be reused
 * 
 * @param[out] _ss the stringstream being reset
 * 
 * @note function should be called before more lines are appended to the stream
 */
void resetsstream(std::stringstream& _ss);

#endif
