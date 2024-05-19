#pragma once
#include "Components/Component.h"

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
