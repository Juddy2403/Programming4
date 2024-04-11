#pragma once
#include "Component.h"

namespace GameEngine
{
    class ActorComponent final : public Component
    {
    public:
        explicit ActorComponent(GameObject* gameObject,int lives, int speed = 100);
        ActorComponent(const ActorComponent& other) = delete;
        ActorComponent(ActorComponent&& other) noexcept = delete;
        ActorComponent& operator=(const ActorComponent& other) = delete;
        ActorComponent& operator=(ActorComponent&& other) noexcept = delete;
        //void Update() override;
        //void Render() override;
        ~ActorComponent() override = default;

        void Hit();
        [[nodiscard]] int GetRemainingLives() const { return m_Lives; }
        [[nodiscard]] int GetSpeed() const { return m_Speed; }
        void Move(const glm::vec2& direction);
    private:
        int m_Speed{};
        int m_Lives{ 3 };
    };

    class ScoreComponent final : public Component
    {
    public:
        explicit ScoreComponent(GameObject* gameObject);
        ScoreComponent(const ScoreComponent& other) = delete;
        ScoreComponent(ScoreComponent&& other) noexcept = delete;
        ScoreComponent& operator=(const ScoreComponent& other) = delete;
        ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;
        ~ScoreComponent() override = default;

        void IncreaseScore(int value);
        [[nodiscard]] int GetScore() const { return m_Score; }
    private:
        int m_Score{};
    };
}

