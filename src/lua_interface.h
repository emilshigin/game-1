#ifndef LUA_INTERFACE_H
#define LUA_INTERFACE_H

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

typedef struct GameSettings {
    int screenWidth;
    int screenHeight;
    float playerSpeed;
    int targetFPS;
} GameSettings;

// Initialize Lua state
lua_State* Lua_Init(void);

// Load settings from Lua file
GameSettings Lua_LoadSettings(lua_State* L, const char* filepath);

// Cleanup Lua state
void Lua_Cleanup(lua_State* L);

#endif
