
#include "text.h"

#include <GL/glut.h>

void glbridge_draw_text(float x, float y, void* font, const char* string) {
  glRasterPos3f(x, y, 0.0);
  for (const char* c = string; *c != 0; c++) {
    glutBitmapCharacter(font, *c);
  }
}
