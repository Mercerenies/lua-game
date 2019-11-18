
#include "luabridge/core.h"

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

  L = luabridge_init();
  if (L == NULL) {
    fprintf(stderr, "Could not initialize Lua.\n");
    return 1;
  }
  atexit(deinit_trap);
  luabridge_init_libs(L);

  luabridge_eval_file(L, "script/script.lua");

  return 0;
}
