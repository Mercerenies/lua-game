
#ifndef GAME_LUABRIDGE_CONSTANT_H
#define GAME_LUABRIDGE_CONSTANT_H

#include <lua.h>

const char* t_Constant;

// -0, +0, e
int luabridge_constant_identify(lua_State* L, int index);

void luabridge_constant_define(lua_State* L);

#endif // GAME_LUABRIDGE_CONSTANT_H
