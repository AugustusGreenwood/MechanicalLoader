cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(MechanicalLoader)

set(SOURCE_FILES
    src/main.c
    src/stage_control/driver.c
    src/stage_control/commands.c
    src/stage_control/calibration.c
    src/stage_control/run.c
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    option(DEBUGLOG "Print all debug information" OFF)
else()
    option(DEBUGLOG "Print all debug information" ON)
endif()
if(DEBUGLOG)
    add_definitions(-DDEBUGLOG)
endif(DEBUGLOG)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -Wall -Wextra")

add_executable(MechanicalLoader ${SOURCE_FILES})

target_include_directories(MechanicalLoader 
    PUBLIC
        include/
    PRIVATE
        src/stage_control/
        src/result/
)

target_link_libraries(MechanicalLoader usb-1.0)
