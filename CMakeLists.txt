cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_C_STANDARD 11)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(nturt_vcu LANGUAGES C)

zephyr_include_directories(
    include
)

add_subdirectory(src/canopen)
add_subdirectory(src/ctrl)
add_subdirectory(src/dashboard)
add_subdirectory(src/msg)
add_subdirectory(src/perception)
add_subdirectory(src/sys)
add_subdirectory(src/telemetry)

target_sources(app PRIVATE
    src/main.c
)
