#pragma once
#include "IObserver.h"
#include "Scene.h"

class EnemyBulletObserver final : public GameEngine::IObserver
{
public:
    explicit EnemyBulletObserver( GameEngine::Scene* scene);
    virtual void Notify(GameEngine::Subject* subject, int event
        , GameEngine::EventData* eventData) override;
private:
    GameEngine::Scene* m_Scene{nullptr};
};