#include "IObserver.h"
#include "Subject.h"
#include "GameActor.h"
#include <iostream>
#include "AchievementsManager.h"

GameEngine::IObserver::IObserver(const std::string& name) : m_Name{ name } {}

void GameEngine::HealthObserver::Notify(Subject::GameEvent event, Subject* subject)
{
	switch (event)
	{
	case GameEngine::Subject::GameEvent::playerDied:
		Notify(subject);
		break;
	case GameEngine::Subject::GameEvent::scoreIncreased:
		break;
	default:
		break;
	}
}

void GameEngine::HealthObserver::Notify(Subject* subject)
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

void GameEngine::ScoreObserver::Notify(Subject::GameEvent event, Subject* subject)
{
	switch (event)
	{
	case GameEngine::Subject::GameEvent::playerDied:
		break;
	case GameEngine::Subject::GameEvent::scoreIncreased:
		Notify(subject);
		break;
	default:
		break;
	}

}

void GameEngine::ScoreObserver::Notify(Subject* subject)
{
	auto* textComp = GetComponent<TextComponent>();
	if (textComp)
	{
		auto gameActor = dynamic_cast<GameActor*>(subject);
		assert(gameActor);
		int score = gameActor->GetScore();
		if (score >= 500) {
			AchievementsManager::GetInstance().SetAchievement("ACH_WIN_ONE_GAME");
		}
		textComp->SetText("Score: " + std::to_string(score));
		textComp->Update();
	}
	else std::cout << "No text component found! /score observer \n";
}
