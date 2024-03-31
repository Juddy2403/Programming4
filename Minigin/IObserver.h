#pragma once
#include "GameObject.h"

namespace GameEngine
{
    class Subject;
    class IObserver
    {
    private:
        std::string m_Name{};
    public:
        virtual void Notify(Subject* subject, GameEvent event = GameEvent::event) = 0;

        IObserver() = default;
        explicit IObserver(std::string name);
        virtual ~IObserver() = default;
        IObserver(const IObserver& other) = delete;
        IObserver(IObserver&& other) = delete;
        IObserver& operator=(const IObserver& other) = delete;
        IObserver& operator=(IObserver&& other) = delete;
    };
    class HealthObserver final : public IObserver, public Component
    {
    private:
    public:
        HealthObserver(const std::string& name, GameObject* gameObject);
        virtual void Notify(Subject* subject, GameEvent event) override;
    };

    class ScoreObserver final : public IObserver, public Component
    {
    private:
    public:
        ScoreObserver(const std::string& name, GameObject* gameObject);
        virtual void Notify(Subject* subject, GameEvent event) override;
    };
}
