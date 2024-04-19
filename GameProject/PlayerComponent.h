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

class ActorDataComponent final : public GameEngine::Component
{
public:
    explicit ActorDataComponent(GameEngine::GameObject* gameObject, int health);
    ActorDataComponent(const ActorDataComponent& other) = delete;
    ActorDataComponent(ActorDataComponent&& other) noexcept = delete;
    ActorDataComponent& operator=(const ActorDataComponent& other) = delete;
    ActorDataComponent& operator=(ActorDataComponent&& other) noexcept = delete;
    ~ActorDataComponent() override = default;

    void IncreaseScore(int value);
    [[nodiscard]] int GetScore() const { return m_Score; }
    void Hit();
    [[nodiscard]] int GetHealth() const { return m_Health; }
private:
    int m_Health{ 3 };
    int m_Score{};
};


