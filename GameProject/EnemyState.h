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
    virtual bool IsDiving() const = 0;
    virtual std::unique_ptr<EnemyState> Update(EnemyComponent* enemyComponent) = 0;
    virtual ~EnemyState() = default;
};

class IdleState final : public EnemyState
{
public:
    void Enter([[maybe_unused]] EnemyComponent* enemyComponent) override;
    virtual std::unique_ptr<EnemyState> Update(EnemyComponent* enemyComponent) override;
    void Exit([[maybe_unused]] EnemyComponent* enemyComponent) override;
    virtual bool IsDiving() const override { return false; }
private:
    void UpdateBackToFormationTrajectory(EnemyComponent* enemyComponent) const;
    static void GotInFormation(EnemyComponent* enemyComponent);
    std::unique_ptr<Trajectory> m_BackToFormationTrajectory{ nullptr };
};

class GetInFormationState final : public EnemyState
{
public:
    virtual std::unique_ptr<EnemyState> Update(EnemyComponent* enemyComponent) override;
    virtual bool IsDiving() const override { return true; }
private:
    float m_AccumWaitTime{};
    float m_WaitTime{};
    static const float m_TimeInBetween;
};

class BeeBombingRun final : public EnemyState
{
public:
    virtual void Enter([[maybe_unused]] EnemyComponent* enemyComponent) override;
    virtual std::unique_ptr<EnemyState> Update(EnemyComponent* enemyComponent) override;
    virtual bool IsDiving() const override { return true; }
private:
    std::unique_ptr<Trajectory> m_BombingTrajectory{ std::make_unique<Trajectory>() };
};

class ButterflyBombingRun final : public EnemyState
{
public:
    virtual void Enter([[maybe_unused]] EnemyComponent* enemyComponent) override;
    virtual std::unique_ptr<EnemyState> Update(EnemyComponent* enemyComponent) override;
    virtual bool IsDiving() const override { return true; }
private:
    std::unique_ptr<Trajectory> m_BombingTrajectory{ std::make_unique<Trajectory>() };
};

class BossBombingRun final : public EnemyState
{
public:
    virtual void Enter([[maybe_unused]] EnemyComponent* enemyComponent) override;
    virtual std::unique_ptr<EnemyState> Update(EnemyComponent* enemyComponent) override;
    virtual bool IsDiving() const override { return true; }
private:
    std::unique_ptr<Trajectory> m_BombingTrajectory{ std::make_unique<Trajectory>() };
};
