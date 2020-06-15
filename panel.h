#ifndef __PANEL_H
#define __PANEL_H

#include "button.h"
#include "color.h"
#include "data.h"
#include "field.h"
#include "slider.h"
#include <vector>

class Panel
{
private:
  vector<point> vertex;
  point location;
  double length, width;
  GlutRGB top, bottom;
protected:
  double buttonShape;
  GlutRGB buttonColor;
  vector<Button*> buttons;
public:
  Panel(const point& Location, const double& Length, const double& Width, const GlutRGB& Top, const GlutRGB& Bottom, const double& ButtonShape, const GlutRGB& ButtonColor);
  const vector<Button*>& Buttons(void) { return buttons; }
  virtual Slider& GetSlider(void) = 0;
  virtual void Draw(void);
};

class Panel_Top : public Panel
{
private:
  Button_Pencil _pencil;
  Button_Eraser _eraser;
  Button_Line _line;
  Button_Rectangle _rectangle;
  Button_Circle _circle;
  int colorLine, colorRow;
  ColorBar colors;
  Slider _brush_;
public:
  Panel_Top(const point& Location, const double& Length, const double& Width, const GlutRGB& Top, const GlutRGB& Bottom, const double& ButtonShape, const GlutRGB& ButtonColor, const int& ColorLine, const int& ColorRow);
  Slider& GetSlider(void) { return _brush_; }
  ColorBar& GetColorBar(void) { return colors; }
  virtual void Draw(void) override;
};

class Panel_Bottom : public Panel
{
private:
  Button_New _new;
  Button_Open _open;
  Button_Save _save;
  Slider _zoom_;
  Field name;
public:
  Panel_Bottom(const point& Location, const double& Length, const double& Width, const GlutRGB& Top, const GlutRGB& Bottom, const double& ButtonShape, const GlutRGB& ButtonColor);
  Slider& GetSlider(void) { return _zoom_; }
  Field& GetField(void) { return name; }
  Button_New& GetButtonNew(void) { return _new; }
  Button_Open& GetButtonOpen(void) { return _open; }
  Button_Save& GetButtonSave(void) { return _save; }
  virtual void Draw(void) override;
};

#endif