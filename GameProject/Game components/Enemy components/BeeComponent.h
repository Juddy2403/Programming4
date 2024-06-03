#pragma once
#include "EnemyComponent.h"

class BeeComponent final : public EnemyComponent
{
public:
    explicit BeeComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingComponent, PlayerComponent* playerComponent);

    BeeComponent(const BeeComponent& other) = delete;
    BeeComponent(BeeComponent&& other) noexcept = delete;
    BeeComponent& operator=(const BeeComponent& other) = delete;
    BeeComponent& operator=(BeeComponent&& other) noexcept = delete;
    ~BeeComponent() override = default;

    void Update() override;
    virtual bool HasBeenHit() override;
    virtual void GetInAttackState() override;
    virtual EnemyId GetEnemyID() const override;
private:

};
