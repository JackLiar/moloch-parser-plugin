set(glib_url ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glib-2.56.2.tar.xz)

ExternalProject_Add(libglib
    URL ${glib_url}
    EXCLUDE_FROM_ALL ON
    PREFIX glib
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --disable-xattr --disable-shared --enable-static --disable-libelf --disable-selinux --disable-libmount --with-pcre=internal --prefix=<INSTALL_DIR>
)