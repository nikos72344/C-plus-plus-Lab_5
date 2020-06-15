#include "canvas.h"

Canvas::Canvas(const point& Location, const double& Length, const double& Width, const double& Zoom) : location(Location), length(Length), width(Width), color({ 255, 255, 255 }), zoom(Zoom), center(location)
{
  zoomLength = length * zoom;
  zoomWidth = width * zoom;
  vector<GlutRGB> temp(length, color);
  for (int i = 0; i < (int)(width); i++)
    points.push_back(temp);
  vertex = { {location.x - length / 2, location.y - width / 2}, {location.x + length / 2, location.y - width / 2}, {location.x + length / 2, location.y + width / 2}, {location.x - length / 2, location.y + width / 2} };
}

void Canvas::Draw(void)
{
  int top = (int)(center.y - zoomWidth / 2 - (location.y - width / 2)),
    bottom = (int)(center.y + zoomWidth / 2 - (location.y - width / 2)),
    left = (int)(center.x - zoomLength / 2 - (location.x - length / 2)),
    rigth = (int)(center.x + zoomLength / 2 - (location.x - length / 2));
  if (top == bottom && left == rigth)
  {
    top--;
    left--;
  }
  double  tempX = length / (rigth - left),
    tempY = width / (bottom - top);
  for (int i = top; i < bottom; i++)
    for (int j = left; j < rigth; j++)
    {
      point tempPos = { location.x - length / 2 + tempX * (j - left) + tempX / 2 , location.y - width / 2 + tempY * (i - top) + tempY / 2 };
      glBegin(GL_POLYGON);
      glColor3d(points[i][j].red, points[i][j].green, points[i][j].blue);
      glVertex3d(tempPos.x - tempX / 2, tempPos.y - tempY / 2, 0);
      glVertex3d(tempPos.x + tempX / 2, tempPos.y - tempY / 2, 0);
      glVertex3d(tempPos.x + tempX / 2, tempPos.y + tempY / 2, 0);
      glVertex3d(tempPos.x - tempX / 2, tempPos.y + tempY / 2, 0);
      glEnd();
    }
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 0.0, 0.0);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glVertex3d(vertex[0].x, vertex[0].y, 0);
  glEnd();
}

bool Canvas::IsClick(const int& X, const int& Y)
{
  if (X <= location.x + length / 2 && X >= location.x - length / 2 && Y <= location.y + width / 2 && Y >= location.y - width / 2)
    return true;
  return false;
}

void Canvas::CenterUpdate(const point& Center)
{
  point dif;
  dif.x = Center.x - previous.x;
  dif.y = Center.y - previous.y;
  center.x -= dif.x;
  center.y -= dif.y;
  previous = Center;
  if (center.x + zoomLength/2 > location.x + length / 2)
  {
    center.x = location.x + length / 2 - zoomLength / 2;
    previous.x=center.x;
  }
  if (center.x - zoomLength / 2 < location.x - length / 2)
  {
    center.x = location.x - length / 2 + zoomLength / 2;
    previous.x = center.x;
  }
  if (center.y - zoomWidth / 2 < location.y - width / 2)
  {
    center.y = location.y - width / 2 + zoomWidth / 2;
    previous.y = center.y;
  }
  if (center.y + zoomWidth / 2 > location.y + width / 2)
  {
    center.y = location.y + width / 2 - zoomWidth / 2;
    previous.y = center.y;
  }
}

void Canvas::SetDefault(void)
{
  for (auto& i : points)
    for (auto& j : i)
      j = color;
}

void Canvas::Transform(const point& Point, int* i, int* j)
{
  point one = { Point.x - (int)((location.x - length / 2)), Point.y - (int)((location.y - width / 2)) };
  if (one.x <= 0 || one.x >= length || one.y <= 0 || one.y >= width)
    return;
  int top = (int)(center.y - zoomWidth / 2 - (location.y - width / 2)),
    bottom = (int)(center.y + zoomWidth / 2 - (location.y - width / 2)),
    left = (int)(center.x - zoomLength / 2 - (location.x - length / 2)),
    rigth = (int)(center.x + zoomLength / 2 - (location.x - length / 2));
  double  tempX = length / (rigth - left),
    tempY = width / (bottom - top);
  *j = (int)(one.x / tempX + left);
  *i = (int)(one.y / tempY + top);
}

void Canvas::SetPointColor(const point& Point, const GlutRGB& Color)
{
  int i = 0, j = 0;
  Transform(Point, &i, &j);
  points[i][j] = Color;
}

const GlutRGB& Canvas::PointColor(const point& Point)
{
  int i = 0, j = 0;
  Transform(Point, &i, &j);
  return points[i][j];
}