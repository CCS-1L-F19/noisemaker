cmake_minimum_required (VERSION 3.8)

project ("Noisemaker")

set(CMAKE_BUILD_TYPE Debug)
option(BUILD_DOCS "Build Docuentation" OFF)

# Add the cmake folder so the FindSphinx module is found
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory ("src")
add_subdirectory ("tests")

if (BUILD_DOCS)
    add_subdirectory ("docs")
endif()
