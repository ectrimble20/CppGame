#pragma once
#include "Vector2.h"

class Rect
{
public:
	Rect() = delete;
	Rect(int width, int height, Vector2& centerPosition);
	~Rect();
	float GetWidth() const { return width; };
	float GetHeight() const { return height; };
	Vector2 GetPosition() const { return position; };
	void SetPosition(Vector2& p);
	bool CheckCollision(Rect other);
	bool CheckCollision(Vector2& position);
private:
	void UpdateBounds();
	const float width;
	const float height;
	Vector2 position;
	int x0;
	int x1;
	int y0;
	int y1;
};

