#pragma once
#include <SDL_syswm.h>

#include "Component.h"

class FighterComponent final : public GameEngine::Component
{
public:
    explicit FighterComponent(GameEngine::GameObject* gameObject, GameEngine::SpriteComponent* spriteComponent);
    FighterComponent(const FighterComponent& other) = delete;
    FighterComponent(FighterComponent&& other) noexcept = delete;
    FighterComponent& operator=(const FighterComponent& other) = delete;
    FighterComponent& operator=(FighterComponent&& other) noexcept = delete;
    ~FighterComponent() override = default;

    virtual void Update() override;
private:
    GameEngine::SpriteComponent* m_SpriteComponent{};
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
