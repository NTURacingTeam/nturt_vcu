if(CONFIG_VCU_SENSORS)

target_sources_ifdef(CONFIG_VCU_SOURCE_COCKPIT_NATIVE app PRIVATE
    cockpit.c
)

target_sources_ifdef(CONFIG_VCU_SOURCE_IMU_NATIVE app PRIVATE
    imu.c
)

target_sources_ifdef(CONFIG_VCU_SOURCE_GPS_NATIVE app PRIVATE
    gps.c
)

target_sources_ifdef(CONFIG_VCU_HAS_SUSP app PRIVATE
    susp.c
)

target_sources_ifdef(CONFIG_VCU_HAS_POW app PRIVATE
    pow.c
)

endif()
