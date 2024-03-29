set(ragel_url ${CMAKE_CURRENT_SOURCE_DIR}/third_party/ragel-6.9.tar.gz)

ExternalProject_Add(ragel
    URL ${ragel_url}
    EXCLUDE_FROM_ALL ON
    PREFIX ragel
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CONFIGURE_COMMAND <SOURCE_DIR>/configure CXXFLAGS=-std=c++98 --prefix=<INSTALL_DIR>
)
