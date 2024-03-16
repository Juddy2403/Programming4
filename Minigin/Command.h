#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace GameEngine
{

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

		virtual void Execute(GameObject* actor) = 0;
	};

	class Move : public Command {
	protected:
		float m_Speed{ 200.f };
		static glm::vec2 m_Velocity;
	public:
		virtual void KeyPressed() {};
		virtual void KeyReleased() {};
		virtual void Execute(GameObject* actor) override;
	};

	class MoveUp final: public Move {
	private:
	public:
		virtual void KeyPressed() override;
		virtual void KeyReleased() override;
	};
	class MoveDown final : public Move {
	private:
	public:
		virtual void KeyPressed() override;
		virtual void KeyReleased() override;
	};
	class MoveLeft final : public Move {
	private:
	public:
		virtual void KeyPressed() override;
		virtual void KeyReleased() override;
	};
	class MoveRight final : public Move {
	private:
	public:
		virtual void KeyPressed() override;
		virtual void KeyReleased() override;
	};
}


