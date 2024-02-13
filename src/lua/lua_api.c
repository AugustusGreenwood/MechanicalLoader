#include "commands.h"
#include "driver.h"
#include <luajit-2.1/lauxlib.h>
#include <luajit-2.1/lua.h>
#include <luajit-2.1/lualib.h>
#include <stdio.h>
#include <stdlib.h>

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
    set_idle_time(*device, idle_time);
    return 0;
}
static int lua_set_microstepping(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int microsteps = lua_tointeger(L, 2);
    set_microstepping(*device, microsteps);
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
    set_position(*device, position);
    return 0;
}
static int lua_get_high_speed(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int high_speed;
    get_high_speed(*device, &high_speed);
    lua_pushinteger(L, high_speed);
    return 1;
}
static int lua_get_position(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int position;
    get_position(*device, &position);
    lua_pushinteger(L, position);
    return 0;
}
static int lua_get_motor_status(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    int status;
    get_motor_status(*device, &status);
    lua_pushinteger(L, status);
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

static int lua_open_device(lua_State *L) {
    int iface_number = luaL_checkinteger(L, 1);

    Device *device = (Device *)malloc(sizeof(Device));
    device->iface_number = iface_number;
    device->handle = NULL;
    device->context = NULL;

    if (open_device(device) != 0) {
        lua_pushnil(L);
    } else {
        lua_pushlightuserdata(L, device);
    }
    return 1;
}
static int lua_close_device(lua_State *L) {
    Device *device = (Device *)lua_touserdata(L, 1);
    close_device(*device);
    return 0;
}

static const luaL_Reg device_lib[] = {
    {"set_high_speed", lua_set_high_speed},
    {"set_low_speed", lua_set_low_speed},
    {"set_acceleration_time", lua_set_acceleration_time},
    {"set_acceleration_profile", lua_set_acceleration_profile},
    {"set_idle_time", lua_set_idle_time},
    {"set_microstepping", lua_set_microstepping},
    {"set_absolute_movement", lua_set_absolute_movement},
    {"set_relative_movement", lua_set_relative_movement},
    {"set_position", lua_set_position},
    {"get_high_speed", lua_get_high_speed},
    {"get_position", lua_get_position},
    {"get_motor_status", lua_get_motor_status},
    {"turn_motor_on", lua_turn_motor_on},
    {"turn_motor_off", lua_turn_motor_off},
    {"interactive_mode", lua_interactive_mode},
    {"write_motor_driver_settings", lua_write_motor_driver_settings},
    {"read_motor_driver_settings", lua_read_motor_driver_settings},
    {"wait_for_motor_idle", lua_wait_for_motor_idle},
    {"move_stage", lua_move_stage},
    {"move_cycle", lua_move_cycle},
    {"open", lua_open_device},
    {"close", lua_close_device},
    {NULL, NULL}};

void lua_init() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L);

    luaL_newlib(L, device_lib);

    lua_setglobal(L, "Device");

    if (luaL_dofile(L, "script.lua") == LUA_OK) {
        lua_pop(L, lua_gettop(L));
    }

    lua_close(L);
}
