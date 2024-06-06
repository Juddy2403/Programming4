﻿#pragma once
#include "Enemy States/BossStage.h"
#include "EnemyComponent.h"

class BossGalagaComponent final : public EnemyComponent
{
public:
    explicit BossGalagaComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent, PlayerComponent* playerComponent);

    BossGalagaComponent(const BossGalagaComponent& other) = delete;
    BossGalagaComponent(BossGalagaComponent&& other) noexcept = delete;
    BossGalagaComponent& operator=(const BossGalagaComponent& other) = delete;
    BossGalagaComponent& operator=(BossGalagaComponent&& other) noexcept = delete;
    ~BossGalagaComponent() override = default;

    bool IsDiving() const { return m_CurrentState->IsDiving(); }
    //returns true if boss is destroyed
    virtual bool HasBeenHit() override;
    virtual EnemyId GetEnemyID() const override;
    virtual void GetInAttackState() override;
    virtual void GetInBeamAttackState();
    void CapturedFighter() { m_HasCapturedFighter = true; }
    bool HasCapturedFighter() const { return m_HasCapturedFighter; }
private:
    bool m_HasCapturedFighter{ false };
    std::unique_ptr<BossStage> m_BossStage;
};
