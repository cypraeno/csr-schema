#include "helpers.hh"

int lineNum = 0;

std::string trim(const std::string& _str) {
    std::string whitespace = " \t\r\n"; // Include carriage return and tab
    size_t first = _str.find_first_not_of(whitespace);
    if (first == std::string::npos) return "";
    size_t last = _str.find_last_not_of(whitespace);
    return _str.substr(first, (last - first + 1));
}

bool isComment(const std::string& _line) {
    // Check if the first non-whitespace character is '#'
    for (char ch : _line) {
        if (std::isspace(ch)) continue; // Skip whitespace
        return ch == '#';
    }
    return false;
}

void outputError(const std::string& _error) {
    throw std::invalid_argument(lineNum + " - " + _error);
}

std::istream& getCSRLine(std::istream& _istream, std::string& _line) {
    std::string _output, output;

    output = "";

    while((isComment(output) || output.empty()) && std::getline(_istream, _output)) {
        output = trim(_output);
        ++lineNum;
    }
    if (!std::cin.fail()) _line = output;

    return _istream;
}

std::string& getType(const std::string& _header) {
    size_t start_pos = _header.find_first_of('[');
    if (start_pos == std::string::npos) outputError("Error: Material type indicator <<[>> missing");

    size_t end_pos = _header.find_first_of(']', start_pos);
    if (end_pos == std::string::npos) outputError("Error: Material type indicator <<]>> missing");

    std::string type = _header.substr(start_pos, end_pos - start_pos + 1);
    return type;
}

void resetsstream(std::stringstream& _ss) {
    _ss.str(""); // Clear contents
    _ss.clear(); // Reset internal state flags
    _ss.seekg(0); // Reset read position
    _ss.seekp(0); // Reset write position
}
