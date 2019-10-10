function(moloch_set_target_properties target)
    set_target_properties(${target} PROPERTIES
        CXX_STANDARD 11
        C_STANDARD 99
        PREFIX ""
        POSITION_INDEPENDENT_CODE ON
    )
    target_compile_options(${target}
        PUBLIC -DMOLOCH_USE_MALLOC -fno-common -fsanitize=address
        PUBLIC $<$<COMPILE_LANGUAGE:C>:-fsanitize=integer>
        PUBLIC $<$<COMPILE_LANGUAGE:C>:-fsanitize=nullability>
        PUBLIC -Wall -Wextra -DGNU_SOURCE -fno-strict-aliasing
        PUBLIC -fvisibility=hidden -Bsymbolic
    )
    target_include_directories(${target}
        PRIVATE /data/moloch/include
        PRIVATE ${CMAKE_SOURCE_DIR}/src
        PRIVATE ${CMAKE_BINARY_DIR}/install/include
        PRIVATE ${CMAKE_BINARY_DIR}/install/include/glib-2.0
        PUBLIC ${CMAKE_BINARY_DIR}/install/lib/glib-2.0/include
    )
    target_link_directories(${target}
        PRIVATE ${CMAKE_BINARY_DIR}/install/lib
        PRIVATE ${CMAKE_BINARY_DIR}/install/lib64
    )
endfunction()

function(add_moloch_parser parser_name)
    set(parser_src
        ${CMAKE_CURRENT_SOURCE_DIR}/${parser_name}.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/parser.h
    )
    add_library(${parser_name} SHARED ${parser_src})
    add_dependencies(${parser_name} libglib)

    moloch_set_target_properties(${parser_name})

    install(TARGETS ${parser_name}
        LIBRARY DESTINATION parsers COMPONENT "parser-${parser_name}"
    )
endfunction()

function(add_moloch_plugin plugin_name)
    set(parser_src
        ${CMAKE_CURRENT_SOURCE_DIR}/${plugin_name}.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/plugin.h
    )
    add_library(${plugin_name} SHARED ${parser_src})
    add_dependencies(${plugin_name} libglib)

    moloch_set_target_properties(${plugin_name})

    install(TARGETS ${plugin_name}
        LIBRARY DESTINATION plugins COMPONENT "parser-${plugin_name}"
    )
endfunction()
