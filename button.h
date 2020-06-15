#ifndef __BUTTON_H
#define __BUTTON_H

#include "canvas.h"
#include "data.h"
#include "title.h"
#include <vector>
#include <iostream>
#include <fstream>

class Button
{
private:
  powerStatus power;
  brushType brush;
  GlutRGB color, pressing;
  void SetColor(void);
protected:
  vector<point> vertex;
  point location;
  double length, width;
  void Background(void);
public:
  Button(const point& Location, const double& Length, const double& Width, const GlutRGB& Color, const brushType& Brush);
  const brushType& Brush(void) { return brush; }
  const powerStatus& Power(void) { return power; }
  bool IsClick(const int& X, const int& Y);
  void SetPower(const powerStatus& Status) { power = Status; }
  virtual void Draw(void) = 0;
};

class Button_Pencil : public Button
{
private:
  vector<point> vertex;
  double angle;
  GlutRGB nose, body, eraser;
public:
  Button_Pencil(const point& Location, const double& Length, const double& Width, const GlutRGB& Color);
  virtual void Draw(void) override;
};

class Button_Eraser : public Button
{
private:
  vector<point> vertex;
  GlutRGB color;
public:
  Button_Eraser(const point& Location, const double& Length, const double& Width, const GlutRGB& Color);
  virtual void Draw(void) override;
};

class Button_Line : public Button
{
private:
  vector<point> vertex;
  GlutRGB color;
public:
  Button_Line(const point& Location, const double& Length, const double& Width, const GlutRGB& Color);
  virtual void Draw(void) override;
};

class Button_Rectangle : public Button
{
private:
  vector<point> vertex;
  GlutRGB color;
public:
  Button_Rectangle(const point& Location, const double& Length, const double& Width, const GlutRGB& Color);
  virtual void Draw(void) override;
};

class Button_Circle : public Button
{
private:
  double radius;
  int number;
  GlutRGB color;
public:
  Button_Circle(const point& Location, const double& Length, const double& Width, const GlutRGB& Color);
  virtual void Draw(void) override;
};

class Button_New : public Button
{
private:
  Title content;
public:
  Button_New(const point& Location, const double& Length, const double& Width, const GlutRGB& Color);
  void New(Canvas& _Canvas);
  virtual void Draw(void) override;
};

class Button_Open : public Button
{
private:
  Title content;
public:
  Button_Open(const point& Location, const double& Length, const double& Width, const GlutRGB& Color);
  void Open(const string& Name, const vector<vector<GlutRGB>>& Array);
  virtual void Draw(void) override;
};

class Button_Save : public Button
{
private:
  Title content;
public:
  Button_Save(const point& Location, const double& Length, const double& Width, const GlutRGB& Color);
  void Save(const string& Name, const vector<vector<GlutRGB>>& Array);
  virtual void Draw(void) override;
};

#endif