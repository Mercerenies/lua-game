
#include "color.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <string.h>

#define BUF_SIZE 256
static char buf[BUF_SIZE];

const char* t_Color = "Color";
const char* t_Color_Meta = "Color.Meta";

// -0, +1, -
Color* luabridge_color_pushnew(lua_State* L,
                               lua_Number r,
                               lua_Number g,
                               lua_Number b,
                               lua_Number a) {
  Color* table = lua_newuserdata(L, sizeof(Color));
  luaL_getmetatable(L, t_Color);
  lua_setmetatable(L, -2);
  table->r = r;
  table->g = g;
  table->b = b;
  table->a = a;
  return table;
}

// -(3|4), +1, e
static int l_call(lua_State* L) {
  // Remember: First argument is the Color object itself
  lua_Number r = luaL_checknumber(L, 2);
  lua_Number g = luaL_checknumber(L, 3);
  lua_Number b = luaL_checknumber(L, 4);
  lua_Number a = lua_isnoneornil(L, 5) ? 1.0 : luaL_checknumber(L, 5);
  luabridge_color_pushnew(L, r, g, b, a);
  return 1;
}

// -2, +1, e
static int l_index(lua_State* L) {
  Color* table = luaL_checkudata(L, -2, t_Color);
  const char* field = luaL_checkstring(L, -1);
  if (strlen(field) != 1) {
    lua_pushnil(L);
    return 1;
  }
  switch (field[0]) {
  case 'r':
    lua_pushnumber(L, table->r);
    return 1;
  case 'g':
    lua_pushnumber(L, table->g);
    return 1;
  case 'b':
    lua_pushnumber(L, table->b);
    return 1;
  case 'a':
    lua_pushnumber(L, table->a);
    return 1;
  default:
    lua_pushnil(L);
    return 1;
  }
}

// -1, +1, e
static int l_tostring(lua_State* L) {
  buf[0] = 0;
  Color* table = luaL_checkudata(L, -1, t_Color);
  snprintf(buf, BUF_SIZE, "Color(%f, %f, %f, %f)", table->r, table->g, table->b, table->a);
  lua_pushstring(L, buf);
  return 1;
}

// -2, +1, e
static int l_eq(lua_State* L) {
  Color* a = luaL_checkudata(L, -2, t_Color);
  Color* b = luaL_checkudata(L, -1, t_Color);
  int eq = (a->r == b->r && a->g == b->g && a->b == b->b && a->a == b->a);
  lua_pushboolean(L, eq);
  return 1;
}

static const struct luaL_Reg colorlib[] = {
  {"__index", l_index},
  {"__tostring", l_tostring},
  {"__eq", l_eq},
  {NULL, NULL}
};

static const struct luaL_Reg colormetalib[] = {
  {"__call", l_call},
  {NULL, NULL}
};

void luabridge_color_define(lua_State* L) {
  luaL_newmetatable(L, t_Color);
  luaL_setfuncs(L, colorlib, 0);

  luaL_newmetatable(L, t_Color_Meta);
  luaL_setfuncs(L, colormetalib, 0);
  lua_setmetatable(L, -2);

  lua_setglobal(L, t_Color);
}
