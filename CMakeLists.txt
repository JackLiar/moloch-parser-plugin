cmake_minimum_required(VERSION 3.13)
project(moloch-parser-plugin VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(projects)
include(macros)
include(functions)

option(ENABLE_SANITIZE "" OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/utils)
# ================================
# add moloch parsers
# ================================
set(moloch_parsers parser)

foreach(parser_name IN LISTS moloch_parsers)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/parsers/${parser_name})
endforeach()

# ================================
# add moloch plugins
# ================================
set(moloch_plugins plugin)

foreach(plugin_name IN LISTS moloch_plugins)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/plugins/${plugin_name})
endforeach()

include(packaging)

print_configuration()

include(CPack)
