#include "BossGalagaComponent.h"

#include "Enemy States/BossBombingRunState.h"

BossGalagaComponent::BossGalagaComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent, PlayerComponent* playerComponent):
    EnemyComponent(gameObj, spriteComponent, rotatingComponent, playerComponent),
    m_BossStage(std::make_unique<BossStageOne>())
{}
void BossGalagaComponent::Update()
{
    EnemyComponent::Update();
}
bool BossGalagaComponent::HasBeenHit()
{
    BossStage* bossStage = m_BossStage->HasBeenHit(*GetGameObjParent());
    if (bossStage)
    {
        m_BossStage.reset(bossStage);
        return false;
    }
    return true;
}
EnemyId BossGalagaComponent::GetEnemyID() const
{
    if (m_CurrentState->IsDiving()) return EnemyId::bossGalagaDiving;
    return EnemyId::bossGalaga;
}
void BossGalagaComponent::GetInAttackState()
{
    m_CurrentState->Exit(this);
    m_CurrentState = std::make_unique<BossBombingRun>();
    m_CurrentState->Enter(this);
}
void BossGalagaComponent::GetInBeamAttackState()
{
    m_CurrentState->Exit(this);
    m_CurrentState = std::make_unique<BossShootingBeam>();
    m_CurrentState->Enter(this);
}
