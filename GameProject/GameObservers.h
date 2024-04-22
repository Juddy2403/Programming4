#pragma once
#include "IObserver.h"
#include "Scene.h"

class BulletObserver final : public GameEngine::IObserver
{
public:
    explicit BulletObserver(std::string&& name, GameEngine::Scene* scene);
    virtual void Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
        , GameEngine::EventData* eventData) override;
private:
    GameEngine::Scene* m_Scene{nullptr};
};

class EnemyObserver final : public GameEngine::IObserver
{
public:
    explicit EnemyObserver(std::string&& name);
    virtual void Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
        , GameEngine::EventData* eventData) override;
private:
};
