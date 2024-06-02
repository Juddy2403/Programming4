﻿#include "ButterflyComponent.h"
#include "Subjects/GameObject.h"

ButterflyComponent::ButterflyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent, PlayerComponent* playerComponent):
    EnemyComponent(gameObj, spriteComponent, rotatingComponent, playerComponent)
{}

void ButterflyComponent::Update()
{
    EnemyComponent::Update();
}
bool ButterflyComponent::HasBeenHit()
{
    GetGameObjParent()->SetDestroyedFlag();
    return true;
}
EnemyId ButterflyComponent::GetEnemyID() const
{
    if (m_IsDiving) return EnemyId::butterflyDiving;
    return EnemyId::butterfly;
}