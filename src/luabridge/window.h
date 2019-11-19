
#ifndef GAME_LUABRIDGE_WINDOW_H
#define GAME_LUABRIDGE_WINDOW_H

#include <lua.h>

const char* t_Window;

void luabridge_window_setsize(int w, int h);

int luabridge_window_getwidth();

int luabridge_window_getheight();

void luabridge_window_define(lua_State* L);

#endif // GAME_LUABRIDGE_VECTOR2_H
