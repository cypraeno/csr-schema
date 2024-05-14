cmake_minimum_required(VERSION 3.26)

project(CSRValidator VERSION 0.1.5)

# Let users or the build system specify the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Definitions
file(GLOB_RECURSE SOURCE_FILES "src/*.cc")
file(GLOB_RECURSE HEADER_FILES "include/*.hh")
set(INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(TARGET csr-validator)
    set(SCOPE PRIVATE)
    add_executable(${TARGET} ${SOURCE_FILES} ${HEADER_FILES})
    target_compile_definitions(${TARGET} ${SCOPE} INCLUDE_MAIN)
else()
    set(TARGET csr-schema-lib)
    set(SCOPE PUBLIC)
    add_library(${TARGET} STATIC ${SOURCE_FILES} ${HEADER_FILES})
endif()

target_include_directories(${TARGET} ${SCOPE} ${INCLUDE_DIRECTORY})
target_compile_features(${TARGET} PUBLIC cxx_std_11)
target_compile_options(${TARGET} ${SCOPE} -O2)
