#pragma once
class Vector2
{
public:
	Vector2() = default;
	Vector2(float x_in, float y_in);
	Vector2 operator+(const Vector2& rhs) const;
	Vector2& operator+=(const Vector2& rhs);
	Vector2 operator*(float rhs) const;
	Vector2& operator*=(float rhs);
	Vector2 operator-(const Vector2& rhs) const;
	Vector2& operator-=(const Vector2& rhs);
	float GetLength() const;
	float GetLengthSq() const;
	Vector2& Normalize();
	Vector2 GetNormalized() const;
	//Converted these to accessors
	float GetX() const { return x; };
	float GetY() const { return y; };
	//These are now redundant, Rect's operate on floats now
	//adding these for use with Rect which operates in exact numbers.
	//int GetXInt() const { return (int)x; };
	//int GetYInt() const { return (int)y; };
private:
	float x;
	float y;
};