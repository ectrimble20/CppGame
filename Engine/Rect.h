#pragma once
#include "Vector2.h"

class Rect
{
public:
	Rect() = delete;
	Rect(const Vector2& topLeft, const Vector2& bottomRight);
	~Rect();
	float GetX0() const { return x0; };
	float GetY0() const { return y0; };
	float GetX1() const { return x1; };
	float GetY1() const { return y1; };
	float GetWidth() const { return width; };
	float GetHeight() const { return height; };
	void UpdatePosition(Vector2& newPosition);
	bool CheckCollision(Rect other);
	bool CheckCollision(Vector2& position);
	Vector2 GetCenter() const;
private:
	float x0;
	float y0;
	float x1;
	float y1;
	const float width;
	const float height;
};

