#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace GameEngine
{
	enum class Direction {
		up,
		down,
		left,
		right
	};
	class GameObject;
	class Command
	{
	protected:
	public:
		Command() = default;
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
		virtual ~Command() = default;

		virtual void Execute() = 0;
	};

	class Move final : public Command {
	private:
		float m_Speed{ 200.f };
		glm::vec2 m_Velocity{};
		GameObject* m_Actor;
	public:
		Move(GameObject* actor);

		virtual void Execute() override;
		virtual void KeyPressed(const Direction& dir);
		virtual void KeyReleased(const Direction& dir);
	};


}


