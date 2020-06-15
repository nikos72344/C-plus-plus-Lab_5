#include "screen.h"

Screen* MAIN_SCREEN = 0;

void Display(void) { MAIN_SCREEN->Display(); }

void Mouse(int button, int state, int x, int y) { MAIN_SCREEN->Mouse(button, state, x, y); }

void ActiveMotion(int x, int y) { MAIN_SCREEN->ActiveMotion(x, y); }

void Keyboard(unsigned char key, int x, int y) { MAIN_SCREEN->Keyboard(key, x, y); }

void SetMainDisplay(void)
{
  glMatrixMode(GL_PROJECTION);
  glOrtho(0, MAIN_SCREEN->Length(), MAIN_SCREEN->Width(), 0, 1, -1);
}

int main(int argc, char* argv[])
{
  int length = 1000, width = 9 * length / 16, x = 50, y = 50;
  string title = "Paint";
  Screen main(length, width);
  MAIN_SCREEN = &main;

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(length, width);
  glutInitWindowPosition(x, y);
  glutCreateWindow(title.data());

  SetMainDisplay();
  glutDisplayFunc(Display);
  glutMouseFunc(Mouse);
  glutMotionFunc(ActiveMotion);
  glutKeyboardFunc(Keyboard);

  glutMainLoop();

  return 0;
}