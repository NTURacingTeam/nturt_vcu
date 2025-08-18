if(CONFIG_VCU_TM)

target_sources(app PRIVATE
    msg.c
)

target_sources_ifdef(CONFIG_VCU_TM_MSG app PRIVATE
    telemetry.c
)

endif()
