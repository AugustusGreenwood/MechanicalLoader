cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(MechanicalLoader)

include_directories(
    src/driver/
    src/control/
)

set(SOURCE_FILES
    src/main.c
    src/driver/driver.c
    src/control/control.c
    src/control/calibration.c
)

option(DEBUGLOG "Print all debug information" ON)
if(DEBUGLOG)
    add_definitions(-DDEBUGLOG)
endif(DEBUGLOG)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -Wall -Wextra")

add_executable(MechanicalLoader ${SOURCE_FILES})

target_link_libraries(MechanicalLoader usb-1.0)
