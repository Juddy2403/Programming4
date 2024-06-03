#include "ButterflyComponent.h"
#include "Subjects/GameObject.h"

ButterflyComponent::ButterflyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent, PlayerComponent* playerComponent):
    EnemyComponent(gameObj, spriteComponent, rotatingComponent, playerComponent)
{}

void ButterflyComponent::Update()
{
    EnemyComponent::Update();
}
void ButterflyComponent::GetInAttackState()
{
    m_CurrentState->Exit(this);
    m_CurrentState = std::make_unique<BossBombingRun>();
    m_CurrentState->Enter(this);
}
bool ButterflyComponent::HasBeenHit()
{
    GetGameObjParent()->SetDestroyedFlag();
    return true;
}
EnemyId ButterflyComponent::GetEnemyID() const
{
    if (m_CurrentState->IsDiving()) return EnemyId::butterflyDiving;
    return EnemyId::butterfly;
}