﻿#include "BeeComponent.h"

#include "Enemy States/BeeBombingRunState.h"
#include "Game observers/EnemyAIManager.h"
#include "Subjects/GameObject.h"

BeeComponent::BeeComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent, PlayerComponent* playerComponent):
    EnemyComponent(gameObj, spriteComponent, rotatingComponent,playerComponent)
{}

void BeeComponent::GetInAttackState()
{
    m_CurrentState->Exit(this);
    m_CurrentState = std::make_unique<BeeBombingRun>();
    m_CurrentState->Enter(this);
}
EnemyId BeeComponent::GetEnemyID() const
{
    if(!m_CurrentState) return EnemyId::bee;
    if (m_CurrentState->IsDiving()) return EnemyId::beeDiving;
    return EnemyId::bee;
}
