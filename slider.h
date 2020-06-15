#ifndef __SLIDER_H
#define __SLIDER_H

#include "data.h"
#include "button.h"
#include <vector>

class Rail
{
private:
  vector<point> vertex;
  GlutRGB color;
protected:
  point location;
  double length, width;
public:
  Rail(const point& Location, const double& Length, const double& Width, const GlutRGB& Color);
  void Draw(void);
};

class Button_Slider : public Button
{
protected:
  sliderStatus status;
  void SetX(const int& X) { location.x = X; }
public:
  Button_Slider(const point& Location, const double& Length, const double& Width, const GlutRGB& Color);
  virtual void Draw(void) override;
};

class Slider : public Button_Slider, public Rail
{
private:
  double value;
  void ValueUpdate(void);
public:
  Slider(const point& Location, const double& Length, const double& Width, const double& ButtonLength, const GlutRGB& Color);
  const double& Value(void) { return value; }
  const sliderStatus& Status(void) { return Button_Slider::status; }
  void SetStatus(const sliderStatus& Status);
  void ButtonUpdate(int X);
  void Draw(void);
};

#endif