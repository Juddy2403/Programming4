#pragma once
#include "BossStage.h"
#include "Component.h"
#include "DataStructs.h"

class EnemyComponent : public GameEngine::Component
{
public:
    explicit EnemyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent);

    EnemyComponent(const EnemyComponent& other) = delete;
    EnemyComponent(EnemyComponent&& other) noexcept = delete;
    EnemyComponent& operator=(const EnemyComponent& other) = delete;
    EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;
    ~EnemyComponent() override = default;
    
    virtual void Update() override = 0;
    virtual bool HasBeenHit() = 0;
    bool IsDiving() const { return m_IsDiving; }
    virtual EnemyId GetEnemyID() const = 0;
protected:
    bool m_IsDiving{false};
    glm::vec2 m_Speed{ 0.0f, 100.0f };
    GameEngine::SpriteComponent* m_SpriteComponent{};
};

class BeeComponent final : public EnemyComponent
{
public:
    explicit BeeComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent);

    BeeComponent(const BeeComponent& other) = delete;
    BeeComponent(BeeComponent&& other) noexcept = delete;
    BeeComponent& operator=(const BeeComponent& other) = delete;
    BeeComponent& operator=(BeeComponent&& other) noexcept = delete;
    ~BeeComponent() override = default;
    
    void Update() override;
    virtual bool HasBeenHit() override;
    virtual EnemyId GetEnemyID() const override;
private:
};

class ButterflyComponent final : public EnemyComponent
{
public:
    explicit ButterflyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent);

    ButterflyComponent(const ButterflyComponent& other) = delete;
    ButterflyComponent(ButterflyComponent&& other) noexcept = delete;
    ButterflyComponent& operator=(const ButterflyComponent& other) = delete;
    ButterflyComponent& operator=(ButterflyComponent&& other) noexcept = delete;
    ~ButterflyComponent() override = default;
    
    void Update() override;
    virtual bool HasBeenHit() override;
    virtual EnemyId GetEnemyID() const override;
private:
};

class BossGalagaComponent final : public EnemyComponent
{
public:
    explicit BossGalagaComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent);

    BossGalagaComponent(const BossGalagaComponent& other) = delete;
    BossGalagaComponent(BossGalagaComponent&& other) noexcept = delete;
    BossGalagaComponent& operator=(const BossGalagaComponent& other) = delete;
    BossGalagaComponent& operator=(BossGalagaComponent&& other) noexcept = delete;
    ~BossGalagaComponent() override = default;
    
    void Update() override;
    virtual bool HasBeenHit() override;
    virtual EnemyId GetEnemyID() const override;
private:
    std::unique_ptr<BossStage> m_BossStage;
};
