if(CONFIG_VCU_DASHBOARD)

target_sources(app PRIVATE
    dashboard.c
    normal.c
    peripherals.c
    test.c
)

target_sources_ifdef(CONFIG_VCU_DASHBOARD_SHELL app PRIVATE
    shell.c
)

target_sources_ifdef(CONFIG_VCU_DASHBOARD_SETTINGS app PRIVATE
    settings.c
)

endif()
