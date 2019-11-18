
#ifndef GAME_GLBRIDGE_CALLBACK_H
#define GAME_GLBRIDGE_CALLBACK_H

typedef struct {
  void (*ondraw)();
} GLBridgeCallbacks;

void glbridge_init_callbacks();

#endif // GAME_GL_CALLBACK_H
