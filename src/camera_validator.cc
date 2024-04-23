#include "camera_validator.hh"

void isCamera(std::ifstream& _file) {

    std::string line;
    std::stringstream ss;

    // Check for valid lookfrom
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    isXYZ(ss, "lookfrom", N_INF, P_INF);

    // Check for valid lookat
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    isXYZ(ss, "lookat", N_INF, P_INF);

    // Check for valid vup
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    isXYZ(ss, "vup", N_INF, P_INF);

    // Check for valid vfov
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    isDouble(ss, "vfov", 0.0, 360.0);

    // Check for valid aspect ratio
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    isRatio(ss, "aspect_ratio", 0.0, P_INF);

    // Check for valid aperture
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    isDouble(ss, "aperture", 0.0, P_INF);

    // Check for valid focus dist
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF", exitCode::NO_INPUT);
    isDouble(ss, "focus_dist", N_INF, P_INF);
}
