#include "camera_validator.hh"

bool isCamera(std::ifstream& _file) {

    std::string line;
    std::stringstream ss;

    // Check for valid lookfrom
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isXYZ(ss, "lookfrom", N_INF, P_INF)) return false;

    // Check for valid lookat
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isXYZ(ss, "lookat", N_INF, P_INF)) return false;

    // Check for valid vup
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isXYZ(ss, "vup", N_INF, P_INF)) return false;

    // Check for valid vfov
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isDouble(ss, "vfov", 0.0, 360.0)) return false;

    // Check for valid aspect ratio
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isRatio(ss, "aspect_ratio", 0.0, P_INF)) return false;

    // Check for valid aperture
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isDouble(ss, "aperture", 0.0, P_INF)) return false;

    // Check for valid focus dist
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isDouble(ss, "focus_dist", N_INF, P_INF)) return false;

    // Success
    return true;
}
