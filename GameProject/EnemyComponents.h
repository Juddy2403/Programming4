#pragma once
#include "BossStage.h"
#include "Component.h"
#include "DataStructs.h"
#include "EnemyState.h"
#include "RotatingSpriteComponent.h"

class EnemyComponent : public GameEngine::Component
{
public:
    explicit EnemyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingComponent);

    EnemyComponent(const EnemyComponent& other) = delete;
    EnemyComponent(EnemyComponent&& other) noexcept = delete;
    EnemyComponent& operator=(const EnemyComponent& other) = delete;
    EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;
    ~EnemyComponent() override = default;

    void SetFormationPosition(const glm::ivec2& formationPos) { m_FormationPosition = formationPos; }
    glm::ivec2 GetFormationPosition() const { return m_FormationPosition; }
    virtual void Update() override;
    virtual bool HasBeenHit() = 0;
    bool IsDiving() const { return m_IsDiving; }
    virtual EnemyId GetEnemyID() const = 0;
protected:
    std::unique_ptr<EnemyState> m_CurrentState;
    bool m_IsDiving{ false };
    glm::vec2 m_Speed{ 0.0f,100.0f };
    GameEngine::SpriteComponent* m_SpriteComponent{};
    RotatingSpriteComponent* m_RotatingComponent{};
    glm::ivec2 m_FormationPosition{};
    const int m_NrOfStages{};
    int m_InitXPos{};
    float m_CurrentTime{};
    int m_CurrentRotationStage{};
};

class BeeComponent final : public EnemyComponent
{
public:
    explicit BeeComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingComponent);

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
    explicit ButterflyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingComponent);

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
    explicit BossGalagaComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingComponent);

    BossGalagaComponent(const BossGalagaComponent& other) = delete;
    BossGalagaComponent(BossGalagaComponent&& other) noexcept = delete;
    BossGalagaComponent& operator=(const BossGalagaComponent& other) = delete;
    BossGalagaComponent& operator=(BossGalagaComponent&& other) noexcept = delete;
    ~BossGalagaComponent() override = default;

    void Update() override;
    //returns true if boss is destroyed
    virtual bool HasBeenHit() override;
    virtual EnemyId GetEnemyID() const override;
private:
    std::unique_ptr<BossStage> m_BossStage;
};
