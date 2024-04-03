#include "IObserver.h"
#include "Subject.h"
#include "GameObject.h"
#include <iostream>
//#include "AchievementsManager.h"
#include "ActorComponent.h"

GameEngine::IObserver::IObserver(std::string name) : m_Name{ std::move(name) } {}

GameEngine::HealthObserver::HealthObserver(const std::string& name, GameObject* gameObject):
    IObserver(name),
    Component(gameObject)
{}
void GameEngine::HealthObserver::Notify(Subject* subject, GameEvent event)
{
    switch (event)
    {
    case GameEvent::event:
    case GameEngine::GameEvent::playerDied:
        if (auto* textComp = GetGameObjParent()->GetComponent<TextComponent>())
        {
            const auto gameObject = dynamic_cast<GameObject*>(subject);
            assert(gameObject);
            const int lives = gameObject->GetComponent<ActorComponent>()->GetRemainingLives();
            textComp->SetText("# lives: " + std::to_string(lives));
            textComp->Update();
        }
        else std::cerr << "No text component found! /health observer \n";
        break;
    default: break;
    }
}

GameEngine::ScoreObserver::ScoreObserver(const std::string& name, GameObject* gameObject):
    IObserver(name),
    Component(gameObject)
{}

void GameEngine::ScoreObserver::Notify(Subject* subject, GameEvent event)
{
    switch (event)
    {
    case GameEvent::event:
    case GameEngine::GameEvent::scoreIncreased:
        if (auto* textComp = GetGameObjParent()->GetComponent<TextComponent>())
        {
            const auto gameObject = dynamic_cast<GameObject*>(subject);
            assert(gameObject);
            const int score = gameObject->GetComponent<ActorComponent>()->GetScore();
            // if (score >= 500)
            // {
            //     AchievementsManager::GetInstance().SetAchievement("ACH_WIN_ONE_GAME");
            // }
            textComp->SetText("Score: " + std::to_string(score));
        }
        else std::cerr << "No text component found! /score observer \n";
        break;
    default: break;
    }
}
