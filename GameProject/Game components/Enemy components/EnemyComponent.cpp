#include "EnemyComponent.h"
#include "Components/SpriteComponent.h"
#include "Game components/FormationComponent.h"
#include "Game components/RotatingSpriteComponent.h"
#include "Game observers/FormationObserver.h"
#include "Subjects/GameObject.h"

EnemyComponent::EnemyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingComponent, PlayerComponent* playerComponent):
    Component(gameObj),
    m_PlayerComponent(playerComponent),
    m_CurrentState(nullptr),
    m_SpriteComponent(spriteComponent),
    m_RotatingComponent(rotatingComponent),
    m_NrOfRotationStages((m_SpriteComponent->m_SpriteInfo.m_NrOfCols - 1) * 4)
{
    m_InitXPos = spriteComponent->m_SpriteInfo.m_StartPos.x;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 1;
}
void EnemyComponent::SetFormationPosition(const glm::ivec2& formationPos)
{
    m_FormationPosition = formationPos;
}
void EnemyComponent::SetFormationTrajectory(const std::queue<PathData>& pathDataQueue)
{
    m_FormationTrajectory.SetPathData(pathDataQueue, GetGameObjParent()->GetPosition());
}

void EnemyComponent::Update()
{
    if (m_CurrentState)
    {
        if (auto nextState = m_CurrentState->Update(this))
        {
            m_CurrentState->Exit(this);
            m_CurrentState.reset(nextState);
            m_CurrentState->Enter(this);
        }
    }
    else
    {
        if (FormationObserver::GetCurrentStage() == m_Stage)
        {
            FormationObserver::EnemySetOut();
            m_CurrentState = std::make_unique<GetInFormationState>();
            m_CurrentState->Enter(this);
        }
    }
}
int EnemyComponent::GetRotationStage() const
{
    //calculate rotation angle based on the direction
    const auto direction = m_FormationTrajectory.GetDirection();
    float rotationAngle = -(glm::atan(-direction.y, direction.x) - glm::pi<float>() / 2);
    //convert angle between 0 and 2*pi
    if (rotationAngle < 0) rotationAngle += glm::pi<float>() * 2;
    return static_cast<int>(rotationAngle / (glm::pi<float>() * 2) * m_NrOfRotationStages);
}
void EnemyComponent::UpdateSprite(int rotationStage) const
{
    const auto rotationInfo = m_RotatingComponent->GetColFlipPair(rotationStage);
    m_SpriteComponent->m_SpriteInfo.m_StartPos.x = rotationInfo.first * (m_SpriteComponent->m_SpriteInfo.m_Width
        + m_SpriteComponent->m_SpriteInfo.m_Spacing) + GetInitXPos();
    m_SpriteComponent->SetFlipMode(rotationInfo.second);
    m_SpriteComponent->UpdateSrcRect();
}
