#include <SDL.h>
#include "InputManager.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <backends/imgui_impl_sdl2.h>

//GameEngine::InputManager::InputManager(): Singleton<InputManager>(),
//m_pController{ std::make_unique<Controller>(0) }
//{
//}

void GameEngine::InputManager::BindKeyboardCommand(GameObject* actor, float speed)
{
	m_pKeyboardCommand = std::make_unique<Move>(actor,speed);
}



void GameEngine::InputManager::BindControllerCommand(GameObject* actor, float speed)
{
	m_pControllerCommand = std::make_unique<Move>(actor,speed);
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
				if (e.key.keysym.scancode == SDL_SCANCODE_W) m_pKeyboardCommand->KeyPressed({ 0,-1 });
				if (e.key.keysym.scancode == SDL_SCANCODE_A) m_pKeyboardCommand->KeyPressed({ -1,0 });
				if (e.key.keysym.scancode == SDL_SCANCODE_S) m_pKeyboardCommand->KeyPressed({ 0,1 } );
				if (e.key.keysym.scancode == SDL_SCANCODE_D) m_pKeyboardCommand->KeyPressed({ 1,0 } );
			}
			break;
		case SDL_KEYUP:
			if (e.key.keysym.scancode == SDL_SCANCODE_W) m_pKeyboardCommand->KeyReleased({ 0,-1 });
			if (e.key.keysym.scancode == SDL_SCANCODE_A) m_pKeyboardCommand->KeyReleased({ -1,0 });
			if (e.key.keysym.scancode == SDL_SCANCODE_S) m_pKeyboardCommand->KeyReleased({ 0,1 } );
			if (e.key.keysym.scancode == SDL_SCANCODE_D) m_pKeyboardCommand->KeyReleased({ 1,0 } );
			break;
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	ProcessControllerInput();

	return true;
}

void GameEngine::InputManager::ProcessControllerInput()
{
	m_pController->ProcessControllerInput();

	if (m_pController->IsDpadUpKeyDown())    m_pControllerCommand->KeyPressed({ 0,-1 });
	if (m_pController->IsDpadLeftKeyDown())  m_pControllerCommand->KeyPressed({ -1,0 });
	if (m_pController->IsDpadDownKeyDown())  m_pControllerCommand->KeyPressed({ 0,1 } );
	if (m_pController->IsDpadRightKeyDown()) m_pControllerCommand->KeyPressed({ 1,0 } );

	if (m_pController->IsDpadUpKeyUp())      m_pControllerCommand->KeyReleased({ 0,-1 });
	if (m_pController->IsDpadLeftKeyUp())    m_pControllerCommand->KeyReleased({ -1,0 });
	if (m_pController->IsDpadDownKeyUp())    m_pControllerCommand->KeyReleased({ 0,1 } );
	if (m_pController->IsDpadRightKeyUp())   m_pControllerCommand->KeyReleased({ 1,0 } );
}

void GameEngine::InputManager::ExecuteCommand()
{
	m_pKeyboardCommand->Execute();
	m_pControllerCommand->Execute();
}
