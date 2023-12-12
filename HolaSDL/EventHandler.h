#pragma once
#include <SDL.h>
class EventHandler
{
protected:
	virtual void HandleEvent(const SDL_Event& event) = 0;
};

