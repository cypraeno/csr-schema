#include "primitive_validator.hh"

struct vec3 {
    std::string name;
    double x, y, z; 
};

bool isQuad(std::ifstream& _file, std::vector<std::string>& _materials, std::vector<std::string>& _quads) {
    
    std::string line;
    std::stringstream ss;
    
    // Check for valid ID
    std::string id;
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    if (isMember(ss, "id", _quads, id)) outputError("Error: quad id taken");

    // Check for valid position
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "position", N_INF, P_INF);

    // Check for valid u
    vec3 u;
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "u", N_INF, P_INF);
    ss << line;
    ss >> u.name >> u.x >> u.y >> u.z;

    resetsstream(ss);
    
    // Check for valid v
    vec3 v;
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "v", N_INF, P_INF);
    ss << line;
    ss >> v.name >> v.x >> v.y >> v.z;

    resetsstream(ss);

    // Check valid uv orthogonality
    if (u.x*v.x + u.y*v.y + u.z*v.z != 0.0) outputError("Error: uv not orthogonal");

    // Check for valid material
    std::string material;
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    if (!isMember(ss, "material", _materials, material)) outputError("Error: Unknown material id");

    // Success
    _quads.push_back(id);
    return true;
}

bool isSphere(std::ifstream& _file, std::vector<std::string>& _materials, std::vector<std::string>& _spheres) {

    std::string line, keyword;
    std::stringstream ss;

    // Check for valid ID
    std::string id;
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    if (isMember(ss, "id", _spheres, id)) outputError("Error: sphere id taken");
    
    // Check for valid position
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isXYZ(ss, "position", N_INF, P_INF);

    // Check for valid material
    std::string material;
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    if (!isMember(ss, "material", _materials, material)) outputError("Error: Unknown material id");
    
    resetsstream(ss);

    // Check for valid radius
    if (!getCSRLine(_file, line) || !(ss << line)) outputError("Error: Unexpected EOF");
    isDouble(ss, "radius", 0.0, P_INF);

    // Success
    _spheres.push_back(id);
    return true;
}
