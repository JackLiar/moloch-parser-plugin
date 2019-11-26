# ================================
# plugin specific configurations
# ================================

add_moloch_plugin(plugin)
set_property(TARGET plugin APPEND PROPERTY 
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/plugin.cc
)
target_link_libraries(plugin PRIVATE utils)