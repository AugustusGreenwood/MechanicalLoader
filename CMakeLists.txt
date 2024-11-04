cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(c_arcus_performax_control)

set(SOURCE_FILES
    src/main.c
    src/stage_control/driver.c
    src/stage_control/commands.c
    src/stage_control/calibration.c
    src/stage_control/run.c
    src/lua/lua_api.c
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    option(DEBUGLOG "Print all debug information" OFF)
else()
    option(DEBUGLOG "Print all debug information" ON)
endif()
if(DEBUGLOG)
    add_definitions(-DDEBUGLOG)
endif(DEBUGLOG)

#add_library(c_arcus_performax_control SHARED ${SOURCE_FILES})
add_executable(c_arcus_performax_control ${SOURCE_FILES})

target_compile_options(c_arcus_performax_control PRIVATE -march=native -Wall -Wextra -fPIC)

target_include_directories(c_arcus_performax_control
    PUBLIC
        include/
    PRIVATE
        src/stage_control/
        src/result/
        src/lua/
)

target_link_libraries(c_arcus_performax_control usb-1.0 luajit-5.1)
