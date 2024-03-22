#include "InputManager.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <backends/imgui_impl_sdl2.h>
#include "GameActor.h"

bool GameEngine::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		InputKey sdlScanCode = static_cast<InputKey>(e.key.keysym.scancode);

		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			if (m_pKeyboardCommands.find(sdlScanCode) != m_pKeyboardCommands.end())
			{
				auto* command = m_pKeyboardCommands[sdlScanCode].get();
				command->KeyPressed();
			}
			break;
		case SDL_KEYUP:
			if (m_pKeyboardCommands.find(sdlScanCode) != m_pKeyboardCommands.end())
			{
				auto* command = m_pKeyboardCommands[sdlScanCode].get();
				command->KeyReleased();
			}
			break;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	ProcessControllerInput();
	ExecuteCommands();

	return true;
}


void GameEngine::InputManager::ProcessControllerInput()
{

	for (size_t i = 0; i < maxControllerCount; i++)
	{
		if (m_pControllers[i] != nullptr) {
			m_pControllers[i]->ProcessControllerInput();
			//TODO: perhaps create an event queue with the inputs received
			CheckDPADMovement(i, InputKey::DPAD_UP);
			CheckDPADMovement(i, InputKey::DPAD_DOWN);
			CheckDPADMovement(i, InputKey::DPAD_LEFT);
			CheckDPADMovement(i, InputKey::DPAD_RIGHT);
		}
	}
	
}

void GameEngine::InputManager::CheckDPADMovement(const size_t& i,const GameEngine::InputManager::InputKey& inputKey)
{
	if (m_pControllerCommands[i][inputKey] != nullptr)
	{
		auto* command = m_pControllerCommands[i][inputKey].get();
		if(command)
		{
			if (m_pControllers[i]->IsKeyDown(static_cast<int>(inputKey))) command->KeyPressed();
			if (m_pControllers[i]->IsKeyUp(static_cast<int>(inputKey))) command->KeyReleased();
		}
	}
}

void GameEngine::InputManager::ExecuteCommands()
{
	for (auto& command : m_pKeyboardCommands)
	{
		command.second->Execute();
	}
	for (size_t i = 0; i < maxControllerCount; i++)
	{
		if (m_pControllers[i] != nullptr) {
			for (auto& command : m_pControllerCommands[i])
				command.second->Execute();
		}
	}
}

