#pragma once
#include "Component.h"

class BeeComponent final : public GameEngine::Component
{
public:
    explicit BeeComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent);

    BeeComponent(const BeeComponent& other) = delete;
    BeeComponent(BeeComponent&& other) noexcept = delete;
    BeeComponent& operator=(const BeeComponent& other) = delete;
    BeeComponent& operator=(BeeComponent&& other) noexcept = delete;
    ~BeeComponent() override = default;
    
    void Update() override;
private:
    glm::vec2 m_Speed{ 0.0f, 100.0f };
    GameEngine::SpriteComponent* m_SpriteComponent{};
};

class ButterflyComponent final : public GameEngine::Component
{
public:
    explicit ButterflyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent);

    ButterflyComponent(const ButterflyComponent& other) = delete;
    ButterflyComponent(ButterflyComponent&& other) noexcept = delete;
    ButterflyComponent& operator=(const ButterflyComponent& other) = delete;
    ButterflyComponent& operator=(ButterflyComponent&& other) noexcept = delete;
    ~ButterflyComponent() override = default;
    
    void Update() override;
private:
    glm::vec2 m_Speed{ 0.0f, 100.0f };
    GameEngine::SpriteComponent* m_SpriteComponent{};
};

class BossGalagaComponent final : public GameEngine::Component
{
public:
    explicit BossGalagaComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent);

    BossGalagaComponent(const BossGalagaComponent& other) = delete;
    BossGalagaComponent(BossGalagaComponent&& other) noexcept = delete;
    BossGalagaComponent& operator=(const BossGalagaComponent& other) = delete;
    BossGalagaComponent& operator=(BossGalagaComponent&& other) noexcept = delete;
    ~BossGalagaComponent() override = default;
    
    void Update() override;
private:
    glm::vec2 m_Speed{ 0.0f, 100.0f };
    GameEngine::SpriteComponent* m_SpriteComponent{};
};
