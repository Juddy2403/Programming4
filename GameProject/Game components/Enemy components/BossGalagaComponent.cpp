#include "BossGalagaComponent.h"

BossGalagaComponent::BossGalagaComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent):
    EnemyComponent(gameObj, spriteComponent, rotatingComponent),
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
    if (m_IsDiving) return EnemyId::bossGalagaDiving;
    return EnemyId::bossGalaga;
}
