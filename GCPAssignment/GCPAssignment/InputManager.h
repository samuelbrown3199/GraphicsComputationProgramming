#pragma once
#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <SDL.h>

class InputManager
{
public:

	static int mouseX, mouseY;

	InputManager();
	~InputManager();

	static bool IfKeyDown(SDL_Scancode key);
	static bool IfMouseButtonDown(int button);
	static void GetMousePosition();
};

#endif

