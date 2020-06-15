#include "field.h"

Cursor::Cursor(const point& Location, const double& Width) : location(Location), length(2), width(Width), color({ 0, 0 ,0 })
{
  vertex = { { location.x - length / 2, location.y - width / 2 }, { location.x + length / 2, location.y - width / 2 },{ location.x + length / 2, location.y + width / 2 }, { location.x - length / 2, location.y + width / 2 } };
}

void Cursor::DataUpdate(const point& Location, const double& Width)
{
  location = Location;
  width = Width;
  vertex = { { location.x - length / 2, location.y - width / 2 }, { location.x + length / 2, location.y - width / 2 },{ location.x + length / 2, location.y + width / 2 }, { location.x - length / 2, location.y + width / 2 } };
}

void Cursor::Draw(void)
{
  glBegin(GL_POLYGON);
  glColor3d(color.red, color.green, color.blue);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glEnd();
}

Field::Field(const point& Location, const GlutRGB& Color, const int& Left, const int& Rigth) : location(Location), color(Color), status(output), content("Unnamed"), cursor({ 0, 0 }, 0), left(Left), rigth(Rigth)
{
  length = content.Length();
  width = content.Width();
  content.SetLocation({ location.x - length / 2, location.y + width / 2 });
  cursor.DataUpdate({ location.x + length / 2 + 4, location.y }, 2 * width);
  vertex = { {location.x - length / 2 - 17, location.y - width - 4}, {location.x + length / 2 + 17, location.y - width - 4}, {location.x + length / 2 + 17, location.y + width + 4}, {location.x - length / 2 - 17, location.y + width + 4} };
}

void Field::SetLocation(const point& Location)
{
  location = location;
  content.SetLocation({ location.x - length / 2, location.y + width / 2 });
  cursor.DataUpdate({ location.x + length / 2 + 4, location.y + width / 2 }, 2 * width);
  vertex = { {location.x - length / 2 - 17, location.y - width - 4}, {location.x + length / 2 + 17, location.y - width - 4}, {location.x + length / 2 + 17, location.y + width + 4}, {location.x - length / 2 - 17, location.y + width + 4} };
}

void Field::Background(void)
{
  glBegin(GL_POLYGON);
  glColor3d(color.red, color.green, color.blue);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glColor3d(0.0, 0.0, 0.0);
  for (auto& i : vertex)
    glVertex3d(i.x, i.y, 0);
  glVertex3d(vertex[0].x, vertex[0].y, 0);
  glEnd();
}

void Field::Update(void)
{
  double temp = content.Length();
  if (temp != 0)
    length = content.Length();
  location = location;
  content.SetLocation({ location.x - length / 2, location.y + width / 2 });
  cursor.DataUpdate({ location.x + length / 2 + 4, location.y }, 2 * width);
  vertex = { {location.x - length / 2 - 17, location.y - width - 4}, {location.x + length / 2 + 17, location.y - width - 4}, {location.x + length / 2 + 17, location.y + width + 4}, {location.x - length / 2 - 17, location.y + width + 4} };
}

void Field::Input(const unsigned char& Key)
{
  if (status != input)
    return;
  switch (Key)
  {
  case 27:
  case '\r': if (!content.Content().empty()) { status = output; } break;
  case 8: if (!content.Content().empty()) { content.Content().pop_back(); } break;
  default: if (length / 2 + location.x + 26 < rigth && location.x - length / 2 - 26 > left ) { content.Content().push_back(Key); } break;
  }
  content.Update();
  Update();
}

void Field::Draw(void)
{
  switch (status)
  {
  case input: Background(); cursor.Draw();
  case output: content.Draw(); break;
  }
}

bool Field::IsClick(const int& X, const int& Y)
{
  if (X <= location.x + length / 2 && X >= location.x - length / 2 && Y <= location.y + width / 2 && Y >= location.y - width / 2)
    return true;
  return false;
}