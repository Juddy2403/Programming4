#pragma once
#include "Singleton.h"
#include "Command.h"
#include "Controller.h"

namespace GameEngine
{
	class Controller;
	class InputManager final : public Singleton<InputManager>
	{
	private:
		//Commands
		std::unique_ptr<Move> m_pKeyboardCommand{nullptr};
		std::unique_ptr<Move> m_pControllerCommand{nullptr};

		std::unique_ptr<Controller> m_pController;
	public:
		InputManager();
		void BindKeyboardCommand(GameObject* actor);
		void BindControllerCommand(GameObject* actor);

		bool ProcessInput();
		void ProcessControllerInput();
		void ExecuteCommand();
	};

}
