#ifndef __CANVAS_H
#define __CANVAS_H

#include "data.h"
#include <vector>

class Brush;

class Canvas
{
private:
  vector<point> vertex;
  point location;
  double length, width;
  double zoom;
  GlutRGB color;
  point center;
  int zoomLength, zoomWidth;
  point previous;
  vector<vector<GlutRGB>> points;
  void Transform(const point& Point, int* i, int* j);
public:
  Canvas(const point& Location, const double& Length, const double& Width, const double& Zoom);
  vector<vector<GlutRGB>>& Array(void) { return points; }
  void SetZoom(const double& Zoom) { if (Zoom != zoom)center = location; zoom = Zoom; zoomLength = length * zoom; zoomWidth = width * zoom; }
  void SetDefault(void);
  bool IsClick(const int& X, const int& Y);
  void SetPointColor(const point& Point, const GlutRGB& Color);
  void SetPrevious(const point& Previous) { previous = Previous; }
  void CenterUpdate(const point& Center);
  const GlutRGB& Color(void) { return color; }
  const GlutRGB& PointColor(const point& Point);
  void Draw(void);
};

#endif