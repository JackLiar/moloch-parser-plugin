# ================================
# parser specific configurations
# ================================

add_moloch_parser(parser)
set_property(TARGET parser APPEND PROPERTY 
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/parser.cc
)
target_link_libraries(parser PRIVATE utils)
