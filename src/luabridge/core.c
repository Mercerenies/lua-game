
#include "core.h"

#include "vector2.h"
#include "color.h"
#include "object.h"
#include "room.h"
#include "canvas.h"
#include "constant.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 8192
static char buf[BUF_SIZE];

lua_State* luabridge_init() {
  lua_State* L = luaL_newstate();
  if (L == NULL)
    return NULL;
  luaL_openlibs(L);
  return L;
}

void luabridge_init_libs(lua_State* L) {
  luabridge_vector2_define(L);
  luabridge_color_define(L);
  luabridge_object_define(L);
  luabridge_room_define(L);
  luabridge_canvas_define(L);
  luabridge_constant_define(L);
}

void luabridge_deinit(lua_State* L) {
  lua_close(L);
}

int luabridge_eval_file(lua_State* L, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Could not open file: %s\n", strerror(errno));
    return 1;
  }
  size_t read = fread(buf, 1, BUF_SIZE, file);
  fclose(file);
  if (read >= BUF_SIZE - 1) {
    fprintf(stderr, "Script file too large\n");
    return 1;
  }
  buf[read] = 0;
  int error =
    luaL_loadbuffer(L, (const char*)buf, strlen((const char*)buf), filename) ||
    lua_pcall(L, 0, 0, 0);
  if (error) {
    fprintf(stderr, "%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
    return 1;
  }
  return 0;
}
