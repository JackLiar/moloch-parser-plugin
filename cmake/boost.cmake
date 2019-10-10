set(boost_url ${CMAKE_CURRENT_SOURCE_DIR}/third_party/boost_1_57_0.tar.bz2)

ExternalProject_Add(libboost
    URL ${boost_url}
    EXCLUDE_FROM_ALL ON
    PREFIX boost
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

