function(moloch_set_target_properties target)
    set(install_rpath_list
        ${CPACK_PACKAGING_INSTALL_PREFIX}/lib/${target}
        ${CPACK_PACKAGING_INSTALL_PREFIX}/lib64/${target}
    )
    set_target_properties(${target} PROPERTIES
        CXX_STANDARD 11
        C_STANDARD 99
        PREFIX ""
        POSITION_INDEPENDENT_CODE ON
        INSTALL_RPATH "${install_rpath_list}"
    )
    target_compile_options(${target}
        PUBLIC -DMOLOCH_USE_MALLOC -fno-common
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
    if(ENABLE_SANITIZE)
        target_compile_options(${target}
            PUBLIC -fsanitize=address
            PUBLIC $<$<COMPILE_LANGUAGE:C>:-fsanitize=integer>
            PUBLIC $<$<COMPILE_LANGUAGE:C>:-fsanitize=nullability>
        )
        target_link_libraries(${target}
            PRIVATE asan
        )
    endif()
endfunction()

function(add_moloch_parser_or_plugin target type)
    set(src_files
        ${CMAKE_CURRENT_SOURCE_DIR}/../${type}.h
    )
    add_library(${target} SHARED ${src_files})
    add_dependencies(${target} libglib)

    moloch_set_target_properties(${target})

    install(TARGETS ${target}
        LIBRARY DESTINATION "${type}s" COMPONENT "${type}-${target}"
    )
endfunction()

function(add_moloch_parser parser_name)
    add_moloch_parser_or_plugin(${parser_name} "parser")
endfunction()

function(add_moloch_plugin plugin_name)
    add_moloch_parser_or_plugin(${plugin_name} "plugin")
endfunction()

function(add_source_files target src_files)
    get_target_property(source target SOURCES)
    set(SOURCE ${SOURCE} ${src_files})
endfunction()
