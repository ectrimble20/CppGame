#include "Rect.h"

Rect::Rect(const Vector2& topLeft, const Vector2& bottomRight)
	: width(bottomRight.GetX() - topLeft.GetX()), height(bottomRight.GetY() - topLeft.GetY())
{
	x0 = topLeft.GetX();
	y0 = topLeft.GetY();
	x1 = bottomRight.GetX();
	y1 = bottomRight.GetY();
}


Rect::~Rect()
{
}

void Rect::UpdatePosition(Vector2 & newPosition)
{
	x0 = newPosition.GetX() - (width / 2.0f) ;
	y0 = newPosition.GetY() - (height / 2.0f);
	x1 = (width / 2.0f) + newPosition.GetX();
	y1 = (height / 2.0f) + newPosition.GetY();
}

//Not sure if this is correct, we'll need to do some tests and tweak this, I think I need 2-4 more position tests
bool Rect::CheckCollision(Rect other)
{
	return x1 > other.GetX0() && x0 < other.GetX1() && y1 > other.GetY0() && y0 < other.GetY1();
}

bool Rect::CheckCollision(Vector2 & position)
{
	return x0 <= position.GetX() && y0 <= position.GetY() && x1 >= position.GetX() && y1 >= position.GetY();
}

Vector2 Rect::GetCenter() const
{
	return Vector2((x0 + x1) / 2.0f, (y0 + y1) / 2.0f);
}