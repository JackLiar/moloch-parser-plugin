cmake_minimum_required(VERSION 3.13)
project(moloch-parser-plugins VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(projects)
include(macros)
include(functions)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/parsers)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/plugins)

include(packaging)

print_configuration()

include(CPack)
