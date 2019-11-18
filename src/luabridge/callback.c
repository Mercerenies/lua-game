
#include "callback.h"

#include "../glbridge/callback.h"
#include "window.h"
#include "room.h"

#include <lua.h>

static void ondraw(void* state) {
  lua_State* L = state;

  luabridge_room_getobjects(L);

  size_t len = lua_rawlen(L, -1);
  for (size_t i = 1; i <= len; i++) {
    lua_rawgeti(L, -1, i);
    lua_pushstring(L, "draw");
    lua_gettable(L, -2);
    lua_insert(L, -2);
    lua_call(L, 1, 0);
  }
  lua_pop(L, 1);

}

static void onresize(void* state, int w, int h) {
  lua_State* L = state;
  luabridge_window_setsize(L, w, h);
}

GLBridgeCallbacks luabridge_callbacks(lua_State* L) {
  GLBridgeCallbacks cb;
  cb.state = L;
  cb.ondraw = ondraw;
  cb.onresize = onresize;
  return cb;
}
