#include "primitive_validator.hh"

struct vec3 { double x, y, z; };

bool isQuad(std::ifstream& _file, std::vector<std::string>& _materials, std::vector<std::string>& _quads) {
    
    std::string line, keyword;
    std::stringstream ss;
    
    // Check for valid position
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isXYZ(ss, "position", N_INF, P_INF)) return false;

    // Check for valid ID
    std::string id;
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isId(ss, id)) return outputError("Error: Expected id");

    // Check for valid u
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isXYZ(ss, "u", N_INF, P_INF)) return false;
    vec3 u;
    ss << line;
    ss >> u.x >> u.y >> u.z;

    resetsstream(ss);
    
    // Check for valid v
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isXYZ(ss, "v", N_INF, P_INF)) return false;
    vec3 v;
    ss << line;
    ss >> v.x >> v.y >> v.z;

    resetsstream(ss);

    // Check valid uv orthogonality
    if (u.x*v.x + u.y*v.y + u.z*v.z != 0.0) return outputError("Error: uv not orthogonal");

    // Check for valid material
    std::string material;
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !(ss >> keyword) || keyword != "material") return outputError("Error: Expected material");
    if (!(ss >> material)) return outputError("Error: No material id found");
    if (material != "no") {
        auto it = std::find(_materials.begin(), _materials.end(), material);
        if (it == _materials.end()) return outputError("Error: Invalid material id");
    }
    resetsstream(ss);

    // Success
    _quads.push_back(id);
    return true;
}

bool isSphere(std::ifstream& _file, std::vector<std::string>& _materials, std::vector<std::string>& _spheres) {

    std::string line, keyword;
    std::stringstream ss;

    // Check for valid ID
    std::string id;
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isId(ss, id)) return outputError("Error: Expected id");
    
    // Check for valid position
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isXYZ(ss, "position", N_INF, P_INF)) return false;

    // Check for valid material
    std::string material;
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !(ss >> keyword) || keyword != "material") return outputError("Error: Expected material");
    if (!(ss >> material)) return outputError("Error: No material id found");
    if (material != "no") {
        auto it = std::find(_materials.begin(), _materials.end(), material);
        if (it == _materials.end()) return outputError("Error: Invalid material id");
    }
    resetsstream(ss);

    // Check for valid radius
    if (!getCSRLine(_file, line)) return outputError("Error: Unexpected EOF");
    if (!(ss << line) || !isDouble(ss, "radius", 0.0, P_INF)) return false;

    // Success
    _spheres.push_back(id);
    return true;
}
