
#include "core.h"

#include <GL/glut.h>

void glbridge_init_and_display(int* argcp, char** argv) {
  glutInit(argcp, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Hello World!");
}

void glbridge_main_loop() {
  glutMainLoop();
}
