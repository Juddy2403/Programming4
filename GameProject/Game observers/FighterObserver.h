﻿#pragma once
#include "IObserver.h"

class FighterObserver final : public GameEngine::IObserver
{
public:
    FighterObserver() = default;
    virtual void Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
        , GameEngine::EventData* eventData) override;
private:
};
