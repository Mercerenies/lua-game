
#include "color.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <string.h>

const char* t_Room = "Room";

static int ref_currentroom = 0;

// -0, +1, -
static int l_get_objects(lua_State* L) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref_currentroom);
  return 1;
}

static const struct luaL_Reg roomlib[] = {
  {"get_objects", l_get_objects},
  {NULL, NULL}
};

int luabridge_room_getobjects(lua_State* L) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref_currentroom);
  return 1;
}

void luabridge_room_define(lua_State* L) {
  luaL_newmetatable(L, t_Room);
  luaL_setfuncs(L, roomlib, 0);

  lua_newtable(L);
  ref_currentroom = luaL_ref(L, LUA_REGISTRYINDEX);

  lua_setglobal(L, t_Room);
}
