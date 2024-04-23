#include "helpers.hh"

int lineNum = 0;

bool isComment(const std::string& _line) {

    // Check if the first non-whitespace character is '#'
    for (char ch : _line) {
        if (std::isspace(ch)) continue; // Skip whitespace
        return ch == '#';
    }
    return false;
}

void outputError(const std::string& _error, const exitCode _code) {
    if (lineNum != 0) std::cerr << lineNum << " - ";
    std::cerr << _error << std::endl;
    std::exit(static_cast<int>(_code));
}

std::istream& getCSRLine(std::istream& _istream, std::string& _line) {

    std::string output = "";

    while((isComment(output) || output.empty()) && std::getline(_istream, output)) ++lineNum;
    if (!std::cin.fail()) _line = output;

    return _istream;
}

 void getType(const std::string& _header, std::string& _type) {

    size_t start_pos = _header.find_first_of('[');
    if (start_pos == std::string::npos) outputError("Error: type indicator <<[>> missing", exitCode::BAD_INPUT);

    size_t end_pos = _header.find_first_of(']', start_pos);
    if (end_pos == std::string::npos) outputError("Error: type indicator <<]>> missing", exitCode::BAD_INPUT);

    _type = _header.substr(start_pos, end_pos - start_pos + 1);
}
