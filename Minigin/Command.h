#pragma once
#include "Component.h"

namespace GameEngine
{
	class GameObject;
	class Command
	{
	private:
	public:
		Command() = default;
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
		virtual ~Command() = default;

		virtual void Execute(GameObject* actor) = 0;
	};

	class MoveRightCommand : public Command {
	private:
	public:
		virtual void Execute(GameObject* actor) override;
	};
}


