#include "sky_validator.hh"

void isSky(std::ifstream& _file) {
    std::string top, bottom;
    xyz top_colour, bottom_colour;
    
    // Check for valid top
    isXYZ(_file, "top", 0.0, 1.0, top_colour);

    // Check for valid bottom
    isXYZ(_file, "bottom", 0.0, 1.0, bottom_colour);
}