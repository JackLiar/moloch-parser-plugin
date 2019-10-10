# ================================
# add moloch parsers
# ================================
set(moloch_parsers parser)

foreach(parser_name IN LISTS moloch_parsers)
    add_moloch_parser(${parser_name})
endforeach()

# ================================
# parser specific configurations
# ================================

target_link_libraries(parser utils)
