#include "BeeComponent.h"
#include "Subjects/GameObject.h"

BeeComponent::BeeComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent, PlayerComponent* playerComponent):
    EnemyComponent(gameObj, spriteComponent, rotatingComponent,playerComponent)
{}

void BeeComponent::Update()
{
    EnemyComponent::Update();
}
bool BeeComponent::HasBeenHit()
{
    GetGameObjParent()->SetDestroyedFlag();
    return true;
}
EnemyId BeeComponent::GetEnemyID() const
{
    if (m_IsDiving) return EnemyId::beeDiving;
    return EnemyId::bee;
}