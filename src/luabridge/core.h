
#ifndef GAME_LUABRIDGE_CORE_H
#define GAME_LUABRIDGE_CORE_H

#include <lua.h>

lua_State* luabridge_init();

void luabridge_init_libs(lua_State* L);

void luabridge_deinit(lua_State* L);

int luabridge_eval_file(lua_State* L, const char* filename);

#endif // GAME_LUABRIDGE_CORE_H
