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
		//InputManager();
		std::unique_ptr<Move> m_pKeyboardCommand{nullptr};
		std::unique_ptr<Move> m_pControllerCommand{nullptr};

		std::unique_ptr<Controller> m_pController{ std::make_unique<Controller>(0) };
	public:
		void BindKeyboardCommand(GameObject* actor, float speed);
		void BindControllerCommand(GameObject* actor, float speed);

		bool ProcessInput();
		void ProcessControllerInput();
		void ExecuteCommand();

		~InputManager() override = default;
	};

}
