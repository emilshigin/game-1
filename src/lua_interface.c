#include "lua_interface.h"
#include <stdio.h>

lua_State* Lua_Init(void) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);  // Open standard libraries
    return L;
}

GameSettings Lua_LoadSettings(lua_State* L, const char* filepath) {
    // Default settings
    GameSettings settings = {
        .screenWidth = 1280,
        .screenHeight = 720,
        .enabledVSync = 0,
    };
    
    // Load and execute Lua file
    if (luaL_dofile(L, filepath) != LUA_OK) {
        printf("Error loading %s: %s\n", filepath, lua_tostring(L, -1));
        lua_pop(L, 1);
        return settings;  // Return defaults on error
    }
    
    // Read settings table
    lua_getglobal(L, "settings");
    if (lua_istable(L, -1)) {
        lua_getfield(L, -1, "screenWidth");
        if (lua_isinteger(L, -1)) settings.screenWidth = lua_tointeger(L, -1);
        lua_pop(L, 1);
        
        lua_getfield(L, -1, "screenHeight");
        if (lua_isinteger(L, -1)) settings.screenHeight = lua_tointeger(L, -1);
        lua_pop(L, 1);
        
        lua_getfield(L, -1, "enabledVSync");
        if (lua_isnumber(L, -1)) settings.enabledVSync = lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1);  // Pop settings table
    
    return settings;
}

void Lua_Cleanup(lua_State* L) {
    if (L) lua_close(L);
}
