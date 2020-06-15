#include "panel.h"

Panel::Panel(const point& Location, const double& Length, const double& Width, const GlutRGB& Top, const GlutRGB& Bottom, const double& ButtonShape, const GlutRGB& ButtonColor) :
  location(Location), length(Length), width(Width), top(Top), bottom(Bottom), buttonShape(ButtonShape), buttonColor(ButtonColor)
{
  vertex = { { location.x - length / 2, location.y - width / 2 }, { location.x + length / 2, location.y - width / 2 },{ location.x + length / 2, location.y + width / 2 }, { location.x - length / 2, location.y + width / 2 } };
}

void Panel::Draw(void)
{
  glBegin(GL_POLYGON);
  glColor3d(top.red, top.green, top.blue);
  for (unsigned int i = 0; i < vertex.size() / 2; i++)
    glVertex3d(vertex[i].x, vertex[i].y, 0);
  glColor3d(bottom.red, bottom.green, bottom.blue);
  for (unsigned int i = vertex.size() / 2; i < vertex.size(); i++)
    glVertex3d(vertex[i].x, vertex[i].y, 0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 0.0, 0.0);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glEnd();
}

Panel_Top::Panel_Top(const point& Location, const double& Length, const double& Width, const GlutRGB& Top, const GlutRGB& Bottom, const double& ButtonShape, const GlutRGB& ButtonColor, const int& ColorLine, const int& ColorRow) :
  Panel(Location, Length, Width, Top, Bottom, ButtonShape, ButtonColor), colorLine(ColorLine), colorRow(ColorRow),
  _pencil({ ButtonShape / 2, ButtonShape / 2 }, ButtonShape, ButtonShape, ButtonColor),
  _eraser({ 3 * ButtonShape / 2, ButtonShape / 2 }, ButtonShape, ButtonShape, ButtonColor),
  _line({ 5 * ButtonShape / 2, ButtonShape / 2 }, ButtonShape, ButtonShape, ButtonColor),
  _rectangle({ 7 * ButtonShape / 2, ButtonShape / 2 }, ButtonShape, ButtonShape, ButtonColor),
  _circle({ 9 * ButtonShape / 2, ButtonShape / 2 }, ButtonShape, ButtonShape, ButtonColor),
  colors({ 5 * ButtonShape + ColorLine / 2 * ButtonShape / 2, ButtonShape / 2 }, ColorLine / 2 * ButtonShape, ButtonShape, ButtonColor, ColorLine, ColorRow,
    { {0, 0, 0}, {128, 128, 128}, {128, 0, 0}, {255, 0, 0}, {255, 69, 0}, {255, 255, 0}, {0, 128, 0}, {30, 144, 255}, {0, 0, 255}, {128, 0, 128}, {255, 255, 255}, {211, 211, 211}, {139, 69, 19}, {255, 105, 180}, {255, 165, 0}, {222, 184, 135}, {0, 255, 0}, {0, 255, 255}, {123, 104, 238}, {70, 130, 180} }),
  _brush_({ 3 * Length / 4, ButtonShape / 2 }, Length / 2 - 20, ButtonShape / 4, ButtonShape / 4, buttonColor)
{
  buttons.push_back(&_pencil);
  buttons.push_back(&_eraser);
  buttons.push_back(&_line);
  buttons.push_back(&_rectangle);
  buttons.push_back(&_circle);
}

void Panel_Top::Draw(void)
{
  Panel::Draw();
  for (auto i : buttons)
    i->Draw();
  colors.Draw();
  _brush_.Draw();
}

Panel_Bottom::Panel_Bottom(const point& Location, const double& Length, const double& Width, const GlutRGB& Top, const GlutRGB& Bottom, const double& ButtonShape, const GlutRGB& ButtonColor) :
  Panel(Location, Length, Width, Top, Bottom, ButtonShape, ButtonColor),
  _new({ ButtonShape, Location.y }, 2 * ButtonShape, ButtonShape, ButtonColor),
  _open({ 3 * ButtonShape, Location.y }, 2 * ButtonShape, ButtonShape, ButtonColor),
  _save({ 5 * ButtonShape, Location.y }, 2 * ButtonShape, ButtonShape, ButtonColor),
  _zoom_({ 6 * ButtonShape + (Length - 6 * ButtonShape) / 4, Location.y }, (Length - 6 * ButtonShape) / 2 - 20, ButtonShape / 4, ButtonShape / 4, buttonColor),
  name({ Length - (Length - 6 * buttonShape) / 4, Location.y }, ButtonColor, 0, Length)
{
  buttons.push_back(&_new);
  buttons.push_back(&_open);
  buttons.push_back(&_save);
}

void Panel_Bottom::Draw(void)
{
  Panel::Draw();
  for (auto i : buttons)
    i->Draw();
  _zoom_.Draw();
  name.Draw();
}