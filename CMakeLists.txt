cmake_minimum_required(VERSION 3.26) # Required
project(CSRValidator VERSION 0.1.0)


add_executable(csr_validator csr_validator.cpp)

target_compile_features(csr_validator PUBLIC cxx_std_11)