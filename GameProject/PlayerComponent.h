#pragma once
#include "Components/Component.h"

class PlayerComponent final : public GameEngine::Component
{
public:
    explicit PlayerComponent(GameEngine::GameObject* gameObject, int playerID);
    PlayerComponent(const PlayerComponent& other) = delete;
    PlayerComponent(PlayerComponent&& other) noexcept = delete;
    PlayerComponent& operator=(const PlayerComponent& other) = delete;
    PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;
    ~PlayerComponent() override = default;
    
    [[nodiscard]] int GetPlayerID() const { return m_PlayerID; }
private:
    int m_PlayerID{ -1 };
};


class HealthComponent final : public GameEngine::Component
{
public:
    explicit HealthComponent(GameEngine::GameObject* gameObject, int health);
    HealthComponent(const HealthComponent& other) = delete;
    HealthComponent(HealthComponent&& other) noexcept = delete;
    HealthComponent& operator=(const HealthComponent& other) = delete;
    HealthComponent& operator=(HealthComponent&& other) noexcept = delete;
    ~HealthComponent() override = default;
    
    void Hit();
    [[nodiscard]] int GetHealth() const { return m_Health; }
private:
    int m_Health{ 3 };
};



