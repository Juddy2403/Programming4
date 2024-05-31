#pragma once
#include "Trajectory Logic/Trajectory.h"

class RotatingSpriteComponent;
namespace GameEngine
{
    class SpriteComponent;
}
class EnemyComponent;

class EnemyState
{
public:
    virtual void Enter([[maybe_unused]] EnemyComponent* enemyComponent) {}
    virtual void Exit([[maybe_unused]] EnemyComponent* enemyComponent) {}
    virtual EnemyState* Update(EnemyComponent* enemyComponent, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingSpriteComponent) = 0;
    virtual ~EnemyState() = default;
};

class IdleState final : public EnemyState
{
public:
    virtual EnemyState* Update(EnemyComponent* enemyComponent, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingSpriteComponent) override;
};

class GetInFormationState final : public EnemyState
{
public:
    virtual void Enter([[maybe_unused]] EnemyComponent* enemyComponent) override;
    virtual EnemyState* Update(EnemyComponent* enemyComponent, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingSpriteComponent) override;
private:
    int GetRotationStage(EnemyComponent* enemyComponent);
};
