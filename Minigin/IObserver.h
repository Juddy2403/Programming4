#pragma once
#include "Component.h"
#include "Subject.h"

namespace GameEngine
{
    class Subject;

    class IObserver
    {
    public:
        virtual void Notify(Subject* subject, GameEvent event, EventData* eventData = nullptr) = 0;

        IObserver() = default;
        virtual ~IObserver() = default;
        IObserver(const IObserver& other) = delete;
        IObserver(IObserver&& other) = delete;
        IObserver& operator=(const IObserver& other) = delete;
        IObserver& operator=(IObserver&& other) = delete;
    };
}
