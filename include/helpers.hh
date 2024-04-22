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
#include <stdexcept>

// Constants
const double P_INF = std::numeric_limits<double>::infinity();
const double N_INF = -std::numeric_limits<double>::infinity();

/**
 * @brief Wrapper function that throws the error passed through as an std::invalid_arguement error
 * 
 * @param[in] _error The error string to be thrown
 */
void outputError(const std::string& _error);

/**
 * @brief Gets the next line that is non-empty and not a comment, and trims it
 * 
 * @param[in]   _istream    The input stream
 * @param[out]  _line       The string being written to
 * 
 * @return A reference to _istream
 */
std::istream& getCSRLine(std::istream& _istream, std::string& _line);

/**
 * @brief Gets the [type] from a header
 * 
 * @param[in]   _header The string from which the type is extracted 
 * @param[out]  _type   The string to assign the type to
 * 
 * @note The type is the text between "[]". "Material[Lambertian]" has "Lambertian" as its type
 */
 void getType(const std::string& _header, std::string& _type);

/**
 * @brief Resets a stringstream (wipes content ) so that it can be reused
 * 
 * @param[out] _ss The stringstream being reset
 * 
 * @note function should be called before more lines are appended to the stream
 */
void resetsstream(std::stringstream& _ss);

#endif
