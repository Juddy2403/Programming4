#include <SDL.h>
#include "InputManager.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <backends/imgui_impl_sdl2.h>

bool GameEngine::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYUP:
			if (e.key.keysym.scancode == SDL_SCANCODE_W)
			break;
		default:
			break;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}
