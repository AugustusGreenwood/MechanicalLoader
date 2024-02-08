#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

typedef struct {
    double a;
    double b;
    double c;
} Second;

typedef struct {
    int a;
    int b;
    int c;
    Second second;
} First;

int hello(lua_State *lua_state) { return 0; }

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "hello", hello);

    if (luaL_dofile(L, "test.lua") == LUA_OK) {
        lua_pop(L, lua_gettop(L));
    }

    lua_close(L);
    return 0;
}
