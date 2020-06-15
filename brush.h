#ifndef __BRUSH_H
#define __BRUSH_H

#include "canvas.h"
#include "data.h"

class Brush
{
protected:
  point location;
  GlutRGB color;
  int size;
  point Calculate(const double& X, const double& Y, const double& Angle);
public:
  Brush(const point& Location, const int& Size, const GlutRGB& Color);
  void SetSize(const int& Size) { size = Size; }
  void SetColor(const GlutRGB& Color) { color = Color; }
  void SetLocation(const point& Location) { location = Location; }
  virtual void Draw(const point& Point, Canvas& _Canvas) = 0;
};

class Brush_Pencil : public Brush
{
public:
  Brush_Pencil(const point& Location, const int& Size, const GlutRGB& Color);
  virtual void Draw(const point& Point, Canvas& _Canvas) override;
};

class Brush_Eraser : public Brush
{
public:
  Brush_Eraser(const point& Location, const int& Size, const GlutRGB& Color);
  virtual void Draw(const point& Point, Canvas& _Canvas) override;
};

class Brush_Line : public Brush
{
private:
  vector<GlutRGB> colorBackup;
  vector<point> pointBackup;
public:
  Brush_Line(const point& Location, const int& Size, const GlutRGB& Color);
  void PreDraw(const point& Point, Canvas& _Canvas);
  virtual void Draw(const point& Point, Canvas& _Canvas) override;
};

class Brush_Rectangle : public Brush
{
private:
  vector<GlutRGB> colorBackup;
  vector<point> pointBackup;
public:
  Brush_Rectangle(const point& Location, const int& Size, const GlutRGB& Color);
  void PreDraw(const point& Point, Canvas& _Canvas);
  virtual void Draw(const point& Point, Canvas& _Canvas) override;
};

class Brush_Circle : public Brush
{
private:
  vector<GlutRGB> colorBackup;
  vector<point> pointBackup;
  int number;
public:
  Brush_Circle(const point& Location, const int& Size, const GlutRGB& Color);
  void PreDraw(const point& Point, Canvas& _Canvas);
  virtual void Draw(const point& Point, Canvas& _Canvas) override;
};

#endif