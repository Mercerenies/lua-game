
#include "keyboard.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <GL/glut.h>

#include <stdbool.h>

const char* t_Keyboard = "Keyboard";

const char* t_Key = "Key";

typedef struct KeyReg {
  const char* name;
  KeyboardKey value;
} KeyReg;

KeyboardKey luabridge_keyboard_make_normal(unsigned char ch) {
  KeyboardKey k;
  k.is_special = false;
  k.normal = ch;
  return k;
}

KeyboardKey luabridge_keyboard_make_special(int ch) {
  KeyboardKey k;
  k.is_special = true;
  k.special = ch;
  return k;
}

KeyboardKey* luabridge_keyboard_push(lua_State* L, KeyboardKey k) {
  KeyboardKey* table = lua_newuserdata(L, sizeof(KeyboardKey));
  luaL_getmetatable(L, t_Key);
  lua_setmetatable(L, -2);
  *table = k;
  return table;
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

// -2, +1, e
int l_eq(lua_State* L) {
  KeyboardKey* a = luaL_checkudata(L, 1, t_Key);
  KeyboardKey* b = luaL_checkudata(L, 2, t_Key);
  if (a->is_special != b->is_special) {
    lua_pushboolean(L, false);
    return 1;
  }
  if (a->is_special) {
    lua_pushboolean(L, a->special == b->special);
  } else {
    lua_pushboolean(L, a->normal == b->normal);
  }
  return 1;
}

static const struct luaL_Reg keylib[] = {
  {"of", l_key_of},
  {"__eq", l_eq},
  {NULL, NULL}
};

static const struct KeyReg keylibc[] = {
  {"F1", {true, {.special = GLUT_KEY_F1}}},
  {"F2", {true, {.special = GLUT_KEY_F2}}},
  {"F3", {true, {.special = GLUT_KEY_F3}}},
  {"F4", {true, {.special = GLUT_KEY_F4}}},
  {"F5", {true, {.special = GLUT_KEY_F5}}},
  {"F6", {true, {.special = GLUT_KEY_F6}}},
  {"F7", {true, {.special = GLUT_KEY_F7}}},
  {"F8", {true, {.special = GLUT_KEY_F8}}},
  {"F9", {true, {.special = GLUT_KEY_F9}}},
  {"F10", {true, {.special = GLUT_KEY_F10}}},
  {"F11", {true, {.special = GLUT_KEY_F11}}},
  {"F12", {true, {.special = GLUT_KEY_F12}}},
  {"LEFT", {true, {.special = GLUT_KEY_UP}}},
  {"UP", {true, {.special = GLUT_KEY_LEFT}}},
  {"RIGHT", {true, {.special = GLUT_KEY_RIGHT}}},
  {"DOWN", {true, {.special = GLUT_KEY_DOWN}}},
  {"PAGE_UP", {true, {.special = GLUT_KEY_PAGE_UP}}},
  {"PAGE_DOWN", {true, {.special = GLUT_KEY_PAGE_DOWN}}},
  {"HOME", {true, {.special = GLUT_KEY_HOME}}},
  {"END", {true, {.special = GLUT_KEY_END}}},
  {"INSERT", {true, {.special = GLUT_KEY_INSERT}}},
  {NULL, {}}
};

static const struct luaL_Reg keyboardlib[] = {
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
}

