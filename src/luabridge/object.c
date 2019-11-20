
#include "object.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

const char* t_Object = "Object";

// -0, +0, -
static int l_init(lua_State* L) {
  (void)L;
  return 0;
}

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

// -2, +1, e
static int l_new(lua_State* L) {
  if (lua_getmetatable(L, 1) == 0) {
    // No parent to call
    lua_newtable(L);
  } else {
    // Call the parent to construct
    lua_pushstring(L, "__index");
    lua_gettable(L, -2);
    lua_pushstring(L, "new");
    lua_gettable(L, -2);
    lua_insert(L, -2);
    lua_pushvalue(L, 2);
    lua_call(L, 2, 1);
    lua_remove(L, -2);
  }

  lua_pushvalue(L, 1);
  lua_setmetatable(L, -2);

  lua_pushstring(L, "init");
  lua_gettable(L, -2);
  lua_pushvalue(L, -2);
  lua_pushvalue(L, 2);
  lua_call(L, 2, 0);

  return 1;
}

// -1, +1, -
static int l_define(lua_State* L) {
  lua_newtable(L);

  lua_pushstring(L, "__index");
  lua_pushvalue(L, -2);
  lua_rawset(L, -3);

  lua_pushvalue(L, -2);
  lua_setmetatable(L, -2);

  return 1;
}

static const struct luaL_Reg objectlib[] = {
  {"init", l_init},
  {"step", l_step},
  {"draw", l_draw},
  {"key_event", l_key_event},
  {"new", l_new},
  {"define", l_define},
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
