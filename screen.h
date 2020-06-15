#ifndef __SCREEN_H
#define __SCREEN_H

#include "brush.h"
#include "canvas.h"
#include "data.h"
#include "panel.h"
#include <vector>

class Screen
{
private:
  double length, width;
  brushType brush;
  brushStatus _brushStatus;
  double brushSize;
  GlutRGB brushColor;
  string name;
  int colorLine, colorRow;
  double buttonShape;
  GlutRGB buttonColor;
  Panel_Top top;
  Panel_Bottom bottom;
  Canvas canvas;
  vector<Button*> buttons;
  Brush_Pencil _pencil;
  Brush_Eraser _eraser;
  Brush_Line _line;
  Brush_Rectangle _rectangle;
  Brush_Circle _circle;
  void SliderMovement(const int& X);
  void BrushActiveUpdate(const int& X, const int& Y);
  void CanvasUpdate(const int& Button, const int& State, const int& X, const int& Y);
  void FieldUpdate(const int& Button, const int& State, const int& X, const int& Y);
  void ColorButtonsUpdate(const int& Button, const int& State, const int& X, const int& Y);
  void SliderUpdate(const int& Button, const int& State, const int& X, const int& Y);
  void ButtonsUpdate(const int& Button, const int& State, const int& X, const int& Y);
  void ColorPowerUpdate(void);
  void ButtonsPowerUpdate(void);
  void Background(void);
  void SetBrushColor(const GlutRGB& Color) { brushColor = Color; }
  void SetBrush(const brushType& Brush) { if (Brush != none) brush = Brush; }
public:
  Screen(const double& WinLength, const double& WinWidth);
  void Display(void);
  void Mouse(const int& Button, const int& State, const int& X, const int& Y);
  void ActiveMotion(const int& X, const int& Y);
  void Keyboard(const unsigned char& Key, const int& x, const int& y);
  int Length(void) { return length; }
  int Width(void) { return width; }
};

#endif