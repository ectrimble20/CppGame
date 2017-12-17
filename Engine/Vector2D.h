#pragma once
#include <cmath>
template<typename T>
class Vector2D
{
public:
	Vector2D<T>(T in_x, T in_y) : x(in_x), y(in_y) { };
	//Cast between different type Vector2's
	template<typename S> explicit Vector2D(const Vector2D<S>& source) : x((T)source.GetX()), y((T)source.GetY()) {};
	//Operator Overloads
	Vector2D operator+(const Vector2D& rhs) const { return Vector2D(x + rhs.GetX(), y + rhs.GetY()); };
	Vector2D operator-(const Vector2D& rhs) const { return Vector2D(x - rhs.GetX(), y - rhs.GetY()); };
	Vector2D operator*(const T val) const { return Vector2D(x * val, y * val); };
	Vector2D operator+=(const Vector2D& rhs) const { return *this = *this + rhs; };
	Vector2D operator-=(const Vector2D& rhs) const { return *this = *this - rhs; };
	Vector2D operator*=(const T val) const { return *this = *this * rhs; };
	//Adding these functions since they're part of the chili tutorial stuff
	T GetLength() const { return (T)std::sqrt(GetLengthSq())};
	T GetLengthSq() const { return (x * x) + (y * y); };
	Vector2D& Normalize() { return *this = GetNormalized(); };
	Vector2D GetNormalized() {
		const T length = GetLength();
		if (length != (T)0)
		{
			return *this * ((T)1 / length);
		}
		return *this;
	};

	//Accessors
	T GetX() const { return x; };
	T GetY() const { return y; };
private:
	T x;
	T y;
};

typedef Vector2D<int> Vector2I;
typedef Vector2D<float> Vector2f;

