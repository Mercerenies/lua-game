
#include "luabridge/core.h"
#include "glbridge/core.h"
#include "glbridge/callback.h"

#include <stdlib.h>
#include <stdio.h>

static lua_State* L = NULL;

void deinit_trap() {
  if (L != NULL) {
    luabridge_deinit(L);
  }
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

  luabridge_eval_file(L, "script/script.lua");

  glbridge_main_loop();

  return 0;
}
