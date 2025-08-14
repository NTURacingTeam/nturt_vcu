if(CONFIG_VCU_SENSORS)

target_sources(app PRIVATE
    cockpit.c
)

target_sources_ifdef(CONFIG_VCU_HAS_IMU app PRIVATE
    imu.c
)

target_sources_ifdef(CONFIG_VCU_HAS_GNSS app PRIVATE
    gnss.c
)

target_sources_ifdef(CONFIG_VCU_HAS_SUSP app PRIVATE
    susp.c
)

target_sources_ifdef(CONFIG_VCU_HAS_POW app PRIVATE
    pow.c
)

endif()
