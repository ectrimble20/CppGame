#include "EventManager.h"


EventManager::EventManager(Mouse & mouseRef, Keyboard & keyboardRef)
{
	pMouse = &mouseRef;
	pKeyboard = &keyboardRef;
}

EventManager::~EventManager()
{
	pMouse = nullptr;
	pKeyboard = nullptr;
}

bool EventManager::CheckForKeyPress(const unsigned char key)
{
	return pKeyboard->KeyIsPressed(key);
}

//Get's mouse position and translates into a Vector2
Vector2 EventManager::GetMousePosition()
{
	std::pair<int, int> mPos = pMouse->GetPos();
	return Vector2((float)mPos.first, (float)mPos.second);
}
