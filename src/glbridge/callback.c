
#include "callback.h"

#include <GL/glut.h>

#define MILLIS_PER_FRAME 16

static const GLBridgeCallbacks* callbacks = NULL;

static void cb_render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (callbacks != NULL)
    callbacks->ondraw(callbacks->state);

  glutSwapBuffers();
}

static void cb_resize(int w, int h) {

  if (callbacks != NULL)
    callbacks->onresize(callbacks->state, w, h);

  glViewport(0, 0, w, h);
  gluOrtho2D(0, 0, w, h);
}

static void cb_timer(int value) {

  if (callbacks != NULL) {
    callbacks->onstep(callbacks->state);
  }

  cb_render();
  glutTimerFunc(MILLIS_PER_FRAME, cb_timer, value);
}

void glbridge_init_callbacks() {
  glutDisplayFunc(cb_render);
  glutReshapeFunc(cb_resize);
  glutTimerFunc(MILLIS_PER_FRAME, cb_timer, 0);
}

void glbridge_set_callbacks(const GLBridgeCallbacks* cb) {
  callbacks = cb;
}
