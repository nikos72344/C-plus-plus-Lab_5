#include "color.h"

Button_Color::Button_Color(const point& Location, const double& Length, const double& Width, const GlutRGB& BackgroundColor, const GlutRGB& Color) : Button(Location, Length, Width, BackgroundColor, none), color(Color)
{
  vertex = { {location.x - 2 * length / 3 / 2, location.y - 2 * width / 3 / 2}, {location.x + 2 * length / 3 / 2, location.y - 2 * width / 3 / 2}, {location.x + 2 * length / 3 / 2, location.y + 2 * width / 3 / 2}, {location.x - 2 * length / 3 / 2, location.y + 2 * width / 3 / 2} };
}

void Button_Color::Draw(void)
{
  Background();
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

ColorBar::ColorBar(const point& Location, const double& Length, const double& Width, const GlutRGB& Color, const int& Line, const int& Row, const vector<GlutRGB>& Colors) : location(Location), length(Length), width(Width), color(Color), line(Line), row(Row)
{
  vertex = { {location.x - length / 2, location.y - width / 2}, {location.x + length / 2, location.y - width / 2}, {location.x + length / 2, location.y + width / 2}, {location.x - length / 2, location.y + width / 2} };
  double len = length / line ,
    wid = width / row;
  int l = 0;
  for (int i = 0; i < row; i++)
    for (int j = 0; j < line; j++)
      buttons.push_back({ { location.x - length / 2 + len * (j + 1) - len / 2, location.y - width / 2 + wid * (i + 1) - wid / 2 }, len, wid, color, Colors[l++] });
  buttons[0].SetPower(on);
}

void ColorBar::Draw(void)
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
  for (auto& i : buttons)
    i.Draw();
}