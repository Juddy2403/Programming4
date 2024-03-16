#pragma once
#include "Singleton.h"
#include <memory>
#include "Command.h"

namespace GameEngine
{
	class InputManager final : public Singleton<InputManager>
	{
	private:
		std::unique_ptr<MoveUp> m_pMoveUpCommand{ std::make_unique<MoveUp>() };
		std::unique_ptr<MoveDown> m_pMoveDownCommand{ std::make_unique<MoveDown>() };
		std::unique_ptr<MoveRight> m_pMoveRightCommand{ std::make_unique<MoveRight>() };
		std::unique_ptr<MoveLeft> m_pMoveLeftCommand{ std::make_unique<MoveLeft>() };
		std::unique_ptr<Move> m_pMoveCommand{ std::make_unique<Move>() };

	public:
		bool ProcessInput();
		void ExecuteCommand(GameObject* actor);
	};

}
