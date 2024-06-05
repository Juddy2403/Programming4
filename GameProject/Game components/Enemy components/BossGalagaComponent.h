#pragma once
#include "Enemy States/BossStage.h"
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

    //returns true if boss is destroyed
    virtual bool HasBeenHit() override;
    virtual EnemyId GetEnemyID() const override;
    virtual void GetInAttackState() override;
    virtual void GetInBeamAttackState();

private:
    std::unique_ptr<BossStage> m_BossStage;
};
