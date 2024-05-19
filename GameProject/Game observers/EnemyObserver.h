#pragma once
#include "IObserver.h"

class EnemyObserver final : public GameEngine::IObserver
{
public:
    explicit EnemyObserver();
    virtual void Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
        , GameEngine::EventData* eventData) override;
private:
};

