
#include "canvas.h"

#include "color.h"
#include "vector2.h"
#include "constant.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <GL/glut.h>

#include <string.h>

const char* t_Game = "Game";

// -0, +0, e
int l_game_terminate(lua_State* L) {
  (void)L;
  exit(0);
  return 0;
}

static const struct luaL_Reg gamelib[] = {
  {"terminate", l_game_terminate},
  {NULL, NULL}
};

void luabridge_game_define(lua_State* L) {
  luaL_newmetatable(L, t_Game);
  luaL_setfuncs(L, gamelib, 0);

  lua_setglobal(L, t_Game);
}
