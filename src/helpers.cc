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

bool outputError(const std::string& _error) {
    std::cerr << lineNum << " - " << _error << std::endl;
    return false;
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

void resetsstream(std::stringstream& _ss) {
    _ss.str(""); // Clear contents
    _ss.clear(); // Reset internal state flags
    _ss.seekg(0); // Reset read position
    _ss.seekp(0); // Reset write position
}
