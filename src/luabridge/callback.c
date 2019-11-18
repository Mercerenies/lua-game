
#include "callback.h"

#include "../glbridge/callback.h"

#include <lua.h>

static void ondraw(void* state) {
  lua_State* L = state;
  // DEBUG CODE This is just to test this function
  lua_getglobal(L, "test");
  lua_call(L, 0, 0);
  //
  (void)L;
}

GLBridgeCallbacks luabridge_callbacks(lua_State* L) {
  GLBridgeCallbacks cb;
  cb.state = L;
  cb.ondraw = ondraw;
  return cb;
}
