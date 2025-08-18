if(CONFIG_VCU_CANOPEN)

zephyr_include_directories(
    objdict
)

file(GLOB OBJDICT_FILES
    ${CMAKE_CURRENT_LIST_DIR}/objdict/*.c
)

target_sources(app PRIVATE
    ${OBJDICT_FILES}
)

target_sources_ifdef(CONFIG_VCU_CANOPEN_MSG app PRIVATE
    msg.c
)

target_sources_ifdef(CONFIG_VCU_CANOPEN_TM app PRIVATE
    telemetry.c
)

endif()
