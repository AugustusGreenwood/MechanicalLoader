cmake_minimum_required(VERSION 3.27.9)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(MechanicalLoader)

include_directories(include)

set(SOURCE_FILES
    src/main.c
    src/Driver.c
)

option(DEBUGLOG "Print all debug information" ON)
if(DEBUGLOG)
    add_definitions(-DDEBUGLOG)
endif(DEBUGLOG)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(MechanicalLoader ${SOURCE_FILES})

target_link_libraries(MechanicalLoader usb-1.0)
