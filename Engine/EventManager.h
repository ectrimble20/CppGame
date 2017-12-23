#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Vector2.h"

class EventManager
{
public:
	EventManager(Mouse& mouseRef, Keyboard& keyboardRef);
	~EventManager();
	bool CheckForKeyPress(const unsigned char key);
	Vector2 GetMousePosition();
private:
	Mouse * pMouse = nullptr;
	Keyboard * pKeyboard = nullptr;
};

