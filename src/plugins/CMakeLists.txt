# ================================
# add moloch plugins
# ================================
set(moloch_plugins plugin)

foreach(plugin_name IN LISTS moloch_plugins)
    add_moloch_plugin(${plugin_name})
endforeach()

# ================================
# plugin specific configurations
# ================================

target_link_libraries(plugin utils)
