#include "EnemyComponents.h"
#include "Subjects/GameObject.h"
#include "Components/SpriteComponent.h"
#include "Managers/TimeManager.h"

EnemyComponent::EnemyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent):
    Component(gameObj),
    m_CurrentState(std::make_unique<IdleState>()),
    m_SpriteComponent(spriteComponent),
    m_RotatingComponent(rotatingComponent),
    m_NrOfStages((m_SpriteComponent->m_SpriteInfo.m_NrOfCols - 1) * 4)
{
    m_InitXPos = spriteComponent->m_SpriteInfo.m_StartPos.x;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 1;
}
void EnemyComponent::Update()
{
    m_CurrentState->Update(this);

    m_CurrentTime += GameEngine::TimeManager::GetElapsed();
    if (m_CurrentTime < .5f) return;
    const auto rotationInfo = m_RotatingComponent->GetColFlipPair(m_CurrentRotationStage);

    m_SpriteComponent->m_SpriteInfo.m_StartPos.x = rotationInfo.first * (m_SpriteComponent->m_SpriteInfo.m_Width
        + m_SpriteComponent->m_SpriteInfo.m_Spacing) + m_InitXPos;

    m_SpriteComponent->SetFlipMode(rotationInfo.second);
    ++m_CurrentRotationStage %= m_NrOfStages;
    m_SpriteComponent->UpdateSrcRect();
    m_CurrentTime = 0;
}

BeeComponent::BeeComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent):
    EnemyComponent(gameObj, spriteComponent, rotatingComponent)
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
ButterflyComponent::ButterflyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent):
    EnemyComponent(gameObj, spriteComponent, rotatingComponent)
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
