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
		virtual void KeyPressed() {};
		virtual void KeyReleased() {};
	};

#pragma region Move Commands
	class Move : public Command {
	protected:
		bool m_IsActive{ false };
	public:
		Move(GameActor* actor);
		~Move() override;
		virtual void Execute() = 0;
		virtual void MoveActor(glm::vec2 direction);
		virtual void KeyPressed() override;
		virtual void KeyReleased() override;
	};

	class MoveUp final : public Move {
	private:
	public:
		MoveUp(GameActor* actor);
		~MoveUp() override;
		virtual void Execute() override;
	};

	class MoveDown final : public Move {
	private:
	public:
		MoveDown(GameActor* actor);
		~MoveDown() override;
		virtual void Execute() override;
	};

	class MoveRight final : public Move {
	private:
	public:
		MoveRight(GameActor* actor);
		~MoveRight() override;
		virtual void Execute() override;
	};

	class MoveLeft final : public Move {
	private:
	public:
		MoveLeft(GameActor* actor);
		~MoveLeft() override;
		virtual void Execute() override;
	};
#pragma endregion

	class TakeDamage final : public Command {
	private:
	public:
		TakeDamage(GameActor* actor);

		virtual void Execute() {};
		virtual void KeyPressed() override;
	};

	class SmallScoreIncrease final : public Command {

	public:
		SmallScoreIncrease(GameActor* actor);

		virtual void Execute() {};
		virtual void KeyPressed() override;
	};

	class BigScoreIncrease final : public Command {

	public:
		BigScoreIncrease(GameActor* actor);

		virtual void Execute() {};
		virtual void KeyPressed() override;
	};

}


