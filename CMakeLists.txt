cmake_minimum_required(VERSION 3.26) # Required

project(CSRValidator VERSION 0.1.3)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SRC_FOLDER "src/*.cc")
list(APPEND SOURCES ${SRC_FOLDER})
add_executable(csr_validator ${SOURCES}) # Required

target_compile_features(csr_validator PUBLIC cxx_std_11) # Set the C++ standard to C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2") # Set the optimization level to -O2

target_include_directories(csr_validator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Instructions
# Create build files:
# mkdir build (if it does not exist already)
# cmake -B build/ -S (DIRECTORY TO CMakeLists.txt)
# Within build/, CMake files have set up the "make" command:
# make
