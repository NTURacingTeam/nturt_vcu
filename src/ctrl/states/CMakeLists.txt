target_sources(app PRIVATE
    err.c
    states.c
)

target_sources_ifdef(CONFIG_VCU_STATES_SHELL app PRIVATE
    shell.c
)

zephyr_linker_sources(SECTIONS
    iterable_sections.ld
)
