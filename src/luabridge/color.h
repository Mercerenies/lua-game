
#ifndef GAME_LUABRIDGE_COLOR_H
#define GAME_LUABRIDGE_COLOR_H

#include <lua.h>

typedef struct {
  lua_Number r, g, b, a;
} Color;

const char* t_Color;
const char* t_Color_Meta;

// -0, +1, -
Color* luabridge_color_pushnew(lua_State* L,
                               lua_Number r,
                               lua_Number g,
                               lua_Number b,
                               lua_Number a);

void luabridge_color_define(lua_State* L);

#endif // GAME_LUABRIDGE_COLOR_H
