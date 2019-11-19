
#include "luabridge/core.h"
#include "luabridge/callback.h"
#include "luabridge/window.h"
#include "glbridge/core.h"
#include "glbridge/callback.h"

#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>

static lua_State* L = NULL;
static GLBridgeCallbacks callbacks;

void deinit_trap() {
  if (L != NULL) {
    luabridge_deinit(L);
  }
}

int l_protection(lua_State* L) {
  (void)L;
  glbridge_main_loop();
  return 0;
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  glbridge_init_and_display(&argc, argv);
  glbridge_init_callbacks();

  L = luabridge_init();
  if (L == NULL) {
    fprintf(stderr, "Could not initialize Lua.\n");
    return 1;
  }
  atexit(deinit_trap);
  luabridge_init_libs(L);

  callbacks = luabridge_callbacks(L);
  glbridge_set_callbacks(&callbacks);

  luabridge_window_setsize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

  luabridge_eval_file(L, "script/script.lua");

  lua_pushcfunction(L, l_protection);
  int error = lua_pcall(L, 0, 0, 0);
  if (error) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
    return 1;
  }
  return 0;
}
