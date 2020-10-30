#include "InputManager.h"

int InputManager::mouseX = 0;
int InputManager::mouseY = 0;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

bool InputManager::IfKeyDown(SDL_Scancode key)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[key])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::IfMouseButtonDown(int button)
{
	if (button == 0)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			return true;
		}
	}
	else if (button == 1)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			return true;
		}
	}
	else if (button == 2)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
		{
			return true;
		}
	}

	return false;
}

void InputManager::GetMousePosition()
{
	SDL_GetMouseState(&mouseX, &mouseY);
}