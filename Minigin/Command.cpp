#include "Command.h"
#include "Time.h"

using namespace GameEngine;
glm::vec2 Move::m_Velocity = {};

void GameEngine::Move::Execute(GameObject* actor)
{
	auto& time = Time::GetInstance();
	MathHelper::Vector3 currentPos = actor->GetLocalTransform().GetPosition();

	glm::vec2 newPos = glm::vec2{ currentPos.x + time.GetElapsed() * m_Velocity.x,
	currentPos.y + time.GetElapsed() * m_Velocity.y };

	actor->SetPosition(newPos.x, newPos.y);
}

void GameEngine::MoveUp::KeyPressed()
{
	m_Velocity.y = -m_Speed;
}

void GameEngine::MoveUp::KeyReleased()
{
	m_Velocity.y = 0;
}

void GameEngine::MoveDown::KeyPressed()
{
	m_Velocity.y = m_Speed;
}

void GameEngine::MoveDown::KeyReleased()
{
	m_Velocity.y = 0;
}

void GameEngine::MoveRight::KeyPressed()
{
	m_Velocity.x = m_Speed;
}

void GameEngine::MoveRight::KeyReleased()
{
	m_Velocity.x = 0;
}

void GameEngine::MoveLeft::KeyPressed()
{
	m_Velocity.x = -m_Speed;
}

void GameEngine::MoveLeft::KeyReleased()
{
	m_Velocity.x = 0;
}

