
#include "keyboard.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <GL/freeglut.h>

#include <stdbool.h>

// Representation for KeyboardKey:
// 0-255 : GLUT special key constants
// 256-1023 : Special constants used by this application
// 1024-1151 : Standard ASCII encoding

#define GLUT_NULL 0
#define SPECIAL_NULL 256
#define SPECIAL_SHIFT 257
#define SPECIAL_CTRL 258
#define SPECIAL_ALT 259
#define ASCII_NULL 1024
#define ASCII_COUNT 128

#define MAX_KEY_MEMORY 8

static int ref_keytable = 0;

static KeyboardKey pressed[MAX_KEY_MEMORY];
static int pressed_ptr = 0;

static KeyboardKey released[MAX_KEY_MEMORY];
static int released_ptr = 0;

const char* t_Keyboard = "Keyboard";

const char* t_Key = "Key";

typedef struct KeyReg {
  const char* name;
  KeyboardKey value;
} KeyReg;

KeyboardKey luabridge_keyboard_make_normal(unsigned char ch) {
  return ASCII_NULL + (long)ch;
}

KeyboardKey luabridge_keyboard_make_special(int ch) {
  return GLUT_NULL + ch;
}

void luabridge_keyboard_push(lua_State* L, KeyboardKey k) {
  lua_pushinteger(L, k);
}

// -1, +1, e
int l_key_of(lua_State* L) {
  const char* str = luaL_checkstring(L, 1);
  if (str[0] == 0) {
    // If it's null (either by design or by being passed an empty
    // string), return nil.
    lua_pushnil(L);
    return 1;
  }
  luabridge_keyboard_push(L, luabridge_keyboard_make_normal(str[0]));
  return 1;
}

// -1, +1, e
int l_is_down(lua_State* L) {
  KeyboardKey k = luaL_checknumber(L, 1);
  bool result = false;
  switch (k) {
  case SPECIAL_SHIFT:
    result =
      luabridge_keyboard_get_state(L, GLUT_NULL + GLUT_KEY_SHIFT_L) ||
      luabridge_keyboard_get_state(L, GLUT_NULL +GLUT_KEY_SHIFT_R);
    break;
  case SPECIAL_CTRL:
    result =
      luabridge_keyboard_get_state(L, GLUT_NULL + GLUT_KEY_CTRL_L) ||
      luabridge_keyboard_get_state(L, GLUT_NULL + GLUT_KEY_CTRL_R);
    break;
  case SPECIAL_ALT:
    result =
      luabridge_keyboard_get_state(L, GLUT_NULL + GLUT_KEY_ALT_L) ||
      luabridge_keyboard_get_state(L, GLUT_NULL + GLUT_KEY_ALT_R);
    break;
  default:
    result = luabridge_keyboard_get_state(L, k);
    break;
  }
  lua_pushboolean(L, result);
  return 1;
}

// -1, +1, e
int l_is_pressed(lua_State* L) {
  KeyboardKey k = luaL_checknumber(L, 1);
  bool result = false;
  switch (k) {
  case SPECIAL_SHIFT:
    result =
      luabridge_keyboard_was_pressed(GLUT_NULL + GLUT_KEY_SHIFT_L) ||
      luabridge_keyboard_was_pressed(GLUT_NULL + GLUT_KEY_SHIFT_R);
    break;
  case SPECIAL_CTRL:
    result =
      luabridge_keyboard_was_pressed(GLUT_NULL + GLUT_KEY_CTRL_L) ||
      luabridge_keyboard_was_pressed(GLUT_NULL + GLUT_KEY_CTRL_R);
    break;
  case SPECIAL_ALT:
    result =
      luabridge_keyboard_was_pressed(GLUT_NULL + GLUT_KEY_ALT_L) ||
      luabridge_keyboard_was_pressed(GLUT_NULL + GLUT_KEY_ALT_R);
    break;
  default:
    result = luabridge_keyboard_was_pressed(k);
    break;
  }
  lua_pushboolean(L, result);
  return 1;
}

// -1, +1, e
int l_is_released(lua_State* L) {
  KeyboardKey k = luaL_checknumber(L, 1);
  bool result = false;
  switch (k) {
  case SPECIAL_SHIFT:
    result =
      luabridge_keyboard_was_released(GLUT_NULL + GLUT_KEY_SHIFT_L) ||
      luabridge_keyboard_was_released(GLUT_NULL + GLUT_KEY_SHIFT_R);
    break;
  case SPECIAL_CTRL:
    result =
      luabridge_keyboard_was_released(GLUT_NULL + GLUT_KEY_CTRL_L) ||
      luabridge_keyboard_was_released(GLUT_NULL + GLUT_KEY_CTRL_R);
    break;
  case SPECIAL_ALT:
    result =
      luabridge_keyboard_was_released(GLUT_NULL + GLUT_KEY_ALT_L) ||
      luabridge_keyboard_was_released(GLUT_NULL + GLUT_KEY_ALT_R);
    break;
  default:
    result = luabridge_keyboard_was_released(k);
    break;
  }
  lua_pushboolean(L, result);
  return 1;
}

static const struct luaL_Reg keylib[] = {
  {"of", l_key_of},
  {NULL, NULL}
};

static const struct KeyReg keylibc[] = {
  {"F1", GLUT_NULL + GLUT_KEY_F1},
  {"F2", GLUT_NULL + GLUT_KEY_F2},
  {"F3", GLUT_NULL + GLUT_KEY_F3},
  {"F4", GLUT_NULL + GLUT_KEY_F4},
  {"F5", GLUT_NULL + GLUT_KEY_F5},
  {"F6", GLUT_NULL + GLUT_KEY_F6},
  {"F7", GLUT_NULL + GLUT_KEY_F7},
  {"F8", GLUT_NULL + GLUT_KEY_F8},
  {"F9", GLUT_NULL + GLUT_KEY_F9},
  {"F10", GLUT_NULL + GLUT_KEY_F10},
  {"F11", GLUT_NULL + GLUT_KEY_F11},
  {"F12", GLUT_NULL + GLUT_KEY_F12},
  {"LEFT", GLUT_NULL + GLUT_KEY_LEFT},
  {"UP", GLUT_NULL + GLUT_KEY_UP},
  {"RIGHT", GLUT_NULL + GLUT_KEY_RIGHT},
  {"DOWN", GLUT_NULL + GLUT_KEY_DOWN},
  {"PAGE_UP", GLUT_NULL + GLUT_KEY_PAGE_UP},
  {"PAGE_DOWN", GLUT_NULL + GLUT_KEY_PAGE_DOWN},
  {"HOME", GLUT_NULL + GLUT_KEY_HOME},
  {"END", GLUT_NULL + GLUT_KEY_END},
  {"INSERT", GLUT_NULL + GLUT_KEY_INSERT},
  {"NUM_LOCK", GLUT_NULL + GLUT_KEY_NUM_LOCK},
  {"BEGIN", GLUT_NULL + GLUT_KEY_BEGIN},
  {"DELETE", GLUT_NULL + GLUT_KEY_DELETE},
  {"SHIFT_L", GLUT_NULL + GLUT_KEY_SHIFT_L},
  {"SHIFT_R", GLUT_NULL + GLUT_KEY_SHIFT_R},
  {"CTRL_L", GLUT_NULL + GLUT_KEY_CTRL_L},
  {"CTRL_R", GLUT_NULL + GLUT_KEY_CTRL_R},
  {"ALT_L", GLUT_NULL + GLUT_KEY_ALT_L},
  {"ALT_R", GLUT_NULL + GLUT_KEY_ALT_R},
  {"SHIFT", SPECIAL_SHIFT},
  {"CTRL", SPECIAL_CTRL},
  {"ALT", SPECIAL_ALT},
  {NULL, GLUT_NULL}
};

static const struct luaL_Reg keyboardlib[] = {
  {"is_down", l_is_down},
  {"is_pressed", l_is_pressed},
  {"is_released", l_is_released},
  {NULL, NULL}
};

void luabridge_keyboard_define(lua_State* L) {
  luaL_newmetatable(L, t_Keyboard);
  luaL_setfuncs(L, keyboardlib, 0);

  lua_setglobal(L, t_Keyboard);

  luaL_newmetatable(L, t_Key);
  for (const KeyReg* curr = keylibc; curr->name != NULL; curr++) {
    lua_pushstring(L, curr->name);
    luabridge_keyboard_push(L, curr->value);
    lua_rawset(L, -3);
  }
  luaL_setfuncs(L, keylib, 0);

  lua_setglobal(L, t_Key);

  lua_newtable(L);
  ref_keytable = luaL_ref(L, LUA_REGISTRYINDEX);
}

void luabridge_keyboard_set_state(lua_State* L, KeyboardKey k, bool state) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref_keytable);
  lua_pushboolean(L, state);
  lua_rawseti(L, -2, k);
  lua_pop(L, 1);

  if (state) {
    if (pressed_ptr < MAX_KEY_MEMORY)
      pressed[pressed_ptr++] = k;
  } else {
    if (released_ptr < MAX_KEY_MEMORY)
      released[released_ptr++] = k;
  }
}

bool luabridge_keyboard_get_state(lua_State* L, KeyboardKey k) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, ref_keytable);
  lua_rawgeti(L, -1, k);
  bool result = lua_toboolean(L, -1);
  lua_pop(L, 2);
  return result;
}

void luabridge_keyboard_reset_presses() {
  pressed_ptr = 0;
  released_ptr = 0;
}

bool luabridge_keyboard_was_pressed(KeyboardKey k) {
  for (int i = 0; i < pressed_ptr; i++) {
    if (pressed[i] == k)
      return true;
  }
  return false;
}

bool luabridge_keyboard_was_released(KeyboardKey k) {
  for (int i = 0; i < released_ptr; i++) {
    if (released[i] == k)
      return true;
  }
  return false;
}
