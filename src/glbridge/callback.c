
#include "callback.h"

#include <GL/glut.h>

static const GLBridgeCallbacks* callbacks = NULL;

static void cb_render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (callbacks != NULL)
    callbacks->ondraw(callbacks->state);

  glutSwapBuffers();
}

static void cb_resize(int w, int h) {
  glViewport(0, 0, w, h);
  gluOrtho2D(0, 0, w, h);
}

void glbridge_init_callbacks() {
  glutDisplayFunc(cb_render);
  glutReshapeFunc(cb_resize);
}

void glbridge_set_callbacks(const GLBridgeCallbacks* cb) {
  callbacks = cb;
}
