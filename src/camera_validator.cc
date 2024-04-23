#include "camera_validator.hh"

void isCamera(std::ifstream& _file) {

    xyz lookfrom, lookat, vup;
    double vfov, aperture, focus_dist;
    ratio aspect_ratio;
    
    isXYZ(_file, "lookfrom", N_INF, P_INF, lookfrom);           // Check for valid lookfrom
    isXYZ(_file, "lookat", N_INF, P_INF, lookat);               // Check for valid lookat
    isXYZ(_file, "vup", N_INF, P_INF, vup);                     // Check for valid vup
    isDouble(_file, "vfov", 0.0, 360.0, vfov);                  // Check for valid vfov
    isRatio(_file, "aspect_ratio", 0.0, P_INF, aspect_ratio);   // Check for valid aspect ratio
    isDouble(_file, "aperture", 0.0, P_INF, aperture);          // Check for valid aperture
    isDouble(_file, "focus_dist", N_INF, P_INF, focus_dist);    // Check for valid focus dist
}
