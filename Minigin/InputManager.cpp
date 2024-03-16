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
		case SDL_KEYDOWN:
			if (e.key.keysym.scancode == SDL_SCANCODE_W) m_pMoveUpCommand->KeyPressed();
			if (e.key.keysym.scancode == SDL_SCANCODE_A) m_pMoveLeftCommand->KeyPressed();
			if (e.key.keysym.scancode == SDL_SCANCODE_S) m_pMoveDownCommand->KeyPressed();
			if (e.key.keysym.scancode == SDL_SCANCODE_D) m_pMoveRightCommand->KeyPressed();
			break;
		case SDL_KEYUP:
			if (e.key.keysym.scancode == SDL_SCANCODE_W) m_pMoveUpCommand->KeyReleased();
			if (e.key.keysym.scancode == SDL_SCANCODE_A) m_pMoveLeftCommand->KeyReleased();
			if (e.key.keysym.scancode == SDL_SCANCODE_S) m_pMoveDownCommand->KeyReleased();
			if (e.key.keysym.scancode == SDL_SCANCODE_D) m_pMoveRightCommand->KeyReleased();
			break;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void GameEngine::InputManager::ExecuteCommand(GameObject* actor)
{
	m_pMoveCommand->Execute(actor);
}
