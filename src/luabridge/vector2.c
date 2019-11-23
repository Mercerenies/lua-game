
#include "vector2.h"

#include "window.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <string.h>
#include <math.h>

#define BUF_SIZE 256
static char buf[BUF_SIZE];

const char* t_Vector2 = "Vector2";
const char* t_Vector2_Meta = "Vector2.Meta";

// -0, +1, -
Vector2* luabridge_vector2_pushnew(lua_State* L, lua_Number x, lua_Number y) {
  Vector2* table = lua_newuserdata(L, sizeof(Vector2));
  luaL_getmetatable(L, t_Vector2);
  lua_setmetatable(L, -2);
  table->x = x;
  table->y = y;
  return table;
}

Vector2 luabridge_vector2_screentogl(Vector2 vec) {
  int width = luabridge_window_getwidth();
  int height = luabridge_window_getheight();
  vec.x = 2 * vec.x / width - 1;
  vec.y = 1 - 2 * vec.y / height;
  return vec;
}

Vector2 luabridge_vector2_gltoscreen(Vector2 vec) {
  int width = luabridge_window_getwidth();
  int height = luabridge_window_getheight();
  vec.x = (  1 + vec.x) * width / 2;
  vec.y = (- 1 - vec.y) * height / 2;
  return vec;
}

// -2, +1, e
static int l_call(lua_State* L) {
  lua_Number x = luaL_checknumber(L, 2);
  lua_Number y = luaL_checknumber(L, 3);
  luabridge_vector2_pushnew(L, x, y);
  return 1;
}

// -2, +1, e
static int l_index(lua_State* L) {
  Vector2* table = luaL_checkudata(L, 1, t_Vector2);
  const char* field = luaL_checkstring(L, 2);
  switch (field[0]) {
  case 'x':
    lua_pushnumber(L, table->x);
    return 1;
  case 'y':
    lua_pushnumber(L, table->y);
    return 1;
  default:
    luaL_getmetatable(L, t_Vector2);
    lua_pushstring(L, field);
    lua_gettable(L, -2);
    return 1;
  }
}

// -1, +1, e
static int l_tostring(lua_State* L) {
  buf[0] = 0;
  Vector2* table = luaL_checkudata(L, 1, t_Vector2);
  snprintf(buf, BUF_SIZE, "(%f, %f)", table->x, table->y);
  lua_pushstring(L, buf);
  return 1;
}

// -1, +1, e
static int l_unm(lua_State* L) {
  Vector2* table = luaL_checkudata(L, 1, t_Vector2);
  luabridge_vector2_pushnew(L, -table->x, -table->y);
  return 1;
}

// -2, +1, e
static int l_add(lua_State* L) {
  Vector2* a = luaL_checkudata(L, 1, t_Vector2);
  Vector2* b = luaL_checkudata(L, 2, t_Vector2);
  luabridge_vector2_pushnew(L, a->x + b->x, a->y + b->y);
  return 1;
}

// -2, +1, e
static int l_sub(lua_State* L) {
  Vector2* a = luaL_checkudata(L, -2, t_Vector2);
  Vector2* b = luaL_checkudata(L, -1, t_Vector2);
  luabridge_vector2_pushnew(L, a->x - b->x, a->y - b->y);
  return 1;
}

// -2, +1, e
static int l_mul(lua_State* L) {
  Vector2* a = luaL_testudata(L, 1, t_Vector2);
  Vector2* b = luaL_testudata(L, 2, t_Vector2);
  if (a == NULL && b == NULL) {
    return luaL_error(L, "bad vector multiplication");
  } else if (a == NULL) {
    lua_Number a = luaL_checknumber(L, 1);
    luabridge_vector2_pushnew(L, a * b->x, a * b->y);
    return 1;
  } else if (b == NULL) {
    lua_Number b = luaL_checknumber(L, 2);
    luabridge_vector2_pushnew(L, a->x * b, a->y * b);
    return 1;
  } else {
    lua_pushnumber(L, a->x * b->x + a->y * b->y);
    return 1;
  }
}

// -2, +1, e
static int l_div(lua_State* L) {
  Vector2* a = luaL_checkudata(L, 1, t_Vector2);
  lua_Number b = luaL_checknumber(L, 2);
  luabridge_vector2_pushnew(L, a->x / b, a->y / b);
  return 1;
}

// -2, +1, e
static int l_eq(lua_State* L) {
  Vector2* a = luaL_checkudata(L, 1, t_Vector2);
  Vector2* b = luaL_checkudata(L, 2, t_Vector2);
  int eq = (a->x == b->x && a->y == b->y);
  lua_pushboolean(L, eq);
  return 1;
}

// -1, +1, e
static int l_rotated(lua_State* L) {
  Vector2* a = luaL_checkudata(L, 1, t_Vector2);
  lua_Number rad = luaL_checknumber(L, 2);
  lua_Number x = a->x * cos(rad) - a->y * sin(rad);
  lua_Number y = a->x * sin(rad) + a->y * cos(rad);
  luabridge_vector2_pushnew(L, x, y);
  return 1;
}

static const struct luaL_Reg vector2lib[] = {
  {"__index", l_index},
  {"__tostring", l_tostring},
  {"__unm", l_unm},
  {"__add", l_add},
  {"__sub", l_sub},
  {"__mul", l_mul},
  {"__div", l_div},
  {"__eq", l_eq},
  {"rotated", l_rotated},
  {NULL, NULL}
};

static const struct luaL_Reg vector2metalib[] = {
  {"__call", l_call},
  {NULL, NULL}
};

void luabridge_vector2_define(lua_State* L) {
  luaL_newmetatable(L, t_Vector2);
  luaL_setfuncs(L, vector2lib, 0);

  luaL_newmetatable(L, t_Vector2_Meta);
  luaL_setfuncs(L, vector2metalib, 0);
  lua_setmetatable(L, -2);

  lua_setglobal(L, t_Vector2);
}
