if(CONFIG_VCU_CTRL)

add_subdirectory(states)

target_sources(app PRIVATE
    ctrl.c
)

endif()
