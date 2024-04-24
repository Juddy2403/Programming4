#pragma once
#include "Component.h"

class RotatingSpriteComponent final : public GameEngine::SpriteComponent
{
public:
    explicit RotatingSpriteComponent(GameEngine::GameObject* gameObj);
    explicit RotatingSpriteComponent(GameEngine::GameObject* gameObj, const std::string& filename);
    explicit RotatingSpriteComponent(GameEngine::GameObject* gameObj, const std::shared_ptr<GameEngine::Texture2D>& texture);

    RotatingSpriteComponent(const RotatingSpriteComponent& other) = delete;
    RotatingSpriteComponent(RotatingSpriteComponent&& other) noexcept = delete;
    RotatingSpriteComponent& operator=(const RotatingSpriteComponent& other) = delete;
    RotatingSpriteComponent& operator=(RotatingSpriteComponent&& other) noexcept = delete;
    ~RotatingSpriteComponent() override = default;

    virtual void Update() override;
private:
    bool m_IsColIncreasing{ true };
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

class ScoreComponent final : public GameEngine::Component
{
public:
    explicit ScoreComponent(GameEngine::GameObject* gameObject);
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


