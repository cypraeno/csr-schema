#include "primitive_validator.hh"

void isQuad(std::ifstream& _file, const std::vector<std::string>& _materials, std::vector<std::string>& _quads) {

    std::string id, material;
    xyz position, u, v;
    
    // Check for valid ID
    if (isMember(_file, "id", _quads, id)) outputError("Error: quad id taken", exitCode::ID_TAKEN);

    // Check for valid position
    isXYZ(_file, "position", N_INF, P_INF, position);

    // Check for valid u
    isXYZ(_file, "u", N_INF, P_INF, u);

    // Check for valid v
    isXYZ(_file, "v", N_INF, P_INF, v);

    // Check for valid material
    if (!isMember(_file, "material", _materials, material)) outputError("Error: Unknown material id", exitCode::UNKNOWN_ID);

    // Success
    _quads.push_back(id);
}

void isSphere(std::ifstream& _file, const std::vector<std::string>& _materials, std::vector<std::string>& _spheres) {

    std::string id, material;
    xyz position;
    double radius;

    // Check for valid ID
    if (isMember(_file, "id", _spheres, id)) outputError("Error: sphere id taken", exitCode::ID_TAKEN);
    
    // Check for valid position
    isXYZ(_file, "position", N_INF, P_INF, position);

    // Check for valid material
    if (!isMember(_file, "material", _materials, material)) outputError("Error: Unknown material id", exitCode::UNKNOWN_ID);

    // Check for valid radius
    isDouble(_file, "radius", 0.0, P_INF, radius);

    // Success
    _spheres.push_back(id);
}
