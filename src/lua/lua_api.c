#include "commands.h"
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

static int lua_set_high_speed(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int high_speed = lua_tointeger(lua_state, 2);
    HANDLE_ERROR(set_high_speed(device, high_speed), "lua_set_high_speed failed");
    return 0;
}
static int lua_set_low_speed(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int low_speed = lua_tointeger(lua_state, 2);
    HANDLE_ERROR(set_low_speed(device, low_speed), "lua_set_low_speed failed");
    return 0;
}
static int lua_set_acceleration_time(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int accel_time = lua_tointeger(lua_state, 2);
    HANDLE_ERROR(set_acceleration_time(device, accel_time),
                 "lua_set_acceleration_time failed");
    return 0;
}
static int lua_set_acceleration_profile(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int profile = lua_tointeger(lua_state, 2);
    HANDLE_ERROR(set_acceleration_profile(device, profile),
                 "lua_set_acceleration_profile");
    return 0;
}
static int lua_set_idle_time(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int idle_time = lua_tointeger(lua_state, 2);
    HANDLE_ERROR(set_high_speed(device, idle_time), "lua_set_idle_time");
    return 0;
}
static int lua_set_microstepping(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int microsteps = lua_tointeger(lua_state, 2);
    HANDLE_ERROR(set_high_speed(device, microsteps), "lua_set_microstepping");
    return 0;
}
static int lua_set_absolute_movement(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    HANDLE_ERROR(set_absolute_movement(device), "lua_set_absolute_movement");
    return 0;
}
static int lua_set_relative_movement(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    HANDLE_ERROR(set_relative_movement(device), "lua_set_relative_movement");
    return 0;
}
static int lua_set_position(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int position = lua_tointeger(lua_state, 2);
    HANDLE_ERROR(set_high_speed(device, position), "lua_set_position");
    return 0;
}
static int lua_get_high_speed(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int high_speed;
    HANDLE_ERROR(get_high_speed(device, &high_speed), "lua_get_high_speed");
    return 0;
}
static int lua_get_position(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int position;
    HANDLE_ERROR(get_position(device, &position), "lua_get_position");
    return 0;
}
static int lua_get_motor_status(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int status;
    HANDLE_ERROR(get_motor_status(device, &status), "lua_get_motor_status");
    return 0;
}
static int lua_turn_motor_on(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    HANDLE_ERROR(turn_motor_on(device), "lua_turn_motor_on");
    return 0;
}
static int lua_turn_motor_off(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    HANDLE_ERROR(turn_motor_off(device), "lua_turn_motor_off");
    return 0;
}
static int lua_interactive_mode(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    HANDLE_ERROR(interactive_mode(device), "lua_interactive_mode");
    return 0;
}
static int lua_write_motor_driver_settings(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    HANDLE_ERROR(write_motor_driver_settings(device), "lua_write_motor_driver_settings");
    return 0;
}
static int lua_read_motor_driver_settings(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    HANDLE_ERROR(read_motor_driver_settings(device), "lua_read_motor_driver_settings");
    return 0;
}
static int lua_move_stage(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int position = lua_tointeger(lua_state, 2);
    HANDLE_ERROR(move_stage(device, position), "lua_move_stage");
    return 0;
}
static int lua_wait_for_motor_idle(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    HANDLE_ERROR(wait_for_motor_idle(device, NULL, NULL), "lua_wait_for_motor_idle");
    return 0;
}
static int lua_move_cycle(lua_State *lua_state) {
    Device device = *(Device *)lua_topointer(lua_state, 1);
    int amplitude = lua_tointeger(lua_state, 2);
    HANDLE_ERROR(move_cycle(device, amplitude, NULL, NULL), "lua_move_cycle");
    return 0;
}

static const struct luaL_Reg devicelib[] = {
    {"set_high_speed", lua_set_high_speed},
    {"set_low_speed", lua_set_low_speed},
    {"set_acceleration_time", lua_set_acceleration_time},
    {"set_acceleration_profile", lua_set_acceleration_profile},
    {"set_idle_time", lua_set_idle_time},
    {"set_microstepping", lua_set_microstepping},
    {"set_absolute_movement", lua_set_absolute_movement},
    {"set_high_speed", lua_set_relative_movement},
    {"set_position", lua_set_position},
    {"get_high_speed", lua_get_high_speed},
    {"get_position", lua_get_position},
    {"get_motor_status", lua_get_motor_status},
    {"turn_motor_on", lua_turn_motor_on},
    {"turn_motor_off", lua_turn_motor_off},
    {"interactive_mode", lua_interactive_mode},
    {"write_motor_driver_settings", lua_write_motor_driver_settings},
    {"read_motor_driver_settings", lua_read_motor_driver_settings},
    {"move_stage", lua_move_stage},
    {"wait_for_motor_idle", lua_wait_for_motor_idle},
    {"move_cycle", lua_move_cycle},
    {NULL, NULL}};

void lua_init() {
    lua_State *lua_state = luaL_newstate();
    luaL_openlibs(lua_state);

    lua_newtable(lua_state);
    luaL_setfuncs(lua_state, devicelib, 0);
    lua_setglobal(lua_state, "Device");

    if (luaL_dofile(lua_state, "test.lua") == LUA_OK) {
        lua_pop(lua_state, lua_gettop(lua_state));
    }

    lua_close(lua_state);
}
