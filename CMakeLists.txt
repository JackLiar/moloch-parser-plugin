cmake_minimum_required(VERSION 3.13)
project(moloch-parser-plugins VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(projects)
include(functions)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/parsers)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/plugins)

include(packaging)

message(STATUS "")
message(STATUS "")
message(STATUS "Project configure summary:")
message(STATUS "CMake build type .................: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix ...................: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Packaging generator ..............: ${CPACK_GENERATOR}")
message(STATUS "")

include(CPack)
