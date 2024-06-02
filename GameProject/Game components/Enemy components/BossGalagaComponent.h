﻿#pragma once
#include "BossStage.h"
#include "EnemyComponent.h"

class BossGalagaComponent final : public EnemyComponent
{
public:
    explicit BossGalagaComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingComponent, PlayerComponent* playerComponent);

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