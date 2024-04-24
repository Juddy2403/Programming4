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
        explicit IObserver(std::string&& name);
        virtual ~IObserver() = default;
        IObserver(const IObserver& other) = delete;
        IObserver(IObserver&& other) = delete;
        IObserver& operator=(const IObserver& other) = delete;
        IObserver& operator=(IObserver&& other) = delete;
    private:
        std::string m_Name{};
    };

    class HealthObserver final : public IObserver, public Component
    {
    private:
    public:
        explicit HealthObserver(std::string&& name, GameObject* gameObject);
        virtual void Notify(Subject* subject, GameEvent event, EventData* eventData = nullptr) override;
    };

    class ScoreObserver final : public IObserver, public Component
    {
    private:
    public:
        explicit ScoreObserver(std::string&& name, GameObject* gameObject);
        virtual void Notify(Subject* subject, GameEvent event, EventData* eventData = nullptr) override;
    };
}
