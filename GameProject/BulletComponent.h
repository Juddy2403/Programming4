﻿#pragma once
#include "Component.h"

class BulletComponent final : public GameEngine::Component
{
public:
    explicit BulletComponent(GameEngine::GameObject* gameObj,int playerID ,GameEngine::SpriteComponent* spriteComponent);

    BulletComponent(const BulletComponent& other) = delete;
    BulletComponent(BulletComponent&& other) noexcept = delete;
    BulletComponent& operator=(const BulletComponent& other) = delete;
    BulletComponent& operator=(BulletComponent&& other) noexcept = delete;
    ~BulletComponent() override = default;
    
    void Update() override;
    [[nodiscard]] int GetPlayerID() const { return m_PlayerID; }
private:
    int m_PlayerID{-1};
    glm::vec2 m_Velocity{ 0.0f, -300.0f };
    GameEngine::SpriteComponent* m_SpriteComponent{};
};
