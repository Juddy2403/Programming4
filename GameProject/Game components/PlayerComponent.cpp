#include "PlayerComponent.h"

#include "PlayerHealthComponent.h"

PlayerComponent::PlayerComponent(GameEngine::GameObject* gameObject, int playerID):
Component(gameObject), m_PlayerID(playerID){}

void PlayerComponent::GetCaptured(const glm::vec2& enemyPos)
{
    std::queue<PathData> pathDataQueue;
    PathData pathData{};

    pathData.destination = glm::vec2(enemyPos);
    pathData.destination.x += 20;
    pathDataQueue.push(pathData);

    // Set the trajectory
    m_CapturedTrajectory = std::make_unique<Trajectory>();
    m_CapturedTrajectory->SetPathData(pathDataQueue, GetGameObjParent()->GetPosition());

    m_IsGettingCaptured = true;
}

void PlayerComponent::Update()
{
    if(m_IsGettingCaptured)
    {
        if(m_CapturedTrajectory->IsComplete())
        {
            auto healthComp = GetGameObjParent()->GetComponent<PlayerHealthComponent>();
            GetGameObjParent()->SetPosition(m_RespawnPos);
            healthComp->Hit();
            m_IsGettingCaptured = false;
            return;
        }
        const glm::vec2 currentPos = GetGameObjParent()->GetPosition();
        auto [newPos, hasDirectionChanged] = m_CapturedTrajectory->Update(m_Speed, currentPos);
        GetGameObjParent()->SetPosition({ newPos,0 });
    }
}


