#include "material_validator.h"

using materialValidatorFunction = std::function<bool(std::ifstream&, std::vector<std::string>&)>;

// Forward declarations
bool isDielectric(std::ifstream& _file, std::vector<std::string>& _textures);
bool isEmissive(std::ifstream& _file, std::vector<std::string>& _textures);
bool isLambertian(std::ifstream& _file, std::vector<std::string>& _textures);
bool isMetal(std::ifstream& _file, std::vector<std::string>& _textures);

// UPDATE this list as new materials are defined
std::map<std::string, materialValidatorFunction> materialValidatorMap {
    { "[Dielectric]", isDielectric },
    { "[Emissive]", isEmissive },
    { "[Lambertian]", isLambertian },
    { "[Metal]", isMetal },
};

bool isMaterial(std::ifstream& _file, std::string& _material_type, std::vector<std::string>& _textures, std::vector<std::string>& _materials) {

    // Check for valid material type
    auto matIt = materialValidatorMap.find(_material_type);
    if (matIt == materialValidatorMap.end()) outputError("Error: Unknown material type: " + _material_type);

    std::string _line, id;
    
    // Check for valid ID
    if (!std::getline(_file, _line)) return outputError("Error: Unexpected EOF");
    if (!isId(_line, id)) return outputError("Error: Expected id");

    // Success
    if (matIt->second(_file, _textures)) {
        _materials.push_back(id);
        return true;
    }
}

bool isDielectric(std::ifstream& _file, std::vector<std::string>& _textures) {
    
    std::string line, keyword;
    std::istringstream iss;

    // Check for valid IR
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");
    
    iss.str(line);
    if (!(iss >> keyword) || keyword != "ir") return outputError("Error: Expected ir");

    double ir;
    if (!(iss >> ir)) return outputError("Error: Invalid ir value type");
    if (ir < 1) return outputError("Error: ir value not in range");

    // Success
    return true;
}

bool isEmissive(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line, keyword;
    std::istringstream iss;

    // Check for valid RGB
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!(iss >> keyword) || keyword != "rgb") return outputError("Error: Expected rgb");

    double r, g, b;
    if (!(iss >> r >> g >> b)) return outputError("Error: Invalid rgb value type");
    if (r < 0.0 || 255.0 < r) return outputError("Error: r value not in range");
    if (g < 0.0 || 255.0 < g) return outputError("Error: g value not in range");
    if (b < 0.0 || 255.0 < b) return outputError("Error: b value not in range");

    // Check for valid strength
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!(iss >> keyword) || keyword != "strength") return outputError("Error: Expected strength");

    double strength;
    if (!(iss >> strength)) return outputError("Error: Invalid strength value type");
    if (strength < 0.0) return outputError("Error: strength value not in range");

    // Success
    return true;
}

bool isLambertian(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line, keyword;
    std::istringstream iss;

    // Check for valid texture
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!(iss >> keyword) || keyword != "texture") return outputError("Error: Expected texture");

    std::string texture;
    if (!(iss >> texture)) return outputError("Error: No texture id found");
    if (texture != "no") {
        auto it = std::find(_textures.begin(), _textures.end(), texture);
        if (it == _textures.end()) return outputError("Error: Invalid texture id");
    }

    // Check for valid albedo
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!(iss >> keyword) || keyword != "albedo") return outputError("Error: Expected albedo");

    double r, g, b;
    if (!(iss >> r >> g >> b)) return outputError("Error: Invalid albedo value type");
    if (r < 0.0 || 255.0 < r) return outputError("Error: R value not in range");
    if (g < 0.0 || 255.0 < g) return outputError("Error: G value not in range");
    if (b < 0.0 || 255.0 < b) return outputError("Error: B value not in range");

    // Success
    return true;
}

bool isMetal(std::ifstream& _file, std::vector<std::string>& _textures) {

    std::string line, keyword;
    std::istringstream iss;

    // Check for valid albedo
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!(iss >> keyword) || keyword != "albedo") return outputError("Error: Expected albedo");

    double r, g, b;
    if (!(iss >> r >> g >> b)) return outputError("Error: Invalid albedo value type");
    if (r < 0.0 || 255.0 < r) return outputError("Error: R value not in range");
    if (g < 0.0 || 255.0 < g) return outputError("Error: G value not in range");
    if (b < 0.0 || 255.0 < b) return outputError("Error: B value not in range");

    // Check for valid fuzz
    if (!std::getline(_file, line)) return outputError("Error: Unexpected EOF");

    iss.str(line);
    if (!(iss >> keyword) || keyword != "fuzz") return outputError("Error: Expected fuzz");

    double fuzz;
    if (!(iss >> fuzz)) return outputError("Error: Invalid fuzz value type");
    if (fuzz < 0.0) return outputError("Error: fuzz value not in range");

    // Success
    return true;
}
