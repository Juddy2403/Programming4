#include "Command.h"
#include "Time.h"

using namespace GameEngine;

void GameEngine::Move::Execute()
{
	auto& time = Time::GetInstance();
	MathHelper::Vector3 currentPos = m_Actor->GetLocalTransform().GetPosition();

	glm::vec2 newPos = glm::vec2{ currentPos.x + time.GetElapsed() * m_Velocity.x,
	currentPos.y + time.GetElapsed() * m_Velocity.y };

	m_Actor->SetPosition(newPos.x, newPos.y);
}

GameEngine::Move::Move(GameObject* actor, float speed):
	m_Actor{actor},
	m_Speed{speed}
{
}

void GameEngine::Move::KeyPressed(const Direction& dir)
{
	switch (dir)
	{
	case Direction::up:
		m_Velocity.y = -m_Speed;
		break;
	case Direction::down:
		m_Velocity.y = m_Speed;
		break;
	case Direction::right:
		m_Velocity.x = m_Speed;
		break;
	case Direction::left:
		m_Velocity.x = -m_Speed;
		break;
	}
}

void GameEngine::Move::KeyReleased(const Direction& dir)
{
	switch (dir)
	{
	case Direction::up:
		if (m_Velocity.y == -m_Speed) m_Velocity.y = 0;
		break;
	case Direction::down:
		if (m_Velocity.y == m_Speed) m_Velocity.y = 0;
		break;
	case Direction::right:
		if (m_Velocity.x == m_Speed) m_Velocity.x = 0;
		break;
	case Direction::left:
		if (m_Velocity.x == -m_Speed) m_Velocity.x = 0;
		break;
	}
}
