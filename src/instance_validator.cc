#include "instance_validator.hh"

void isInstance(std::ifstream& _file, const std::string& _instanceType, const std::map<std::string, std::vector<std::string>>& _primitiveMap) {

    std::string id;
    xyz translate;

    // Check for valid instance type
    auto insIt = _primitiveMap.find(_instanceType);
    if (insIt == _primitiveMap.end()) outputError("Error: Unknown instance type: " + _instanceType, exitCode::UNKNOWN_INPUT);

    // Check for valid prim_id
    if (!isMember(_file, "prim_id", insIt->second, id))  outputError("Error: Unknown prim_id", exitCode::UNKNOWN_ID);

    // Check for valid translate
    isXYZ(_file, "translate", N_INF, P_INF, translate);
}
