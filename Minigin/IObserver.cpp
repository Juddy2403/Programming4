#include "IObserver.h"
#include "Subject.h"
#include "GameObject.h"
#include <iostream>
#include "AchievementsManager.h"
#include "ActorComponent.h"

GameEngine::IObserver::IObserver(std::string name) : m_Name{ std::move(name) } {}

void GameEngine::HealthObserver::Notify(GameEvent event, Subject* subject)
{
	switch (event)
	{
	case GameEngine::GameEvent::playerDied:
		Notify(subject);
		break;
	// case GameEngine::GameEvent::scoreIncreased:
	// 	break;
	default:
		break;
	}
}

void GameEngine::HealthObserver::Notify(Subject* subject)
{
	if (auto* textComp = GetComponent<TextComponent>())
	{
		const auto gameObject = dynamic_cast<GameObject*>(subject);
		assert(gameObject);
		const int lives = gameObject->GetComponent<ActorComponent>()->GetRemainingLives();
		textComp->SetText("# lives: " + std::to_string(lives));
		textComp->Update();
	}
	else std::cout << "No text component found! /health observer \n";
}

void GameEngine::ScoreObserver::Notify(GameEvent event, Subject* subject)
{
	switch (event)
	{
	case GameEngine::GameEvent::playerDied:
		break;
	case GameEngine::GameEvent::scoreIncreased:
		Notify(subject);
		break;
	default:
		break;
	}

}

void GameEngine::ScoreObserver::Notify(Subject* subject)
{
	if (auto* textComp = GetComponent<TextComponent>())
	{
		const auto gameObject = dynamic_cast<GameObject*>(subject);
		assert(gameObject);
		const int score = gameObject->GetComponent<ActorComponent>()->GetScore();
		if (score >= 500) {
			AchievementsManager::GetInstance().SetAchievement("ACH_WIN_ONE_GAME");
		}
		textComp->SetText("Score: " + std::to_string(score));
		textComp->Update();
	}
	else std::cout << "No text component found! /score observer \n";
}
