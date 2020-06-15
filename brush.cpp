#include "brush.h"

Brush::Brush(const point& Location, const int& Size, const GlutRGB& Color) : location(Location), color(Color), size(Size) {}

point Brush::Calculate(const double& X, const double& Y, const double& Angle)
{
  point temp;
  temp.x = X * cos(Angle) - Y * sin(Angle) + location.x;
  temp.y = X * sin(Angle) + Y * cos(Angle) + location.y;
  return temp;
}

Brush_Pencil::Brush_Pencil(const point& Location, const int& Size, const GlutRGB& Color) : Brush(Location, Size, Color) {}

void Brush_Pencil::Draw(const point& Point, Canvas& _Canvas)
{
  double angle = -atan2(location.y - Point.y, Point.x - location.x);
  double length = sqrt(pow(Point.x - location.x, 2) + pow(Point.y - location.y, 2));
  for (int l = 0; l < (int)(length); l++)
    for (int i = 0; i < size; i++)
    {
      point temp = Calculate(l, -size / 2 + i, angle);
      _Canvas.SetPointColor(temp, color);
    }
  location = Point;
}

Brush_Eraser::Brush_Eraser(const point& Location, const int& Size, const GlutRGB& Color) : Brush(Location, Size, Color) {}

void Brush_Eraser::Draw(const point& Point, Canvas& _Canvas)
{
  double angle = -atan2(location.y - Point.y, Point.x - location.x);
  double length = sqrt(pow(Point.x - location.x, 2) + pow(Point.y - location.y, 2));
  for (int l = 0; l < (int)(length); l++)
    for (int i = 0; i < size; i++)
    {
      point temp = Calculate(l, -size / 2 + i, angle);
      _Canvas.SetPointColor(temp, color);
    }
  location = Point;
}

Brush_Line::Brush_Line(const point& Location, const int& Size, const GlutRGB& Color) : Brush(Location, Size, Color) {}

void Brush_Line::PreDraw(const point& Point, Canvas& _Canvas)
{
  for (unsigned int i = 0; i < pointBackup.size(); i++)
    _Canvas.SetPointColor(pointBackup[i], colorBackup[i]);
  colorBackup.clear();
  pointBackup.clear();
  double angle = -atan2(location.y - Point.y, Point.x - location.x);
  double length = sqrt(pow(Point.x - location.x, 2) + pow(Point.y - location.y, 2));
  for(int l = 0; l < (int)(length); l++)
    for (int i = 0; i < size; i++)
    {
      point temp = Calculate(l, -size / 2 + i, angle);
      colorBackup.push_back(_Canvas.PointColor(temp));
      pointBackup.push_back(temp);
    }
  for (int l = 0; l < (int)(length); l++)
    for (int i = 0; i < size; i++)
      _Canvas.SetPointColor(Calculate(l, -size / 2 + i, angle), color);
}

void Brush_Line::Draw(const point& Point, Canvas& _Canvas)
{
  PreDraw(Point, _Canvas);
  colorBackup.clear();
  pointBackup.clear();
}

Brush_Rectangle::Brush_Rectangle(const point& Location, const int& Size, const GlutRGB& Color) : Brush(Location, Size, Color) {}

void Brush_Rectangle::PreDraw(const point& Point, Canvas& _Canvas)
{
  for (unsigned int i = 0; i < pointBackup.size(); i++)
    _Canvas.SetPointColor(pointBackup[i], colorBackup[i]);
  colorBackup.clear();
  pointBackup.clear();
  int length = abs(Point.x - location.x);
  int width = abs(Point.y - location.y);
  int signX = Point.x > location.x ? 1 : -1;
  int signY = Point.y > location.y ? 1 : -1;
  for (int i = 0; i < width; i++)
    for (int l = 0; l < length; l++)
    {
      if ((i >= size) && (i <= (width - size)) && (l >= size) && (l <= (length - size)))
      {
        l += length - 2 * size;
        continue;
      }
      point temp = { location.x + signX * l, location.y + signY * i };
      colorBackup.push_back(_Canvas.PointColor(temp));
      pointBackup.push_back(temp);
    }
  for (int i = 0; i < width; i++)
    for (int l = 0; l < length; l++)
    {
      if ((i >= size) && (i <= (width - size)) && (l >= size) && (l <= (length - size)))
      {
        l += length - 2 * size;
        continue;
      }
      point temp = { location.x + signX * l, location.y + signY * i };
      _Canvas.SetPointColor(temp, color);
    }
}

void Brush_Rectangle::Draw(const point& Point, Canvas& _Canvas)
{
  PreDraw(Point, _Canvas);
  colorBackup.clear();
  pointBackup.clear();
}

Brush_Circle::Brush_Circle(const point& Location, const int& Size, const GlutRGB& Color) : Brush(Location, Size, Color), number(360) {}

void Brush_Circle::PreDraw(const point& Point, Canvas& _Canvas)
{
  for (unsigned int i = 0; i < pointBackup.size(); i++)
    _Canvas.SetPointColor(pointBackup[i], colorBackup[i]);
  colorBackup.clear();
  pointBackup.clear();
  int radius = sqrt(pow(Point.x - location.x, 2) + pow(Point.y - location.y, 2)) / 2;
  int signX = Point.x > location.x ? 1 : -1;
  int signY = Point.y > location.y ? 1 : -1;
  point center = { location.x + signX * abs(Point.x - location.x) / 2, location.y + signY * abs(Point.y - location.y) / 2 };
  for (int i = 0; i < number; i++)
    for (int l = 0; l < size; l++)
    {
      point temp = { center.x + signX * (radius - size / 2 + l) * cos(2 * PI * i / number), center.y + signY * (radius - size / 2 + l) * sin(2 * PI * i / number) };
      colorBackup.push_back(_Canvas.PointColor(temp));
      pointBackup.push_back(temp);
    }
  for (int i = 0; i < number; i++)
    for (int l = 0; l < size; l++)
    {
      point temp = { center.x + signX * (radius - size / 2 + l) * cos(2 * PI * i / number), center.y + signY * (radius - size / 2 + l) * sin(2 * PI * i / number) };
      _Canvas.SetPointColor(temp, color);
    }
}

void Brush_Circle::Draw(const point& Point, Canvas& _Canvas)
{
  PreDraw(Point, _Canvas);
  colorBackup.clear();
  pointBackup.clear();
}