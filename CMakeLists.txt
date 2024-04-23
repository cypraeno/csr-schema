cmake_minimum_required(VERSION 3.26) # Required

project(CSRValidator VERSION 0.1.3)
set(CMAKE_BUILD_TYPE Debug)

# Define source files
file(GLOB_RECURSE LIBRARY_SOURCES "src/*.cc")
file(GLOB_RECURSE LIBRARY_HEADERS "include/*.hh")

# Create library target
add_library(csr-schema-lib STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

# Set C++ standard
target_compile_features(csr-schema-lib PUBLIC cxx_std_11)

# Include directories
target_include_directories(csr-schema-lib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Define source files for the executable
file(GLOB_RECURSE EXECUTABLE_SOURCES "src/*.cc")

# Create executable target
add_executable(csr_validator ${EXECUTABLE_SOURCES})
target_include_directories(csr_validator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set C++ standard for the executable
target_compile_features(csr_validator PUBLIC cxx_std_11)
target_compile_definitions(csr_validator PRIVATE INCLUDE_MAIN)

# Set optimization level for the executable
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Instructions
# Create build files:
# mkdir build (if it does not exist already)
# cmake -B build/ -S (DIRECTORY TO CMakeLists.txt)
# Within build/, CMake files have set up the "make" command:
# make
