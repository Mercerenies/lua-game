
#include "canvas.h"

#include "color.h"
#include "vector2.h"
#include "constant.h"

#include "../glbridge/text.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <GL/glut.h>

#include <string.h>

const char* t_Canvas = "Canvas";

// -2, +0, e
int l_draw_line(lua_State* L) {
  Vector2* a = luaL_checkudata(L, 1, t_Vector2);
  Vector2* b = luaL_checkudata(L, 2, t_Vector2);
  Vector2 a1 = luabridge_vector2_screentogl(*a);
  Vector2 b1 = luabridge_vector2_screentogl(*b);
  glBegin(GL_LINES);
  glVertex3f(a1.x, a1.y, 0.0);
  glVertex3f(b1.x, b1.y, 0.0);
  glEnd();
  return 0;
}

// -2, +0, e
int l_draw_rectangle(lua_State* L) {
  Vector2* a = luaL_checkudata(L, 1, t_Vector2);
  Vector2* b = luaL_checkudata(L, 2, t_Vector2);
  Vector2 a1 = luabridge_vector2_screentogl(*a);
  Vector2 b1 = luabridge_vector2_screentogl(*b);
  glBegin(GL_QUADS);
  glVertex3f(a1.x, a1.y, 0.0);
  glVertex3f(a1.x, b1.y, 0.0);
  glVertex3f(b1.x, b1.y, 0.0);
  glVertex3f(b1.x, a1.y, 0.0);
  glEnd();
  return 0;
}

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

// -2, +0, e
// draw_text(pos, text)
int l_draw_text(lua_State* L) {
  Vector2* pos = luaL_checkudata(L, 1, t_Vector2);
  Vector2 pos1 = luabridge_vector2_screentogl(*pos);
  const char* text = luaL_checkstring(L, 2); // Doesn't support nulls
                                             // right now. Don't print
                                             // nulls to the screen.

  glbridge_draw_text(pos1.x, pos1.y, GLUT_BITMAP_8_BY_13, text);

  return 0;
}

// -1, +0, e
int l_set_color(lua_State* L) {
  Color* color = luaL_checkudata(L, 1, t_Color);
  glColor4f(color->r, color->g, color->b, color->a);
  return 0;
}

static const struct luaL_Reg canvaslib[] = {
  {"draw_rectangle", l_draw_rectangle},
  {"draw_line", l_draw_line},
  {"draw_primitive", l_draw_primitive},
  {"draw_text", l_draw_text},
  {"set_color", l_set_color},
  {NULL, NULL}
};

void luabridge_canvas_define(lua_State* L) {
  luaL_newmetatable(L, t_Canvas);
  luaL_setfuncs(L, canvaslib, 0);

  lua_setglobal(L, t_Canvas);
}
