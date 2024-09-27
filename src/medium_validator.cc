#include "medium_validator.hh"

void isMedium(std::ifstream& _file, std::vector<std::string>& _mediums) {
    std::string id;
    double density;
    xyz albedo;

    // Check for valid ID
    if (isMember(_file, "id", _mediums, id)) outputError("Error: material id taken", exitCode::ID_TAKEN);

    // Check for valid density
    isDouble(_file, "density", 0.0, P_INF, density);

    // Check for valid albedo
    isXYZ(_file, "albedo", 0.0, 255.0, albedo);

    _mediums.push_back(id);
}