
#include "callback.h"

#include "../glbridge/callback.h"
#include "window.h"
#include "room.h"
#include "keyboard.h"

#include <lua.h>

#include <ctype.h>
#include <stdbool.h>

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
  (void)L;
  luabridge_window_setsize(w, h);
}

static void onstep(void* state) {
  lua_State* L = state;

  luabridge_room_getobjects(L);

  size_t len = lua_rawlen(L, -1);
  for (size_t i = 1; i <= len; i++) {
    lua_rawgeti(L, -1, i);
    lua_pushstring(L, "step");
    lua_gettable(L, -2);
    lua_insert(L, -2);
    lua_call(L, 1, 0);
  }
  lua_pop(L, 1);

  luabridge_keyboard_reset_presses();

}

static void onkey(void* state, unsigned char ch, int x, int y) {
  lua_State* L = state;

  (void)x;
  (void)y;

  KeyboardKey key = luabridge_keyboard_make_normal(tolower(ch));

  luabridge_keyboard_push(L, key);
  int keyindex = lua_gettop(L);
  luabridge_room_getobjects(L);

  luabridge_keyboard_set_state(L, key, true);

  size_t len = lua_rawlen(L, -1);
  for (size_t i = 1; i <= len; i++) {
    lua_rawgeti(L, -1, i);
    lua_pushstring(L, "key_down");
    lua_gettable(L, -2);
    lua_insert(L, -2);
    lua_pushvalue(L, keyindex);
    lua_call(L, 2, 0);
  }
  lua_pop(L, 2);

}

static void onspeckey(void* state, int ch, int x, int y) {
  lua_State* L = state;

  (void)x;
  (void)y;

  KeyboardKey key = luabridge_keyboard_make_special(ch);

  luabridge_keyboard_push(L, key);
  int keyindex = lua_gettop(L);
  luabridge_room_getobjects(L);

  luabridge_keyboard_set_state(L, key, true);

  size_t len = lua_rawlen(L, -1);
  for (size_t i = 1; i <= len; i++) {
    lua_rawgeti(L, -1, i);
    lua_pushstring(L, "key_down");
    lua_gettable(L, -2);
    lua_insert(L, -2);
    lua_pushvalue(L, keyindex);
    lua_call(L, 2, 0);
  }
  lua_pop(L, 2);

}

static void onkeyup(void* state, unsigned char ch, int x, int y) {
  lua_State* L = state;

  (void)x;
  (void)y;

  KeyboardKey key = luabridge_keyboard_make_normal(tolower(ch));

  luabridge_keyboard_push(L, key);
  int keyindex = lua_gettop(L);
  luabridge_room_getobjects(L);

  luabridge_keyboard_set_state(L, key, false);

  size_t len = lua_rawlen(L, -1);
  for (size_t i = 1; i <= len; i++) {
    lua_rawgeti(L, -1, i);
    lua_pushstring(L, "key_up");
    lua_gettable(L, -2);
    lua_insert(L, -2);
    lua_pushvalue(L, keyindex);
    lua_call(L, 2, 0);
  }
  lua_pop(L, 2);

}

static void onspeckeyup(void* state, int ch, int x, int y) {
  lua_State* L = state;

  (void)x;
  (void)y;

  KeyboardKey key = luabridge_keyboard_make_special(ch);

  luabridge_keyboard_push(L, key);
  int keyindex = lua_gettop(L);
  luabridge_room_getobjects(L);

  luabridge_keyboard_set_state(L, key, false);

  size_t len = lua_rawlen(L, -1);
  for (size_t i = 1; i <= len; i++) {
    lua_rawgeti(L, -1, i);
    lua_pushstring(L, "key_up");
    lua_gettable(L, -2);
    lua_insert(L, -2);
    lua_pushvalue(L, keyindex);
    lua_call(L, 2, 0);
  }
  lua_pop(L, 2);

}

GLBridgeCallbacks luabridge_callbacks(lua_State* L) {
  GLBridgeCallbacks cb;
  cb.state = L;
  cb.ondraw = ondraw;
  cb.onresize = onresize;
  cb.onstep = onstep;
  cb.onkey = onkey;
  cb.onspeckey = onspeckey;
  cb.onkeyup = onkeyup;
  cb.onspeckeyup = onspeckeyup;
  return cb;
}
