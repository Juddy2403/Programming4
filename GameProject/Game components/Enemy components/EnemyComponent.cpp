#include "EnemyComponent.h"
#include "Components/SpriteComponent.h"
#include "Game components/RotatingSpriteComponent.h"
#include "Subjects/GameObject.h"

EnemyComponent::EnemyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent):
    Component(gameObj),
    m_CurrentState(std::make_unique<GetInFormationState>()),
    m_SpriteComponent(spriteComponent),
    m_RotatingComponent(rotatingComponent),
    m_NrOfStages((m_SpriteComponent->m_SpriteInfo.m_NrOfCols - 1) * 4)
{
    m_InitXPos = spriteComponent->m_SpriteInfo.m_StartPos.x;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 1;
}
void EnemyComponent::SetFormationPosition(const glm::ivec2& formationPos)
{
    m_FormationPosition = formationPos;
    m_CurrentState->Enter(this);
}
void EnemyComponent::SetFormationTrajectory(const std::queue<PathData>& pathDataQueue)
{
    m_FormationTrajectory.SetPathData(pathDataQueue, GetGameObjParent()->GetPosition());
}

void EnemyComponent::Update()
{
    if(auto nextState = m_CurrentState->Update(this, m_SpriteComponent, m_RotatingComponent))
    {
        m_CurrentState->Exit(this);
        m_CurrentState.reset(nextState);
        m_CurrentState->Enter(this);
    }
}



