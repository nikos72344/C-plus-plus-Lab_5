#include "slider.h"

Rail::Rail(const point& Location, const double& Length, const double& Width, const GlutRGB& Color) : location(Location), length(Length), width(Width), color(Color)
{
  vertex = { {location.x - length / 2, location.y - width / 2}, {location.x + length / 2, location.y - width / 2}, {location.x + length / 2, location.y + width / 2}, {location.x - length / 2, location.y + width / 2} };
}

void Rail::Draw(void)
{
  glBegin(GL_POLYGON);
  glColor3d(color.red, color.green, color.blue);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 0.0, 0.0);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glVertex3d(vertex[0].x, vertex[0].y, 0);
  glEnd();
}

Button_Slider::Button_Slider(const point& Location, const double& Length, const double& Width, const GlutRGB& Color) : Button(Location, Length, Width, Color, none), status(inaction) {}

void Button_Slider::Draw(void)
{
  Background();
}

Slider::Slider(const point& Location, const double& Length, const double& Width, const double& ButtonLength, const GlutRGB& Color) :
  Button_Slider(Location, ButtonLength, 2*ButtonLength, Color),
  Rail(Location, Length, Width, Color)
{
  ValueUpdate();
}

void Slider::ValueUpdate(void)
{
  value = (Button_Slider::location.x - (Rail::location.x - Rail::length / 2)) / Rail::length;
}

void Slider::SetStatus(const sliderStatus& Status)
{
  Slider::status = Status;
  switch (Status)
  {
  case inaction: Button_Slider::SetPower(off); break;
  case movement: Button_Slider::SetPower(on); break;
  }
  ValueUpdate();
}

void Slider::ButtonUpdate(int X)
{
  if (Button_Slider::status == movement)
  {
    if (X > (Rail::location.x + Rail::length / 2))
      X = Rail::location.x + Rail::length / 2;
    if (X < Rail::location.x - Rail::length / 2)
      X = Rail::location.x - Rail::length / 2;
    int dif = X - Button_Slider::location.x;
    Button_Slider::SetX(X);
    for (auto& i : Button_Slider::vertex)
      i.x += dif;
    ValueUpdate();
  }
}

void Slider::Draw(void)
{
  Rail::Draw();
  Button_Slider::Draw();
}