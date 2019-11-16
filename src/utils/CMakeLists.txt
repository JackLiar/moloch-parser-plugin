set(utils_src
    ${CMAKE_CURRENT_SOURCE_DIR}/ch++.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/ch++.h
    ${CMAKE_CURRENT_SOURCE_DIR}/hs++.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/hs++.h
)
add_library(utils OBJECT ${utils_src})
add_dependencies(utils libhs)
target_link_libraries(utils
    PUBLIC -Wl,--whole-archive chimera -Wl,--no-whole-archive hs pcre
)

moloch_set_target_properties(utils)

install(FILES
    ${CMAKE_BINARY_DIR}/install/lib/libpcre.so
    ${CMAKE_BINARY_DIR}/install/lib/libhs.so
    ${CMAKE_BINARY_DIR}/install/lib/libhs.so.5
    ${CMAKE_BINARY_DIR}/install/lib/libhs.so.5.2.1
    DESTINATION lib
)
