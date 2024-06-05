#include "EnemyComponent.h"
#include "Components/SpriteComponent.h"
#include "Enemy States/GetInFormationState.h"
#include "Enemy States/IdleState.h"
#include "Game components/FormationComponent.h"
#include "Game components/RotatingSpriteComponent.h"
#include "Game observers/EnemyAIManager.h"
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
    EnemyAIManager::AddEnemy(this);
}
EnemyComponent::~EnemyComponent()
{
    if(m_CurrentState) m_CurrentState->Exit(this);
    EnemyAIManager::RemoveEnemy(this);
}
void EnemyComponent::GetInIdleState()
{
    m_CurrentState->Exit(this);
    m_CurrentState = std::make_unique<IdleState>();
    m_CurrentState->Enter(this);
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
            m_CurrentState = std::move(nextState);
            m_CurrentState->Enter(this);
        }
    }
    else if (FormationObserver::GetCurrentStage() == m_Stage)
    {
        FormationObserver::EnemySetOut();
        m_CurrentState = std::make_unique<GetInFormationState>();
        m_CurrentState->Enter(this);
    }
}
int EnemyComponent::GetRotationStage(const glm::vec2& direction) const
{
    //calculate rotation angle based on the direction
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

bool EnemyComponent::UpdateTrajectory(Trajectory& trajectory) const
{
    const glm::vec2 currentPos = GetGameObjParent()->GetPosition();
    auto [newPos, hasDirectionChanged] = trajectory.Update(GetSpeed(), currentPos);
    if (hasDirectionChanged)
    {
        if (trajectory.IsComplete()) return true;
        int rotationStage = GetRotationStage(trajectory.GetDirection());
        UpdateSprite(rotationStage);
    }
    GetGameObjParent()->SetPosition({ newPos,0 });
    return false;
}
