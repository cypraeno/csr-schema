#include "camera_validator.h"

bool isCamera(std::ifstream& _file) {

    std::string line;
    std::istringstream iss;

    // Check for valid lookfrom
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    iss.str(line);
    if (!isXYZ(iss, "lookfrom", N_INF, P_INF)) return false;

    // Check for valid lookat
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    iss.str(line);
    if (!isXYZ(iss, "lookat", N_INF, P_INF)) return false;

    // Check for valid vup
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    iss.str(line);
    if (!isXYZ(iss, "vup", N_INF, P_INF)) return false;

    // Check for valid vfov
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    iss.str(line);
    if (!isDouble(iss, "vfov", 0.0, 360.0)) return false;

    // Check for valid aspect ratio
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    iss.str(line);
    if (!isRatio(iss, "aperture", 0.0, P_INF)) return false;

    // Check for valid aperture
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    iss.str(line);
    if (!isDouble(iss, "aperture", 0.0, P_INF)) return false;

    // Check for valid focus dist
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    iss.str(line);
    if (!isDouble(iss, "focus_dist", N_INF, P_INF)) return false;

    // Success
    return true;
}
