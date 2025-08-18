if(CONFIG_VCU_MSG)

target_sources(app PRIVATE
    msg.c
)

target_sources_ifdef(CONFIG_VCU_MSG_LOGGING app PRIVATE
    logging.c
)

endif()
