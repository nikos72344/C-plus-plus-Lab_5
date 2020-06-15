#ifndef __FIELD_H
#define __FIELD_H

#include "data.h"
#include "title.h"
#include <vector>

class Cursor
{
private:
  vector<point> vertex;
  point location;
  double length, width;
  GlutRGB color;
public:
  Cursor(const point& Location, const double& Width);
  void DataUpdate(const point& Location, const double& Width);
  void Draw(void);
};

class Field
{
private:
  vector<point> vertex;
  point location;
  double length, width;
  GlutRGB color;
  fieldStatus status;
  int left, rigth;
  Title content;
  Cursor cursor;
  void Background(void);
  void Update(void);
public:
  Field(const point& Location, const GlutRGB& Color, const int& Left, const int& Rigth);
  const double& Length(void) { return length; }
  const double& Width(void) { return width; }
  void SetLocation(const point& Location);
  void SetStatus(const fieldStatus& Status) { status = Status; }
  bool IsClick(const int& X, const int& Y);
  Title& Content(void) { return content; }
  void Input(const unsigned char& Key);
  void Draw(void);
};

#endif