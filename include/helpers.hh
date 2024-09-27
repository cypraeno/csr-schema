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
#include <cstdlib>

// Constants
const std::string CURRENT_VERSION = "0.1.5";                    /**< Version accepted by validator */
const double P_INF = std::numeric_limits<double>::infinity();   /**< Positive infinity */
const double N_INF = -std::numeric_limits<double>::infinity();  /**< Negative infinity */

/**
 * @brief The exit codes for various fail cases
 */
enum class exitCode : int {
    MISSING_ARG = 1,
    INCORRECT_ARG = 2,
    NO_INPUT = 3,
    BAD_INPUT = 4,
    UNKNOWN_INPUT = 5,
    ID_TAKEN = 6,
    UNKNOWN_ID = 7,
    FILE_ERROR = 8,
};

// Structs
struct xyz      { double x, y, z; };        /**< Implementation of struct to store a set of three doubles */
struct ratio    { double num, denom; };     /**< Implementation of struct to store ratios */

/**
 * @brief Wrapper function that outputs error to stderr stream and exits with the provided exit code
 * 
 * @param[in] _error The error string to be outputted
 * @param[in] _code  The exit code used for exit
 */
void outputError(const std::string& _error, const exitCode _code);

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
 * @note The type is the text between "[]". "Material[Diffuse]" has "Diffuse" as its type
 */
 void getType(const std::string& _header, std::string& _type);

#endif
