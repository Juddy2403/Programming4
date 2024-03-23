#include "Command.h"
#include "Time.h"
#include "GameActor.h"

using namespace GameEngine;

GameEngine::Command::Command(GameActor* actor) : m_Actor{ actor } {}

#pragma region Move Commands
void GameEngine::Move::MoveActor(glm::vec2 direction)
{
	auto& time = Time::GetInstance();

	m_Actor->GetLocalTransform().Translate(time.GetElapsed() * m_Actor->GetSpeed() * direction);
}

GameEngine::Move::Move(GameActor* actor): Command(actor){}

GameEngine::Move::~Move(){}

void GameEngine::Move::KeyPressed()
{
	m_IsActive = true;
}

void GameEngine::Move::KeyReleased()
{
	m_IsActive = false;
}

GameEngine::MoveUp::MoveUp(GameActor* actor): Move(actor){}

GameEngine::MoveUp::~MoveUp() {}

void GameEngine::MoveUp::Execute()
{
	if (m_IsActive) MoveActor({0,-1});
}

GameEngine::MoveDown::MoveDown(GameActor* actor) : Move(actor) {}

GameEngine::MoveDown::~MoveDown() {}

void GameEngine::MoveDown::Execute()
{
	if (m_IsActive) MoveActor({ 0,1 });
}

GameEngine::MoveRight::MoveRight(GameActor* actor) : Move(actor) {}

GameEngine::MoveRight::~MoveRight() {}

void GameEngine::MoveRight::Execute()
{
	if (m_IsActive) MoveActor({ 1,0 });
}

GameEngine::MoveLeft::MoveLeft(GameActor* actor) : Move(actor) {}

GameEngine::MoveLeft::~MoveLeft() {}

void GameEngine::MoveLeft::Execute()
{
	if (m_IsActive) MoveActor({ -1,0 });
}
#pragma endregion

GameEngine::TakeDamage::TakeDamage(GameActor* actor): Command(actor) {}

void GameEngine::TakeDamage::KeyPressed()
{
	m_Actor->Hit();
}
