#pragma once
#include <glm/glm.hpp>

namespace GameEngine
{
	class GameObject;

	class Command
	{
	protected:
		GameObject* m_Actor;
	public:
		Command(GameObject* actor);
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
		virtual ~Command() = default;

		virtual void Execute() = 0;
	};

	class Move final : public Command {
	private:
		float m_Speed{};
		glm::vec2 m_Direction{};
	public:
		Move(GameObject* actor, float speed);
		~Move() override;
		virtual void Execute() override;
		virtual void KeyPressed(const glm::vec2& dir);
		virtual void KeyReleased(const glm::vec2& dir);
	};

	class TakeDamage final : public Command {
	private:
	public:
		virtual void Execute() override;
	};

}


