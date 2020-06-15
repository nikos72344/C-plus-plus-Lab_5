#ifndef __DATA_H
#define __DATA_H

#include <gl/glut.h>

using namespace std;

const double PI = 3.1415926535897932384626433832795;

enum brushType
{
  none,
  pencil,
  eraser,
  line,
  rectangle,
  circle
};

enum powerStatus
{
  off,
  on
};

enum sliderStatus
{
  inaction,
  movement
};

enum fieldStatus
{
  input,
  output
};

enum brushStatus
{
  transfer,
  painting
};

struct point
{
  double x, y;
};

class GlutRGB
{
public:
  GLdouble red, green, blue;
  GlutRGB(GLdouble r = 0, GLdouble g = 0, GLdouble b = 0) : red(r / 255.0), green(g / 255.0), blue(b / 255.0) {}
  bool operator!=(const GlutRGB& Color);
};

#endif