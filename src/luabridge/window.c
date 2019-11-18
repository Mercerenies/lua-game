
#include "window.h"

#include "vector2.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static int window_width = 0;
static int window_height = 0;

const char* t_Window = "Window";

// -0, +1, -
int l_get_size(lua_State* L) {
  luabridge_vector2_pushnew(L, window_width, window_height);
  return 1;
}

static const struct luaL_Reg windowlib[] = {
  {"get_size", l_get_size},
  {NULL, NULL}
};

void luabridge_window_setsize(lua_State* L, int w, int h) {
  (void)L; // May use this later, so I want to go ahead and take it as
           // an argument.
  window_width = w;
  window_height = h;
}

void luabridge_window_define(lua_State* L) {
  luaL_newmetatable(L, t_Window);
  luaL_setfuncs(L, windowlib, 0);

  lua_setglobal(L, t_Window);
}
