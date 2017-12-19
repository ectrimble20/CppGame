#include "Rect.h"



Rect::Rect(int width, int height, Vector2 & centerPosition) : width(width), height(height), position(centerPosition)
{
	UpdateBounds();
}

Rect::~Rect()
{
}

//Updates the position and recalculates the boundaries
void Rect::SetPosition(Vector2 & p)
{
	position = p;
	UpdateBounds();
}

//used to detect collision between two rects
bool Rect::CheckCollision(Rect other)
{
	return x1 > other.x0 && x0 < other.x1 && y1 > other.y0 && y0 < other.y1;
}

//checks for a single position over-lap, very useful for detecting mouse clicks on an object
bool Rect::CheckCollision(Vector2 & position)
{
	return x0 <= position.GetX() && y0 <= position.GetY() && x1 >= position.GetX() && y1 >= position.GetY();
}

void Rect::UpdateBounds()
{
	x0 = (width / 2) + position.GetX();
	y0 = (width / 2) + position.GetX();
	x1 = (width / 2) + position.GetX();
	y1 = (width / 2) + position.GetX();
}

