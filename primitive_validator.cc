#include "primitive_validator.h"

struct vec3 { double x, y, z; };

bool isQuad(std::ifstream& _file, std::vector<std::string>& _materials) {
    
    std::string line, keyword;
    std::istringstream iss;
    
    // Check for valid position
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isXYZ(iss, "position", N_INF, P_INF)) return false;

    // Check for valid u
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isXYZ(iss, "u", N_INF, P_INF)) return false;

    // Assign vector for validation
    iss.str(line);
    vec3 u;
    iss >> u.x >> u.y >> u.z;
    
    // Check for valid v
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!isXYZ(iss, "v", N_INF, P_INF)) return false;

    // Assign vector for validation
    iss.str(line);
    vec3 v;
    iss >> v.x >> v.y >> v.z;

    // Check valid uv orthogonality
    if (u.x*v.x + u.y*v.y + u.z*v.z != 0.0) return outputError("Error: uv not orthogonal");

    // Check for valid material
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!(iss >> keyword) || keyword != "material") return outputError("Error: Expected material");

    std::string material;
    if (!(iss >> material)) return outputError("Error: No material id found");
    if (material != "no") {
        auto it = std::find(_materials.begin(), _materials.end(), material);
        if (it == _materials.end()) return outputError("Error: Invalid material id");
    }

    // Success
    return true;
}
