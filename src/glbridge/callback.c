
#include "callback.h"

#include <GL/glut.h>

#include <stdbool.h>

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

static void cb_keyboard(unsigned char key, int x, int y) {
  if (callbacks != NULL)
    callbacks->onkey(callbacks->state, key, x, y);
}

static void cb_special_keyboard(int key, int x, int y) {
  if (callbacks != NULL)
    callbacks->onspeckey(callbacks->state, key, x, y);
}

static void cb_keyboard_up(unsigned char key, int x, int y) {
  if (callbacks != NULL)
    callbacks->onkeyup(callbacks->state, key, x, y);
}

static void cb_special_keyboard_up(int key, int x, int y) {
  if (callbacks != NULL)
    callbacks->onspeckeyup(callbacks->state, key, x, y);
}

void glbridge_init_callbacks() {
  glutDisplayFunc(cb_render);
  glutReshapeFunc(cb_resize);
  glutTimerFunc(MILLIS_PER_FRAME, cb_timer, 0);
  glutKeyboardFunc(cb_keyboard);
  glutSpecialFunc(cb_special_keyboard);
  glutKeyboardUpFunc(cb_keyboard_up);
  glutSpecialUpFunc(cb_special_keyboard_up);
  glutIgnoreKeyRepeat(true);
}

void glbridge_set_callbacks(const GLBridgeCallbacks* cb) {
  callbacks = cb;
}
