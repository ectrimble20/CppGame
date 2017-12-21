#pragma once
#include "Rect.h"
#include "Surface.h"
#include "Vector2.h"

class Button
{
public:
	Button(const Rect& rect, const Surface& surface);
	Button(Rect& rect, Surface& surface);
	~Button();
	Surface GetSurface() const { return surface; };
	bool Clicked(const Vector2& clickSpot) const;
	void Hide() {
		display = false;
	};
	void Show() {
		display = true;
	};
	void Disable() {
		active = false;
	};
	void Enable() {
		active = true;
	};
private:
	bool active = true;
	bool display = true;
	const Rect rect;
	const Surface surface;
};

