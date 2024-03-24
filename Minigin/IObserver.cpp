#include "IObserver.h"
#include "ISubject.h"
#include "GameActor.h"
#include <iostream>

GameEngine::IObserver::IObserver(const std::string& name) : m_Name{ name } {}

void GameEngine::HealthObserver::Notify(ISubject::GameEvent event, ISubject* subject)
{
	switch (event)
	{
	case GameEngine::ISubject::GameEvent::playerDied:
		Notify(subject);
		break;
	case GameEngine::ISubject::GameEvent::scoreIncreased:
		break;
	default:
		break;
	}
}

void GameEngine::HealthObserver::Notify(ISubject* subject)
{
	auto* textComp = GetComponent<TextComponent>();
	if (textComp)
	{
		auto gameActor = dynamic_cast<GameActor*>(subject);
		assert(gameActor);
		int lives = gameActor->GetRemainingLives();
		textComp->SetText("# lives: " + std::to_string(lives));
		textComp->Update();
	}
	else std::cout << "No text component found! /health observer \n";
}

void GameEngine::ScoreObserver::Notify(ISubject::GameEvent event, ISubject* subject)
{
	switch (event)
	{
	case GameEngine::ISubject::GameEvent::playerDied:
		break;
	case GameEngine::ISubject::GameEvent::scoreIncreased:
		Notify(subject);
		break;
	default:
		break;
	}

}

void GameEngine::ScoreObserver::Notify(ISubject* subject)
{
	auto* textComp = GetComponent<TextComponent>();
	if (textComp)
	{
		auto gameActor = dynamic_cast<GameActor*>(subject);
		assert(gameActor);
		int score = gameActor->GetScore();
		textComp->SetText("Score: " + std::to_string(score));
		textComp->Update();
	}
	else std::cout << "No text component found! /score observer \n";
}
