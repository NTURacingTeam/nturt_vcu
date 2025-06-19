if(CONFIG_VCU_CTRL)

target_sources(app PRIVATE
    ctrl.c
    rtd_sound.c
    states.c
)

zephyr_linker_sources(SECTIONS
    iterable_sections.ld
)

endif()
