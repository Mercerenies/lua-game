
#include "object.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

const char* t_Object = "Object";

// -0, +0, -
static int l_step(lua_State* L) {
  (void)L;
  return 0;
}

// -0, +0, -
static int l_draw(lua_State* L) {
  (void)L;
  return 0;
}

// -0, +0, -
static int l_key_event(lua_State* L) {
  (void)L;
  return 0;
}

// -0, +1, -
static int l_new(lua_State* L) {
  lua_newtable(L);
  luaL_getmetatable(L, t_Object);
  lua_setmetatable(L, -2);
  return 1;
}

static const struct luaL_Reg objectlib[] = {
  {"step", l_step},
  {"draw", l_draw},
  {"key_event", l_key_event},
  {"new", l_new},
  {NULL, NULL}
};

void luabridge_object_define(lua_State* L) {
  luaL_newmetatable(L, t_Object);
  luaL_setfuncs(L, objectlib, 0);

  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_rawset(L, -3);

  lua_setglobal(L, t_Object);
}
