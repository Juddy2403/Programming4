#pragma once

class EnemyComponent;
class EnemyState
{
public:
    virtual EnemyState* Update(EnemyComponent* enemyComponent) = 0;
    virtual ~EnemyState() = default;
};

class IdleState final : public EnemyState
{
    virtual EnemyState* Update(EnemyComponent* enemyComponent) override;
};
