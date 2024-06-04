#pragma once
#include "EnemyState.h"

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
