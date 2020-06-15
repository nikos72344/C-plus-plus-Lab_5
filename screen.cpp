#include "screen.h"

Screen::Screen(const double& WinLength, const double& WinWidth) : length(WinLength), width(WinWidth), colorLine(10), colorRow(2), buttonShape(50), buttonColor({ 176, 224, 230 }), brush(none), brushSize(0.5), brushColor({ 0, 0, 0 }), _brushStatus(transfer),
top({ length / 2, buttonShape / 2 }, length, buttonShape, { 175, 238, 238 }, { 72, 209, 240 }, buttonShape, buttonColor, colorLine, colorRow),
bottom({ length / 2, width - buttonShape / 2 }, length, buttonShape, { 175, 238, 238 }, { 72, 209, 240 }, buttonShape, buttonColor),
canvas({ length / 2, width / 2 }, 16 * (width - 2 * buttonShape) / 9, width - 2 * buttonShape, 0.5),
_pencil({ 0, 0 }, 50 * brushSize, brushColor),
_eraser({ 0, 0 }, 50 * brushSize, canvas.Color()),
_line({ 0, 0 }, 50 * brushSize, brushColor),
_rectangle({ 0, 0 }, 50 * brushSize, brushColor),
_circle({ 0, 0 }, 50 * brushSize, brushColor)
{
  for (auto& i : top.Buttons())
    buttons.push_back(i);
  for (auto& i : bottom.Buttons())
    buttons.push_back(i);
  name = bottom.GetField().Content().Content();
}

void Screen::Background(void)
{
  glBegin(GL_QUADS);
  glColor3d(176 / 255.0, 224 / 255.0, 230 / 255.0);
  glVertex3d(0, 0, -1);
  glColor3d(72 / 255.0, 209 / 255.0, 240 / 255.0);
  glVertex3d(length, 0, -1);
  glColor3d(175 / 255.0, 238 / 255.0, 238 / 255.0);
  glVertex3d(length, width, -1);
  glColor3d(224 / 255.0, 255 / 255.0, 255 / 255.0);
  glVertex3d(0, width, -1);
  glEnd();
}

void Screen::Display(void)
{
  Background();
  top.Draw();
  bottom.Draw();
  canvas.Draw();
  glutSwapBuffers();
}

void Screen::Mouse(const int& Button, const int& State, const int& X, const int& Y)
{
  CanvasUpdate(Button, State, X, Y);
  FieldUpdate(Button, State, X, Y);
  ColorButtonsUpdate(Button, State, X, Y);
  SliderUpdate(Button, State, X, Y);
  ButtonsUpdate(Button, State, X, Y);
  glutPostRedisplay();
}

void Screen::ActiveMotion(const int& X, const int& Y)
{
  if (brush == none && canvas.IsClick(X, Y))
    canvas.CenterUpdate({ (double)X, (double)Y });
  BrushActiveUpdate(X, Y);
  SliderMovement(X);
  glutPostRedisplay();
}

void Screen::Keyboard(const unsigned char& Key, const int& x, const int& y)
{
  bottom.GetField().Input(Key);
  name = bottom.GetField().Content().Content();
  glutPostRedisplay();
}

void Screen::BrushActiveUpdate(const int& X, const int& Y)
{
  if(_brushStatus == painting)
    switch (brush)
    {
    case pencil: _pencil.SetColor(brushColor);
      _pencil.SetSize(50 * brushSize);
      _pencil.Draw({ (double)X, (double)Y }, canvas);
      break;
    case eraser: _eraser.SetSize(50 * brushSize);
      _eraser.Draw({ (double)X, (double)Y }, canvas);
      break;
    case line: _line.SetColor(brushColor);
      _line.SetSize(50 * brushSize);
      _line.PreDraw({ (double)X, (double)Y }, canvas);
      break;
    case rectangle: _rectangle.SetColor(brushColor);
      _rectangle.SetSize(50 * brushSize);
      _rectangle.PreDraw({ (double)X, (double)Y }, canvas);
      break;
    case circle: _circle.SetColor(brushColor);
      _circle.SetSize(50 * brushSize);
      _circle.PreDraw({ (double)X, (double)Y }, canvas);
    }
}

void Screen::CanvasUpdate(const int& Button, const int& State, const int& X, const int& Y)
{
  if (brush == none && canvas.IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_DOWN)
    canvas.SetPrevious({ (double)X, (double)Y });
  if (brush != none && canvas.IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_DOWN)
  {
    _brushStatus = painting;
    switch (brush)
    {
    case pencil: _pencil.SetLocation({ (double)X, (double)Y }); break;
    case eraser: _eraser.SetLocation({ (double)X, (double)Y }); break;
    case line: _line.SetLocation({ (double)X, (double)Y }); break;
    case rectangle: _rectangle.SetLocation({ (double)X, (double)Y }); break;
    case circle: _circle.SetLocation({ (double)X, (double)Y }); break;
    }
  }
  if (brush != none && canvas.IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_UP)
  {
    switch (brush)
    {
    case line: _line.SetColor(brushColor);
      _line.SetSize(50 * brushSize);
      _line.Draw({ (double)X, (double)Y }, canvas);
      break;
    case rectangle: _rectangle.SetColor(brushColor);
      _rectangle.SetSize(50 * brushSize);
      _rectangle.Draw({ (double)X, (double)Y }, canvas);
      break;
    case circle: _circle.SetColor(brushColor);
      _circle.SetSize(50 * brushSize);
      _circle.Draw({ (double)X, (double)Y }, canvas);
    }
    _brushStatus = transfer;
  }
}

void Screen::ColorButtonsUpdate(const int& Button, const int& State, const int& X, const int& Y)
{
  for (auto& i : top.GetColorBar().Buttons())
  {
    if (i.IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_DOWN)
    {
      i.SetPower(on);
      return;
    }
    if (i.IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_UP)
    {
      SetBrushColor(i.Color());
      break;
    }
  }
  ColorPowerUpdate();
}

void Screen::FieldUpdate(const int& Button, const int& State, const int& X, const int& Y)
{
  Field& temp = bottom.GetField();
  if (temp.IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_UP)
  {
    temp.SetStatus(input);
    return;
  }
  if ( !temp.Content().Content().empty() && !temp.IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_UP)
    temp.SetStatus(output);
}

void Screen::SliderUpdate(const int& Button, const int& State, const int& X, const int& Y)
{
  auto& _top_ = top.GetSlider();
  if (_top_.IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_DOWN)
    _top_.SetStatus(movement);
  if (_top_.Status() == movement && Button == GLUT_LEFT && State == GLUT_UP)
    _top_.SetStatus(inaction);
  auto& _bottom_ = bottom.GetSlider();
  if (_bottom_.IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_DOWN)
    _bottom_.SetStatus(movement);
  if (_bottom_.Status() == movement && Button == GLUT_LEFT && State == GLUT_UP)
    _bottom_.SetStatus(inaction);
  brushSize = _top_.Value();
  canvas.SetZoom(_bottom_.Value());
}

void Screen::ButtonsUpdate(const int& Button, const int& State, const int& X, const int& Y)
{
  for (auto& i : buttons)
  {
    if (i->IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_DOWN)
    {
      i->SetPower(on);
      return;
    }
    if (i->IsClick(X, Y) && Button == GLUT_LEFT && State == GLUT_UP)
    {
      bottom.GetButtonNew().New(canvas);
      bottom.GetButtonOpen().Open(name, canvas.Array());
      bottom.GetButtonSave().Save(name, canvas.Array());
      if (i->Brush() == brush)
        brush = none;
      else
        SetBrush(i->Brush());
      break;
    }
  }
  ButtonsPowerUpdate();
}

bool GlutRGB::operator!=(const GlutRGB& Color)
{
  return red != Color.red || green != Color.green || blue != Color.blue;
}

void Screen::ColorPowerUpdate(void)
{
  for (auto& i : top.GetColorBar().Buttons())
  if (i.Power() == on && brushColor != i.Color())
    i.SetPower(off);
}

void Screen::ButtonsPowerUpdate(void)
{
  for (auto& i : buttons)
    if (i->Power() == on && brush != i->Brush() || i->Brush() == none)
      i->SetPower(off);
}

void Screen::SliderMovement(const int& X)
{
  top.GetSlider().ButtonUpdate(X);
  brushSize = top.GetSlider().Value();
  bottom.GetSlider().ButtonUpdate(X);
  canvas.SetZoom(bottom.GetSlider().Value());
}