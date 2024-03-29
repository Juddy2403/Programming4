#pragma once
#include "Component.h"

namespace GameEngine
{
    class ActorComponent final : public GameEngine::Component
    {
    public:
        explicit ActorComponent(GameObject* gameObject,int lives);
        ActorComponent(const ActorComponent& other) = delete;
        ActorComponent(ActorComponent&& other) noexcept = delete;
        ActorComponent& operator=(const ActorComponent& other) = delete;
        ActorComponent& operator=(ActorComponent&& other) noexcept = delete;
        //void Update() override;
        //void Render() override;
        ~ActorComponent() override = default;

        void Hit();
        void IncreaseScore(int value);
        [[nodiscard]] int GetScore() const { return m_Score; }
        [[nodiscard]] int GetRemainingLives() const { return m_Lives; }
    private:
        int m_Score{};
        int m_Lives{ 3 };
    };
}

