#include "Rect.h"



Rect::Rect(float width, float height, Vector2 & centerPosition) : width(width), height(height), position(centerPosition)
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
bool Rect::CheckCollision(const Rect & other) const
{
	return x1 > other.x0 && x0 < other.x1 && y1 > other.y0 && y0 < other.y1;
}

//checks for a single position over-lap, very useful for detecting mouse clicks on an object
bool Rect::CheckCollision(const Vector2 & position) const
{
	return position.GetX() >= x0 && position.GetX() <= x1 && position.GetY() >= y0 && position.GetY() <= y1;
	//return x0 <= position.GetX() && y0 <= position.GetY() && x1 >= position.GetX() && y1 >= position.GetY();
}

void Rect::UpdateBounds()
{
	x0 = position.GetX() - (width / 2);
	y0 = position.GetY() - (height / 2);
	x1 = position.GetX() + (width / 2);
	y1 = position.GetY() + (height / 2);
	GameLogger::Log("Bounds updated to XY0: " + std::to_string(x0) + "," + std::to_string(y0) + " XY1: " + std::to_string(x1) + "," + std::to_string(y1));
}

