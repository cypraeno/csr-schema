cmake_minimum_required(VERSION 3.26) # Required
project(CSRValidator VERSION 0.1.0)


add_executable(csr_validator 
               helpers.cc 
               general_validators.cc 
               texture_validator.cc 
               material_validator.cc 
               primitive_validator.cc
               csr_validator.cc)

target_compile_features(csr_validator PUBLIC cxx_std_11)