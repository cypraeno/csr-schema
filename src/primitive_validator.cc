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

void isBox(std::ifstream& _file, const std::vector<std::string>& _materials, std::vector<std::string>& _boxes) {
    
    std::string id, material;
    xyz position, a, b, c;
    
    // Check for valid ID
    if (isMember(_file, "id", _boxes, id)) outputError("Error: box id taken", exitCode::ID_TAKEN);

    // Check for valid position
    isXYZ(_file, "position", N_INF, P_INF, position);

    // Check for valid a
    isXYZ(_file, "a", N_INF, P_INF, a);

    // Check for valid b
    isXYZ(_file, "b", N_INF, P_INF, b);

    // Check for valid c
    isXYZ(_file, "c", N_INF, P_INF, c);

    // Check for valid material
    if (!isMember(_file, "material", _materials, material)) outputError("Error: Unknown material id", exitCode::UNKNOWN_ID);

    // Success
    _boxes.push_back(id);
}