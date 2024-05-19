#include "EnemyComponent.h"
#include "Components/SpriteComponent.h"
#include "Game components/RotatingSpriteComponent.h"
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



