#include "helpers.h"

std::string trim(const std::string& str) {
    std::string whitespace = " \t\r\n"; // Include carriage return and tab
    size_t first = str.find_first_not_of(whitespace);
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, (last - first + 1));
}

bool isComment(const std::string& line) {
    // Check if the first non-whitespace character is '#'
    for (char ch : line) {
        if (std::isspace(ch)) continue; // Skip whitespace
        return ch == '#';
    }
    return false;
}