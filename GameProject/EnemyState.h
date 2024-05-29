#pragma once
#include <queue>
#include <glm/vec2.hpp>

class RotatingSpriteComponent;
namespace GameEngine
{
    class SpriteComponent;
}
class EnemyComponent;
struct EnemyPathData
{
    bool isRotating{false};
    bool isRotatingClockwise{true};
    float radius{};
    float totalRotationAngle{};
    float accumRotationAngle{};
    glm::vec2 centerOfRotation{};
    glm::vec2 destination{};
};
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
    bool m_IsFollowingPath{false};
    glm::vec2 m_Direction{ 0,0 };
    std::queue<EnemyPathData> m_PathData;
};
