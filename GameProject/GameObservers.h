#pragma once
#include "IObserver.h"
#include "Scene.h"

class FighterObserver final : public GameEngine::IObserver
{
public:
    FighterObserver() = default;
    virtual void Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
        , GameEngine::EventData* eventData) override;
private:
};

class BulletObserver final : public GameEngine::IObserver
{
public:
    explicit BulletObserver( GameEngine::Scene* scene);
    virtual void Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
        , GameEngine::EventData* eventData) override;
private:
    GameEngine::Scene* m_Scene{nullptr};
};

class EnemyObserver final : public GameEngine::IObserver
{
public:
    explicit EnemyObserver();
    virtual void Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
        , GameEngine::EventData* eventData) override;
private:
};
