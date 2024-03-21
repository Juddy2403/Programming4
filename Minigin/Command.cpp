#include "Command.h"
#include "Time.h"
#include "GameActor.h"

using namespace GameEngine;

void GameEngine::Move::Execute()
{
	auto& time = Time::GetInstance();

	m_Actor->GetLocalTransform().Translate(time.GetElapsed() * m_Speed * m_Direction);
}

GameEngine::Move::Move(GameObject* actor, float speed):
	Command(actor),
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

GameEngine::Command::Command(GameObject* actor):
	m_Actor{actor}
{
}

void GameEngine::TakeDamage::Execute()
{
	auto actor = static_cast<GameActor*>(m_Actor);
	actor->Hit();
}
