#include "Button.h"



Button::Button(const Rect& rect, const Surface& surface) : rect(rect), surface(surface)
{
}

//Just for testing
Button::Button(Rect& rect, Surface& surface) : rect(rect), surface(surface)
{
}


Button::~Button()
{
}

bool Button::Clicked(const Vector2 & clickSpot) const
{
	//if it's not active, you can't click it
	if (!active)
	{
		return false;
	}
	return rect.CheckCollision(clickSpot);
}
