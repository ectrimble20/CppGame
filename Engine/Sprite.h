#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "Animation.h"
#include <vector>

//Movement animations
enum SpriteAnimationType
{
	IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT, WALK_UP, WALK_DOWN, WALK_LEFT, WALK_RIGHT
};

/*
Sprite - Version 1.0.0

The Sprite class is an extendable class designed to handle Image, Rect/Position in one place.

The option to attach a mouse and keyboard object for listening will allow the Sprite class
to handle interactions as well.  I'm not 100% on where this is going yet, but I have a good
idea of how I want it to work.

This idea arose from 1) other projects and the definition of sprites in general and 2) my
button class was a real pain to try to implement and use, unable to actually handle anything
on its own.
*/

class Sprite
{
public:
	Sprite();
	~Sprite();
	void Move();
protected:
	//Vector2 position;
	//Vector2 velocity;
	//Rect rect;
	std::vector<Animation> images;
};

