#include <SDL.h>
#include "InputManager.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <backends/imgui_impl_sdl2.h>

void GameEngine::InputManager::BindKeyboardCommand(GameObject* actor)
{
	m_pKeyboardCommand = std::make_unique<Move>(actor);
}

void GameEngine::InputManager::BindControllerCommand(GameObject* actor)
{
	m_pControllerCommand = std::make_unique<Move>(actor);
}

bool GameEngine::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			if (m_pKeyboardCommand != nullptr)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_W) m_pKeyboardCommand->KeyPressed(Direction::up);
				if (e.key.keysym.scancode == SDL_SCANCODE_A) m_pKeyboardCommand->KeyPressed(Direction::left);
				if (e.key.keysym.scancode == SDL_SCANCODE_S) m_pKeyboardCommand->KeyPressed(Direction::down);
				if (e.key.keysym.scancode == SDL_SCANCODE_D) m_pKeyboardCommand->KeyPressed(Direction::right);
			}
			break;
		case SDL_KEYUP:
			if (e.key.keysym.scancode == SDL_SCANCODE_W)  m_pKeyboardCommand->KeyReleased(Direction::up);
			if (e.key.keysym.scancode == SDL_SCANCODE_A)  m_pKeyboardCommand->KeyReleased(Direction::left);
			if (e.key.keysym.scancode == SDL_SCANCODE_S)  m_pKeyboardCommand->KeyReleased(Direction::down);
			if (e.key.keysym.scancode == SDL_SCANCODE_D)  m_pKeyboardCommand->KeyReleased(Direction::right);
			break;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	m_pController->ProcessControllerInput();

	if (m_pController->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_UP))    m_pControllerCommand->KeyPressed(Direction::up);
	if (m_pController->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_LEFT))  m_pControllerCommand->KeyPressed(Direction::left);
	if (m_pController->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_DOWN))  m_pControllerCommand->KeyPressed(Direction::down);
	if (m_pController->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_RIGHT)) m_pControllerCommand->KeyPressed(Direction::right);

	if (m_pController->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_UP))    m_pControllerCommand->KeyReleased(Direction::up);
	if (m_pController->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_LEFT))  m_pControllerCommand->KeyReleased(Direction::left);
	if (m_pController->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_DOWN))  m_pControllerCommand->KeyReleased(Direction::down);
	if (m_pController->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_RIGHT)) m_pControllerCommand->KeyReleased(Direction::right);


	return true;
}

void GameEngine::InputManager::ExecuteCommand()
{
	m_pKeyboardCommand->Execute();
	m_pControllerCommand->Execute();
}
