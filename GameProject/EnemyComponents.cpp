#include "EnemyComponents.h"

#include "GameObject.h"

EnemyComponent::EnemyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent):
    Component(gameObj), m_SpriteComponent(spriteComponent)
{}

BeeComponent::BeeComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent):
    EnemyComponent(gameObj, spriteComponent)
{}

void BeeComponent::Update()
{}
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
ButterflyComponent::ButterflyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent):
    EnemyComponent(gameObj, spriteComponent)
{}

void ButterflyComponent::Update()
{}
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
BossGalagaComponent::BossGalagaComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent):
    EnemyComponent(gameObj, spriteComponent),
    m_BossStage(std::make_unique<BossStageOne>())
{}
void BossGalagaComponent::Update()
{}
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
    if (m_IsDiving) return EnemyId::bossGalagaDiving;
    return EnemyId::bossGalaga;
}
