#pragma once
#include <glm/glm.hpp>

namespace GameEngine
{
	class GameActor;

	class ICommand
	{
	protected:
		GameActor* m_Actor;
	public:
		enum class ExecuteOn
		{
			keyPressed,
			keyUp,
			keyDown
		};
		
		explicit ICommand(GameActor* actor);
		ICommand(const ICommand& other) = delete;
		ICommand(ICommand&& other) = delete;
		ICommand& operator=(const ICommand& other) = delete;
		ICommand& operator=(ICommand&& other) = delete;
		virtual ~ICommand() = default;

		[[nodiscard]] virtual ExecuteOn ExecuteOnKeyState() const = 0;
		virtual void Execute() = 0;
	};

	class Move final: public ICommand {
	public:
		Move(const Move& other) = delete;
		Move(Move&& other) noexcept = delete;
		Move& operator=(const Move& other) = delete;
		Move& operator=(Move&& other) noexcept = delete;
		Move(GameActor* actor,const glm::vec2& direction);
		~Move() override;
		void Execute() override;
		[[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;
	protected:
		glm::vec2 m_Direction{};

	};
	
	class TakeDamage final : public ICommand {
	private:
	public:
		explicit TakeDamage(GameActor* actor);

		void Execute() override;
		[[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;
	};

	class SmallScoreIncrease final : public ICommand {

	public:
		SmallScoreIncrease(GameActor* actor);

		void Execute() override;
		[[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;

	};

	class BigScoreIncrease final : public ICommand {

	public:
		BigScoreIncrease(GameActor* actor);

		void Execute() override ;
		[[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;
	};

}


