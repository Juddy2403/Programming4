#include "CapturedFighterComponent.h"

#include "FormationComponent.h"
CapturedFighterComponent::CapturedFighterComponent(GameEngine::GameObject* gameObj, BossGalagaComponent* parent, GameEngine::SpriteComponent* spriteComponent):
    Component(gameObj),
    m_RotatingSprite(std::make_unique<RotatingSprite>(spriteComponent)),
    m_GetBackTrajectory(std::make_unique<Trajectory>()),
    m_Parent(parent)
{
    std::queue<PathData> pathDataQueue;
    PathData pathData;

    // Initial movement to get behind the boss
    pathData.destination = glm::vec2(parent->GetGameObjParent()->GetPosition()) + glm::vec2(0, -32);
    pathDataQueue.push(pathData);

    m_GetBackTrajectory->SetPathData(pathDataQueue, gameObj->GetPosition());
}
void CapturedFighterComponent::Update()
{
    if(m_Parent == nullptr || m_Parent->IsDestroyed())
    {
        GetGameObjParent()->SetDestroyedFlag();
        return;
    }
    
    if(m_GetBackTrajectory)
    {
        if(m_GetBackTrajectory->IsComplete())
        {
            m_GetBackTrajectory = nullptr;
            return;
        }
        auto newPos = m_GetBackTrajectory->Update(m_Speed, GetGameObjParent()->GetPosition()).first;
        m_RotatingSprite->RotateSpriteInDirection(m_GetBackTrajectory->GetDirection());
        GetGameObjParent()->SetPosition({ newPos,0 });
    }
    else
    {
        if(m_Parent->IsDiving()) m_RotatingSprite->RotateSpriteInDirection(m_Parent->GetCurDirection());
        else m_RotatingSprite->RotateSpriteInDirection({FormationComponent::GetDirection(),0});
        auto newPos = m_Parent->GetGameObjParent()->GetPosition() + glm::vec3{ 0, -32,0 };
        GetGameObjParent()->SetPosition(newPos);
    }
}
