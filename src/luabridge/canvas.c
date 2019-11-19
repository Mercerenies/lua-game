
#include "canvas.h"

#include "color.h"
#include "vector2.h"
#include "constant.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <GL/glut.h>

#include <string.h>

const char* t_Canvas = "Canvas";

// -2, +0, e
// draw_primitive(mode, points)
int l_draw_primitive(lua_State* L) {
  luabridge_constant_identify(L, 1);
  lua_Number mode = luaL_checknumber(L, 1);

  luaL_checktype(L, 2, LUA_TTABLE);
  size_t len = lua_rawlen(L, 2);

  glBegin(mode);

  for (size_t i = 1; i <= len; i++) {
    lua_rawgeti(L, 2, i);
    Vector2* vec = luaL_testudata(L, -1, t_Vector2);
    if (vec == NULL) {
      glEnd();
      return luaL_error(L, "Vector2 expected");
    }
    Vector2 converted = luabridge_vector2_screentogl(*vec);
    glVertex3f(converted.x, converted.y, 0.0);
  }

  glEnd();
  return 0;
}

// -1, +0, e
int l_set_color(lua_State* L) {
  Color* color = luaL_checkudata(L, 1, t_Color);
  glColor4f(color->r, color->g, color->b, color->a);
  return 0;
}

static const struct luaL_Reg canvaslib[] = {
  {"draw_primitive", l_draw_primitive},
  {"set_color", l_set_color},
  {NULL, NULL}
};

void luabridge_canvas_define(lua_State* L) {
  luaL_newmetatable(L, t_Canvas);
  luaL_setfuncs(L, canvaslib, 0);

  lua_setglobal(L, t_Canvas);
}
