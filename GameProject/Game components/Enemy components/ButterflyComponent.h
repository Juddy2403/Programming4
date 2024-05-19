#pragma once
#include "EnemyComponent.h"

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

