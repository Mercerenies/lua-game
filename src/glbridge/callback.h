
#ifndef GAME_GLBRIDGE_CALLBACK_H
#define GAME_GLBRIDGE_CALLBACK_H

typedef struct {
  void* state; // Borrowed
  void (*ondraw)(void* state);
  void (*onresize)(void* state, int w, int h);
  void (*onstep)(void* state);
  void (*onkey)(void* state, unsigned char key, int x, int y);
  void (*onspeckey)(void* state, int key, int x, int y);
  void (*onkeyup)(void* state, unsigned char key, int x, int y);
  void (*onspeckeyup)(void* state, int key, int x, int y);
} GLBridgeCallbacks;

void glbridge_init_callbacks();

// Takes NO ownership of its pointer!
void glbridge_set_callbacks(const GLBridgeCallbacks* cb);

#endif // GAME_GLBRIDGE_CALLBACK_H
