#include "button.h"

Button::Button(const point& Location, const double& Length, const double& Width, const GlutRGB& Color, const brushType& Brush) : location(Location), length(Length), width(Width), power(off), color(Color), pressing({ 127, 127, 127 }), brush(Brush)
{
  vertex = { { location.x - length / 2, location.y - width / 2 }, { location.x + length / 2, location.y - width / 2 }, { location.x + length / 2, location.y + width / 2 }, { location.x - length / 2, location.y + width / 2 } };
}

void Button::SetColor(void)
{
	switch (power)
	{
  case on:
    if (pressing.red > 0) pressing.red *= -1;
    if (pressing.green > 0) pressing.green *= -1;
    if (pressing.blue > 0) pressing.blue *= -1;
    break;
  case off:
    if (pressing.red < 0) pressing.red *= -1;
    if (pressing.green < 0) pressing.green *= -1;
    if (pressing.blue < 0) pressing.blue *= -1;
    break;
	}
}

void Button::Background(void)
{
  SetColor();
  glBegin(GL_POLYGON);
  glColor3d(color.red + pressing.red, color.green + pressing.green, color.blue + pressing.blue);
  for (unsigned int i = 0; i < vertex.size() / 2; i++)
    glVertex3d(vertex[i].x, vertex[i].y, 0);
  glColor3d(color.red, color.green, color.blue);
  for (unsigned int i = vertex.size() / 2; i < vertex.size(); i++)
    glVertex3d(vertex[i].x, vertex[i].y, 0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 0.0, 0.0);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glVertex3d(vertex[0].x, vertex[0].y, 0);
  glEnd();
}

bool Button::IsClick(const int& X, const int& Y)
{
  if (X <= location.x + length / 2 && X >= location.x - length / 2 && Y <= location.y + width / 2 && Y >= location.y - width / 2)
    return true;
  return false;
}

Button_Pencil::Button_Pencil(const point& Location, const double& Length, const double& Width, const GlutRGB& Color) : Button(Location, Length, Width, Color, pencil), angle(-PI/4), nose(210, 180, 140), body(160, 82, 45), eraser(199, 21, 133)
{
  vector<point> dots = { {location.x - length / 4, location.y}, {location.x - length / 6, location.y - width / 16}, {location.x + 5 * length / 24, location.y - width / 16}, {location.x + length / 4, location.y - width / 16},  {location.x + length / 4, location.y + width / 16}, {location.x + 5 * length / 24, location.y + width / 16}, {location.x - length / 6, location.y + width / 16} };
  for (auto& i : dots)
  {
    point temp;
    temp.x = i.x * cos(angle) - i.y * sin(angle) - location.x / 2;
    temp.y = i.x * sin(angle) + i.y * cos(angle) + location.y;
    vertex.push_back(temp);
  }
}

void Button_Pencil::Draw(void)
{
  Background();
  vector<int> noseIndex = { 0, 1, 6 };
  vector<int> bodyIndex = { 1, 2, 5, 6 };
  vector<int> eraserIndex = { 2, 3, 4, 5 };
  glBegin(GL_POLYGON);
  glColor3d(nose.red, nose.green, nose.blue);
  for (auto& i : noseIndex)
    glVertex3d(vertex[i].x, vertex[i].y, 0);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3d(body.red, body.green, body.blue);
  for (auto& i : bodyIndex)
    glVertex3d(vertex[i].x, vertex[i].y, 0);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3d(eraser.red, eraser.green, eraser.blue);
  for (auto& i : eraserIndex)
    glVertex3d(vertex[i].x, vertex[i].y, 0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 0.0, 0.0);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glVertex3d(vertex[0].x, vertex[0].y, 0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 0.0, 0.0);
  glVertex3d(vertex[1].x, vertex[1].y, 0);
  glVertex3d(vertex[6].x, vertex[6].y, 0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 0.0, 0.0);
  glVertex3d(vertex[2].x, vertex[2].y, 0);
  glVertex3d(vertex[5].x, vertex[5].y, 0);
  glEnd();
}

Button_Eraser::Button_Eraser(const point& Location, const double& Length, const double& Width, const GlutRGB& Color) : Button(Location, Length, Width, Color, eraser), color(199, 21, 133)
{
  vertex = { {location.x - length / 4, location.y - width / 4}, {location.x + length / 4, location.y - width / 4}, {location.x + length / 4, location.y + width / 4}, {location.x - length / 4, location.y + width / 4} };
}

void Button_Eraser::Draw(void)
{
  Background();
  GLdouble shine = 127 / 255.0;
  glBegin(GL_POLYGON);
  glColor3d(color.red, color.green, color.blue);
  for (unsigned int i = 0; i < vertex.size(); i++)
  {
    switch (i)
    {
    case 1: glColor3d(color.red + shine, color.green + shine, color.blue + shine); break;
    default: glColor3d(color.red, color.green, color.blue); break;
    }
    glVertex3d(vertex[i].x, vertex[i].y, 0);
  }
  glEnd();
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 0.0, 0.0);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glVertex3d(vertex[0].x, vertex[0].y, 0);
  glEnd();
}

Button_Line::Button_Line(const point& Location, const double& Length, const double& Width, const GlutRGB& Color) : Button(Location, Length, Width, Color, line), color({ 0.0, 0.0, 0.0 })
{
  vertex = { {location.x - length / 4,location.y}, {location.x + length / 4, location.y} };
}

void Button_Line::Draw(void)
{
  Background();
  glBegin(GL_LINE_STRIP);
  glColor3d(color.red, color.green, color.blue);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glEnd();
}

Button_Rectangle::Button_Rectangle(const point& Location, const double& Length, const double& Width, const GlutRGB& Color) : Button(Location, Length, Width, Color, rectangle), color(0.0, 0.0, 0.0)
{
  vertex = { {location.x - length / 4, location.y - width / 4}, {location.x + length / 4, location.y - width / 4}, {location.x + length / 4, location.y + width / 4}, {location.x - length / 4, location.y + width / 4} };
}

void Button_Rectangle::Draw(void)
{
  Background();
  glBegin(GL_LINE_STRIP);
  glColor3d(color.red, color.green, color.blue);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glVertex3d(vertex[0].x, vertex[0].y, 0);
  glEnd();
}

Button_Circle::Button_Circle(const point& Location, const double& Length, const double& Width, const GlutRGB& Color) : Button(Location, Length, Width, Color, circle), radius(width / 4), number(360), color(0.0, 0.0, 0.0) {}

void Button_Circle::Draw(void)
{
  Background();
  glBegin(GL_LINE_STRIP);
  glColor3d(color.red, color.green, color.blue);
  for (int i = 0; i < number; i++)
    glVertex3d(location.x + radius * cos(2 * PI * i / number), location.y + radius * sin(2 * PI * i / number), 0);
  glEnd();
}

Button_New::Button_New(const point& Location, const double& Length, const double& Width, const GlutRGB& Color) : Button(Location, Length, Width, Color, none), content("New")
{
  content.SetLocation({ location.x - content.Length() / 2, location.y + content.Width() / 2 });
}

void Button_New::New(Canvas& _Canvas)
{
  if (Power() != on)
    return;
  _Canvas.SetDefault();
}

void Button_New::Draw(void)
{
  Background();
  content.Draw();
}

Button_Open::Button_Open(const point& Location, const double& Length, const double& Width, const GlutRGB& Color) : Button(Location, Length, Width, Color, none), content("Open")
{
  content.SetLocation({ location.x - content.Length() / 2, location.y + content.Width() / 2 });
}

void Button_Open::Open(const string& Name, const vector<vector<GlutRGB>>& Array)
{
  if (Power() != on)
    return;
  ifstream fin;
  string fileName = Name;
  if (Name.size() < 4 || Name[Name.size() - 1] != 'c' || Name[Name.size() - 2] != 'i' || Name[Name.size() - 3] != 'p' || Name[Name.size() - 4] != '.')
    fileName += ".pic";
  fin.open(fileName.data(), ios::in | ios::binary);
  if (!fin.is_open())
  {
    cout << '\a';
    return;
  }
  for (auto& i : Array)
    for (auto& j : i)
      fin.read((char*)&j, sizeof(j));
  fin.close();
}

void Button_Open::Draw(void)
{
  Background();
  content.Draw();
}

Button_Save::Button_Save(const point& Location, const double& Length, const double& Width, const GlutRGB& Color) : Button(Location, Length, Width, Color, none), content("Save")
{
  content.SetLocation({ location.x - content.Length() / 2, location.y + content.Width() / 2 });
}

void Button_Save::Save(const string& Name, const vector<vector<GlutRGB>>& Array)
{
  if (Power() != on)
    return;
  ofstream fout;
  string fileName = Name;
  if (Name.size() < 4 || Name[Name.size() - 1] != 'c' || Name[Name.size() - 2] != 'i' || Name[Name.size() - 3] != 'p' || Name[Name.size() - 4] != '.')
    fileName += ".pic";
  fout.open(fileName.data(), ios::out | ios::binary);
  if (!fout.is_open())
  {
    cout << '\a';
    return;
  }
  for (auto& i : Array)
    for (auto& j : i)
      fout.write((char*)&j, sizeof(j));
  fout.close();
}

void Button_Save::Draw(void)
{
  Background();
  content.Draw();
}