#include "GameActor.h"

GameEngine::GameActor::GameActor(std::string name): GameObject(name)
{
}

GameEngine::GameActor::GameActor(std::string name,int lives, float speed):
	GameObject(name),
	m_Lives{lives},
	m_Speed{speed}
{
}

void GameEngine::GameActor::Hit()
{
	--m_Lives;
	Notify(GameEvent::playerDied,static_cast<int>(ObserverIdentifier::health));
}

void GameEngine::GameActor::IncreaseScore(int value)
{
	m_Score += value;
	Notify(GameEvent::scoreIncreased,static_cast<int>(ObserverIdentifier::score));
}
