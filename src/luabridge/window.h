
#ifndef GAME_LUABRIDGE_WINDOW_H
#define GAME_LUABRIDGE_WINDOW_H

#include <lua.h>

const char* t_Window;

void luabridge_window_setsize(lua_State* L, int w, int h);

void luabridge_window_define(lua_State* L);

#endif // GAME_LUABRIDGE_VECTOR2_H
