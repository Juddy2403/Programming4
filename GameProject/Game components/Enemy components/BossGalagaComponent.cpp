#include "BossGalagaComponent.h"

#include "Enemy States/BombingRunState.h"
#include "Enemy States/BossShootingBeamState.h"
#include "Game components/CapturedFighterComponent.h"

BossGalagaComponent::BossGalagaComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent, PlayerComponent* playerComponent):
    EnemyComponent(gameObj, spriteComponent, playerComponent),
    m_BossStage(std::make_unique<BossStageOne>())
{}

bool BossGalagaComponent::HasBeenHit()
{
    BossStage* bossStage = m_BossStage->HasBeenHit(this);
    if (bossStage)
    {
        m_BossStage.reset(bossStage);
        return false;
    }
    if(m_CapturedFighter) m_CapturedFighter->GetGameObjParent()->SetDestroyedFlag();
    return true;
}
EnemyId BossGalagaComponent::GetEnemyID() const
{
    if(!m_CurrentState) return EnemyId::bossGalaga;
    if (m_CurrentState->IsDiving()) return EnemyId::bossGalagaDiving;
    return EnemyId::bossGalaga;
}
void BossGalagaComponent::GetInAttackState()
{
    m_CurrentState->Exit(this);
    m_CurrentState = std::make_unique<BombingRunState>();
    m_CurrentState->Enter(this);
}
void BossGalagaComponent::GetInBeamAttackState()
{
    m_CurrentState->Exit(this);
    m_CurrentState = std::make_unique<BossShootingBeamState>();
    m_CurrentState->Enter(this);
}
void BossGalagaComponent::SetCapturedFighter(CapturedFighterComponent* capturedFighter)
{
     m_CapturedFighter = capturedFighter; 
}
