
#ifndef GAME_LUABRIDGE_KEYBOARD_H
#define GAME_LUABRIDGE_KEYBOARD_H

#include <lua.h>

#include <stdbool.h>

typedef long KeyboardKey;

const char* t_Keyboard;

const char* t_Key;

KeyboardKey luabridge_keyboard_make_normal(unsigned char ch);

KeyboardKey luabridge_keyboard_make_special(int ch);

// -0, +1, -
void luabridge_keyboard_push(lua_State* L, KeyboardKey k);

void luabridge_keyboard_define(lua_State* L);

#endif // GAME_LUABRIDGE_KEYBOARD_H
