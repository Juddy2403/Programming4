#include <SDL.h>
#include "InputManager.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <backends/imgui_impl_sdl2.h>
#include "GameActor.h"

//GameEngine::InputManager::InputManager(): Singleton<InputManager>(),
//m_pController{ std::make_unique<Controller>(0) }
//{
//}

void GameEngine::InputManager::BindCommand(InputKey inputKey, GameActor* actor, int controllerIdx)
{
	if (controllerIdx >= 0 ) {
		//adding a controller ptr if its needed
		if(m_pControllers[controllerIdx] == nullptr)
		m_pControllers[controllerIdx] = std::make_unique<Controller>(controllerIdx);

		switch (inputKey)
		{
		case InputKey::DPAD:
			m_pControllerCommands[controllerIdx][inputKey] = std::make_unique<Move>(actor);
			break;
		}
	}
	else
	{
		switch (inputKey)
		{
		case InputKey::WASD:
			m_pKeyboardCommands[inputKey] = std::make_unique<Move>(actor);
			break;
		}
	}
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

			if (m_pKeyboardCommands[InputKey::WASD] != nullptr)
			{
				auto* command = dynamic_cast<Move*>( m_pKeyboardCommands[InputKey::WASD].get() );
				if (e.key.keysym.scancode == SDL_SCANCODE_W) command->KeyPressed({ 0,-1 });
				if (e.key.keysym.scancode == SDL_SCANCODE_A) command->KeyPressed({ -1,0 });
				if (e.key.keysym.scancode == SDL_SCANCODE_S) command->KeyPressed({ 0,1 } );
				if (e.key.keysym.scancode == SDL_SCANCODE_D) command->KeyPressed({ 1,0 } );
			}
			break;
		case SDL_KEYUP:
			if (m_pKeyboardCommands[InputKey::WASD] != nullptr)
			{
				auto* command = dynamic_cast<Move*>(m_pKeyboardCommands[InputKey::WASD].get());
				if (e.key.keysym.scancode == SDL_SCANCODE_W) command->KeyReleased({ 0,-1 });
				if (e.key.keysym.scancode == SDL_SCANCODE_A) command->KeyReleased({ -1,0 });
				if (e.key.keysym.scancode == SDL_SCANCODE_S) command->KeyReleased({ 0,1 });
				if (e.key.keysym.scancode == SDL_SCANCODE_D) command->KeyReleased({ 1,0 });
			}

			break;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	ProcessControllerInput();

	return true;
}

void GameEngine::InputManager::ProcessControllerInput()
{

	for (size_t i = 0; i < maxControllerCount; i++)
	{
		if (m_pControllers[i] != nullptr) {
			m_pControllers[i]->ProcessControllerInput();
			if (m_pControllerCommands[i][InputKey::DPAD] != nullptr)
			{
				auto* command = dynamic_cast<Move*>(m_pControllerCommands[i][InputKey::DPAD].get());

				if (m_pControllers[i]->IsDpadUpKeyDown())    command->KeyPressed({ 0,-1 });
				if (m_pControllers[i]->IsDpadLeftKeyDown())  command->KeyPressed({ -1,0 });
				if (m_pControllers[i]->IsDpadDownKeyDown())  command->KeyPressed({ 0,1 });
				if (m_pControllers[i]->IsDpadRightKeyDown()) command->KeyPressed({ 1,0 });
								 							 
				if (m_pControllers[i]->IsDpadUpKeyUp())      command->KeyReleased({ 0,-1 });
				if (m_pControllers[i]->IsDpadLeftKeyUp())    command->KeyReleased({ -1,0 });
				if (m_pControllers[i]->IsDpadDownKeyUp())    command->KeyReleased({ 0,1 });
				if (m_pControllers[i]->IsDpadRightKeyUp())   command->KeyReleased({ 1,0 });
			}
		}
	}
	
}

void GameEngine::InputManager::ExecuteCommand()
{
	for (auto it = m_pKeyboardCommands.begin(); it != m_pKeyboardCommands.end(); ++it)
		it->second->Execute();
	for (size_t i = 0; i < maxControllerCount; i++)
	{
		if (m_pControllers[i] != nullptr) {
			for (auto it = m_pControllerCommands[i].begin(); it != m_pControllerCommands[i].end(); ++it)
				it->second->Execute();
		}
	}
}
