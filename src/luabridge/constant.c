
#include "constant.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <GL/gl.h>

#include <string.h>

const char* t_Constant = "Constant";

typedef struct ConstantReg {
  const char* name;
  lua_Number value;
} ConstantReg;

static const ConstantReg constantlib[] = {
  {"POINTS", GL_POINTS},
  {"LINES", GL_LINES},
  {"LINE_STRIP", GL_LINE_STRIP},
  {"LINE_LOOP", GL_LINE_LOOP},
  {"TRIANGLES", GL_TRIANGLES},
  {"TRIANGLE_STRIP", GL_TRIANGLE_STRIP},
  {"TRIANGLE_FAN", GL_TRIANGLE_FAN},
  {"QUADS", GL_QUADS},
  {"QUAD_STRIP", GL_QUAD_STRIP},
  {"POLYGON", GL_POLYGON},
  {NULL, 0}
};

// -0, +0, e
int luabridge_constant_identify(lua_State* L, int index) {
  index = lua_absindex(L, index);
  switch (lua_type(L, index)) {
  case LUA_TNUMBER:
    // It's fine as is, so return now
    return 0;
  case LUA_TSTRING:
    // Look it up
    luaL_getmetatable(L, t_Constant);
    lua_pushvalue(L, index);
    lua_rawget(L, -2);
    lua_replace(L, index);
    lua_pop(L, 1);
    return 0;
  default:
    return luaL_error(L, "Expecting number or string");
  }
}

void luabridge_constant_define(lua_State* L) {
  luaL_newmetatable(L, t_Constant);

  for (const ConstantReg* curr = constantlib; curr->name != NULL; curr++) {
    lua_pushstring(L, curr->name);
    lua_pushnumber(L, curr->value);
    lua_rawset(L, -3);
  }

  lua_setglobal(L, t_Constant);
}
