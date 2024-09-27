#include "volume_validator.hh"

void isVolume(std::ifstream& _file, const std::vector<std::string>& _mediums, const std::vector<std::string>& _primitives, std::vector<std::string>& _volumes) {
    std::string id, medium_id, prim_id;

    // Check for valid ID
    if (isMember(_file, "id", _volumes, id)) outputError("Error: volume id taken", exitCode::ID_TAKEN);

    // Check for valid medium
    if (!isMember(_file, "medium_id", _mediums, medium_id)) outputError("Error: Unknown medium id", exitCode::UNKNOWN_ID);     
    
    // Check for valid medium
    if (!isMember(_file, "prim_id", _primitives, prim_id)) outputError("Error: Unknown primitive id (Only Spheres/Boxes!)", exitCode::UNKNOWN_ID);   

    _volumes.push_back(id);
}