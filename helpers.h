#ifndef HELPERS
#define HELPERS

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

#endif
