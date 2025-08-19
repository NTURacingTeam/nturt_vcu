target_sources(app PRIVATE
    states.c
)

target_sources_ifdef(CONFIG_VCU_STATES_ERR app PRIVATE
    err.c
)

target_sources_ifdef(CONFIG_VCU_STATES_SHELL app PRIVATE
    shell.c
)

zephyr_linker_sources(SECTIONS
    iterable_sections.ld
)
