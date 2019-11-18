
#include "callback.h"

#include "../glbridge/callback.h"
#include "window.h"

#include <lua.h>

static void ondraw(void* state) {
  lua_State* L = state;
  (void)L;
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
