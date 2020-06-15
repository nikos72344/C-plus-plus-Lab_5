#ifndef __TITLE_H
#define __TITLE_H

#include "data.h"
#include <string>

class Title
{
private:
  point location;
  double length, width;
  GlutRGB color;
  string content;
public:
  Title(const string& Content = "", const GlutRGB& Color = { 0, 0, 0 });
  void SetLocation(const point& Location) { location = Location; }
  void SetContent(const string& Content) { content = Content; }
  string& Content(void) { return content; }
  void Update(void);
  const double& Length(void) { return length; }
  const double& Width(void) { return width; }
  void Draw(void);
};

#endif