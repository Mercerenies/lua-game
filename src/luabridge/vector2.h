
#ifndef GAME_LUABRIDGE_VECTOR2_H
#define GAME_LUABRIDGE_VECTOR2_H

#include <lua.h>

typedef struct {
  lua_Number x, y;
} Vector2;

const char* t_Vector2;
const char* t_Vector2_Meta;

// -0, +1, -
Vector2* luabridge_vector2_pushnew(lua_State* L, lua_Number x, lua_Number y);

void luabridge_vector2_define(lua_State* L);

#endif // GAME_LUABRIDGE_VECTOR2_H
