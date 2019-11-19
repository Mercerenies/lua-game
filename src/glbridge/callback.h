
#ifndef GAME_GLBRIDGE_CALLBACK_H
#define GAME_GLBRIDGE_CALLBACK_H

typedef struct {
  void* state; // Borrowed
  void (*ondraw)(void* state);
  void (*onresize)(void* state, int w, int h);
  void (*onstep)(void* state);
} GLBridgeCallbacks;

void glbridge_init_callbacks();

// Takes NO ownership of its pointer!
void glbridge_set_callbacks(const GLBridgeCallbacks* cb);

#endif // GAME_GLBRIDGE_CALLBACK_H
