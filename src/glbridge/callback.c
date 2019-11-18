
#include "callback.h"

#include <GL/glut.h>

///// static GLBridgeCallbacks callbacks;

static void cb_render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
