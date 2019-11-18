
#ifndef GAME_LUABRIDGE_ROOM_H
#define GAME_LUABRIDGE_ROOM_H

#include <lua.h>

// To be perfectly clear, this file is definitely getting rewritten as
// we refine the API. I just need a simple place to put the object
// list right now while I don't care about having actual rooms in the
// game. When I do care, I'll make this more mature and feature-ful.

const char* t_Room;

// -0, +1, -
int luabridge_room_getobjects(lua_State* L);

void luabridge_room_define(lua_State* L);

#endif // GAME_LUABRIDGE_ROOM_H
