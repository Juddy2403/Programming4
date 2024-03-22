#pragma once
#include <glm/glm.hpp>

namespace GameEngine
{
	class GameActor;

	class Command
	{
	protected:
		GameActor* m_Actor;
	public:
		Command(GameActor* actor);
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
		virtual ~Command() = default;

		virtual void Execute() = 0;
	};

	class Move final : public Command {
	private:
		glm::vec2 m_Direction{};
	public:
		Move(GameActor* actor);
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


