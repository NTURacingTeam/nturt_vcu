if(CONFIG_VCU_DASHBOARD)

add_subdirectory(modes)

target_sources(app PRIVATE
    dashboard.c
    peripherals.c
)

target_sources_ifdef(CONFIG_VCU_DASHBOARD_SHELL app PRIVATE
    shell.c
)

target_sources_ifdef(CONFIG_VCU_DASHBOARD_SETTINGS app PRIVATE
    settings.c
)

endif()
