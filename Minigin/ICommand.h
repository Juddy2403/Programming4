#pragma once
#include <glm/glm.hpp>

namespace GameEngine
{
	class GameObject;

	class ICommand
	{
	protected:
		GameObject* m_Actor;
	public:
		enum class ExecuteOn
		{
			keyPressed,
			keyUp,
			keyDown
		};
		
		explicit ICommand(GameObject* actor);
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
		
		explicit Move(GameObject* actor,const glm::vec2& direction, const float speed);
		~Move() override;
		void Execute() override;
		[[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;
	protected:
		float m_Speed;
		glm::vec2 m_Direction{};

	};
	
	class TakeDamage final : public ICommand {
	private:
	public:
		explicit TakeDamage(GameObject* actor);

		void Execute() override;
		[[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;
	};

	class SmallScoreIncrease final : public ICommand {

	public:
		SmallScoreIncrease(GameObject* actor);

		void Execute() override;
		[[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;

	};

	class BigScoreIncrease final : public ICommand {

	public:
		BigScoreIncrease(GameObject* actor);

		void Execute() override ;
		[[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;
	};

}


