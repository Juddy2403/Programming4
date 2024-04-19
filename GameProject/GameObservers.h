#pragma once
#include "IObserver.h"

class BulletObserver final : public GameEngine::IObserver
{
public:
    explicit BulletObserver(std::string&& name, GameEngine::Scene* scene);
    virtual void Notify(GameEngine::Subject* subject, GameEngine::GameEvent event) override;
private:
    GameEngine::Scene* m_Scene{nullptr};
};
