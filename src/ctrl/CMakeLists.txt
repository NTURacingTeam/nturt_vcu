if(CONFIG_VCU_CTRL)

add_subdirectory(states)

file(GLOB SIMULINK_FILES
    ${CMAKE_CURRENT_LIST_DIR}/simulink/*.c
)

target_sources(app PRIVATE
    ${SIMULINK_FILES}
    ctrl.c
    inv.c
)

target_sources_ifdef(CONFIG_VCU_CTRL_SHELL app PRIVATE
    shell.c
)

target_sources_ifdef(CONFIG_VCU_CTRL_SETTINGS app PRIVATE
    settings.c
)

endif()
