
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

void luabridge_keyboard_set_state(lua_State* L, KeyboardKey k, bool state);

bool luabridge_keyboard_get_state(lua_State* L, KeyboardKey k);

void luabridge_keyboard_reset_presses();

bool luabridge_keyboard_was_pressed(KeyboardKey k);

bool luabridge_keyboard_was_released(KeyboardKey k);

#endif // GAME_LUABRIDGE_KEYBOARD_H
