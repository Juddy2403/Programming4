#pragma once
#include "Singleton.h"
#include <memory>
#include "Command.h"
#include "Controller.h"

namespace GameEngine
{
	class InputManager final : public Singleton<InputManager>
	{
	private:
		//Commands
		std::unique_ptr<Move> m_pKeyboardCommand{nullptr};
		std::unique_ptr<Move> m_pControllerCommand{nullptr};

		std::unique_ptr<Controller> m_pController{ std::make_unique<Controller>(0) };
	public:
		void BindKeyboardCommand(GameObject* actor);
		void BindControllerCommand(GameObject* actor);

		bool ProcessInput();
		void ExecuteCommand();
	};

}
