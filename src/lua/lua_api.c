#include "commands.h"
#include "driver.h"
#include "result.h"
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <unistd.h>

static int lua_set_high_speed(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int high_speed = lua_tointeger(L, 2);
    set_high_speed(*device, high_speed);
    return 0;
}
static int lua_set_low_speed(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int low_speed = lua_tointeger(L, 2);
    set_low_speed(*device, low_speed);
    return 0;
}
static int lua_set_acceleration_time(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int accel_time = lua_tointeger(L, 2);
    set_acceleration_time(*device, accel_time);
    return 0;
}
static int lua_set_acceleration_profile(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int profile = lua_tointeger(L, 2);
    set_acceleration_profile(*device, profile);
    return 0;
}
static int lua_set_idle_time(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int idle_time = lua_tointeger(L, 2);
    set_high_speed(*device, idle_time);
    return 0;
}
static int lua_set_microstepping(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int microsteps = lua_tointeger(L, 2);
    set_high_speed(*device, microsteps);
    return 0;
}
static int lua_set_absolute_movement(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    set_absolute_movement(*device);
    return 0;
}
static int lua_set_relative_movement(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    set_relative_movement(*device);
    return 0;
}
static int lua_set_position(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int position = lua_tointeger(L, 2);
    set_high_speed(*device, position);
    return 0;
}
static int lua_get_high_speed(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int high_speed;
    get_high_speed(*device, &high_speed);
    return 0;
}
static int lua_get_position(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int position;
    get_position(*device, &position);
    return 0;
}
static int lua_get_motor_status(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int status;
    get_motor_status(*device, &status);
    return 0;
}
static int lua_turn_motor_on(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    turn_motor_on(*device);
    return 0;
}
static int lua_turn_motor_off(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    turn_motor_off(*device);
    return 0;
}
static int lua_interactive_mode(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    interactive_mode(*device);
    return 0;
}
static int lua_write_motor_driver_settings(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    write_motor_driver_settings(*device);
    return 0;
}
static int lua_read_motor_driver_settings(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    read_motor_driver_settings(*device);
    return 0;
}
static int lua_move_stage(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int position = lua_tointeger(L, 2);
    move_stage(*device, position);
    return 0;
}
static int lua_wait_for_motor_idle(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    wait_for_motor_idle(*device, NULL, NULL);
    return 0;
}
static int lua_move_cycle(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int amplitude = lua_tointeger(L, 2);
    move_cycle(*device, amplitude, NULL, NULL);
    return 0;
}
static int lua_open(lua_State *L) {
    Device device;
    device.iface_number = 0;
    open_device(&device);

    if (device.handle == NULL) {
        lua_pushnil(L);
    } else {
        lua_pushlightuserdata(L, &device);
    }

    return 1;
}
static int lua_close_device(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    close_device(*device);
    return 0;
}

#define EXPOSE_C_FUNC(L, name, func)                                                     \
    do {                                                                                 \
        lua_pushcfunction(L, func);                                                      \
        lua_setglobal(L, name);                                                          \
    } while (0)

void lua_init() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    EXPOSE_C_FUNC(L, "set_high_speed", lua_set_high_speed);
    EXPOSE_C_FUNC(L, "set_low_speed", lua_set_low_speed);
    EXPOSE_C_FUNC(L, "set_acceleration_time", lua_set_acceleration_time);
    EXPOSE_C_FUNC(L, "set_acceleration_profile", lua_set_acceleration_profile);
    EXPOSE_C_FUNC(L, "set_idle_time", lua_set_idle_time);
    EXPOSE_C_FUNC(L, "set_microstepping", lua_set_microstepping);
    EXPOSE_C_FUNC(L, "set_absolute_movement", lua_set_absolute_movement);
    EXPOSE_C_FUNC(L, "set_high_speed", lua_set_relative_movement);
    EXPOSE_C_FUNC(L, "set_position", lua_set_position);
    EXPOSE_C_FUNC(L, "get_high_speed", lua_get_high_speed);
    EXPOSE_C_FUNC(L, "get_position", lua_get_position);
    EXPOSE_C_FUNC(L, "get_motor_status", lua_get_motor_status);
    EXPOSE_C_FUNC(L, "turn_motor_on", lua_turn_motor_on);
    EXPOSE_C_FUNC(L, "turn_motor_off", lua_turn_motor_off);
    EXPOSE_C_FUNC(L, "interactive_mode", lua_interactive_mode);
    EXPOSE_C_FUNC(L, "write_motor_driver_settings", lua_write_motor_driver_settings);
    EXPOSE_C_FUNC(L, "read_motor_driver_settings", lua_read_motor_driver_settings);
    EXPOSE_C_FUNC(L, "move_stage", lua_move_stage);
    EXPOSE_C_FUNC(L, "wait_for_motor_idle", lua_wait_for_motor_idle);
    EXPOSE_C_FUNC(L, "move_cycle", lua_move_cycle);
    EXPOSE_C_FUNC(L, "open", lua_open);
    EXPOSE_C_FUNC(L, "close", lua_close_device);

    if (luaL_dofile(L, "test.lua") == LUA_OK) {
        lua_pop(L, lua_gettop(L));
    }

    lua_close(L);
}
