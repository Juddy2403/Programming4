#include "Command.h"
#include "Time.h"
#include "GameObject.h"

using namespace GameEngine;

void GameEngine::Move::Execute()
{
	auto& time = Time::GetInstance();
	//glm::vec2 currentPos = m_Actor->GetLocalTransform().GetPosition();

	//glm::vec2 newPos = glm::vec2{ currentPos + time.GetElapsed() * m_Speed * m_Direction};

	//m_Actor->SetPosition(newPos.x, newPos.y);

	m_Actor->GetLocalTransform().Translate(time.GetElapsed() * m_Speed * m_Direction);
}

GameEngine::Move::Move(GameObject* actor, float speed):
	m_Actor{actor},
	m_Speed{speed}
{
}

GameEngine::Move::~Move()
{

}

void GameEngine::Move::KeyPressed(const glm::vec2& dir)
{
	if (dir.x != 0) m_Direction.x = dir.x;
	if (dir.y != 0) m_Direction.y = dir.y;
}

void GameEngine::Move::KeyReleased(const glm::vec2& dir)
{
	if (dir.x == m_Direction.x) m_Direction.x = 0;
	if (dir.y == m_Direction.y) m_Direction.y = 0;
}
