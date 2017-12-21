#pragma once
#include "GameLogger.h"
#include "Vector2.h"

class Rect
{
public:
	Rect() = delete;
	Rect(float width, float height, Vector2& centerPosition);
	~Rect();
	float GetWidth() const { return width; };
	float GetHeight() const { return height; };
	Vector2 GetPosition() const { return position; };
	void SetPosition(Vector2& p);
	bool CheckCollision(const Rect& other) const;
	bool CheckCollision(const Vector2& position) const;
private:
	void UpdateBounds();
	const float width;
	const float height;
	Vector2 position;
	float x0;
	float x1;
	float y0;
	float y1;
};

