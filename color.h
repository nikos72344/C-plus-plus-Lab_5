#ifndef __COLOR_H
#define __COLOR_H

#include "data.h"
#include "button.h"
#include <vector>

class Button_Color : public Button
{
private:
  vector<point> vertex;
  GlutRGB color;
public:
  Button_Color(const point& Location, const double& Length, const double& Width, const GlutRGB& BackgroundColor, const GlutRGB& Color);
  const GlutRGB& Color(void) { return color; }
  virtual void Draw(void) override;
};

class ColorBar
{
private:
  vector<point> vertex;
  point location;
  double length, width;
  GlutRGB color;
  vector<Button_Color> buttons;
  int line, row;
public:
  ColorBar(const point& Location, const double& Length, const double& Width, const GlutRGB& Color, const int& Line, const int& Row, const vector<GlutRGB>& Colors);
  const point& Location(void) { return location; }
  const double& Length(void) { return length; }
  const double& Width(void) { return width; }
  vector<Button_Color>& Buttons(void) { return buttons; }
  void Draw(void);
};

#endif