#include "EnemyState.h"
#include "Game components/FormationComponent.h"
#include "Game components/RotatingSpriteComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Subjects/GameObject.h"
#include "Trajectory Logic/Parsers.h"

const float GetInFormationState::m_TimeInBetween = 0.2f;

void IdleState::UpdateBackToFormationTrajectory(EnemyComponent* enemyComponent) const
{
    std::queue<PathData> pathDataQueue;
    PathData pathData;
    pathData.destination = glm::vec2(enemyComponent->GetFormationPosition()) + glm::vec2(FormationComponent::GetOffset(),0);
    pathDataQueue.push(pathData);
    m_BackToFormationTrajectory->SetPathData(pathDataQueue, enemyComponent->GetGameObjParent()->GetPosition());
}
void IdleState::GotInFormation(EnemyComponent* enemyComponent) {
    enemyComponent->GetGameObjParent()->NotifyAll(static_cast<int>(GameEvent::gotInFormation));
    int rotationStage = enemyComponent->GetRotationStage({ 0,1 });
    enemyComponent->UpdateSprite(rotationStage);
}
void IdleState::Enter(EnemyComponent* enemyComponent)
{
    if(!TrajectoryMath::ArePositionsEqual(enemyComponent->GetGameObjParent()->GetPosition(),
        enemyComponent->GetFormationPosition()+glm::ivec2{FormationComponent::GetOffset(),0}))
    {
        m_BackToFormationTrajectory = std::make_unique<Trajectory>();
        UpdateBackToFormationTrajectory(enemyComponent);
        return;
    }
    GotInFormation(enemyComponent);
}
std::unique_ptr<EnemyState> IdleState::Update(EnemyComponent* enemyComponent)
{
    if(m_BackToFormationTrajectory != nullptr)
    {
        if (enemyComponent->UpdateTrajectory(*m_BackToFormationTrajectory))
        {
            m_BackToFormationTrajectory = nullptr;
            GotInFormation(enemyComponent);
            return nullptr;
        }
        UpdateBackToFormationTrajectory(enemyComponent);

        return nullptr;
    }
    glm::vec2 formationPos = enemyComponent->GetFormationPosition();
    formationPos.x += FormationComponent::GetOffset();
    enemyComponent->GetGameObjParent()->SetPosition({ formationPos,0 });
    return nullptr;
}
void IdleState::Exit(EnemyComponent* enemyComponent)
{
    enemyComponent->GetGameObjParent()->NotifyAll(static_cast<int>(GameEvent::leftFormation));
}

std::unique_ptr<EnemyState> GetInFormationState::Update(EnemyComponent* enemyComponent)
{
    m_WaitTime = m_TimeInBetween * enemyComponent->m_SetOutTurn;
    m_AccumWaitTime += GameEngine::TimeManager::GetElapsed();
    if (m_AccumWaitTime < m_WaitTime) return nullptr;
    if (enemyComponent->UpdateTrajectory(enemyComponent->GetFormationTrajectory())) return std::make_unique<IdleState>();
    return nullptr;
}
void BeeBombingRun::Enter(EnemyComponent* enemyComponent)
{
    std::queue<PathData> pathDataQueue;
    PathData pathData;

    enemyComponent->GetGameObjParent()->Notify(static_cast<int>(GameEvent::bulletShot),
        static_cast<int>(ObserverIdentifier::bullet));
    // Initial upward movement
    pathData.destination = glm::vec2(enemyComponent->GetGameObjParent()->GetPosition()) + glm::vec2(0, -50);
    pathDataQueue.push(pathData);

    // Loop movement
    pathData = {};
    pathData.isRotating = true;
    pathData.isRotatingClockwise = static_cast<bool>(rand() % 2);
    pathData.centerOfRotation = glm::vec2(enemyComponent->GetGameObjParent()->GetPosition());
    pathData.totalRotationAngle = 3.49066f;
    pathDataQueue.push(pathData);

    // Dive towards the player
    pathData = {};
    const glm::vec2 playerPos = enemyComponent->GetPlayerComponent()->GetGameObjParent()->GetPosition();
    pathData.destination = playerPos + glm::vec2{ 0,-50 };
    pathDataQueue.push(pathData);

    // Loop movement
    pathData = {};
    pathData.isRotating = true;
    pathData.isRotatingClockwise = static_cast<bool>(rand() % 2);
    pathData.centerOfRotation = playerPos;
    pathData.totalRotationAngle = 4.88692f;
    pathDataQueue.push(pathData);

    pathData = {};
    pathData.destination = glm::vec2(enemyComponent->GetFormationPosition());
    pathDataQueue.push(pathData);

    // Set the trajectory
    m_BombingTrajectory->SetPathData(pathDataQueue, enemyComponent->GetGameObjParent()->GetPosition());
}
std::unique_ptr<EnemyState> BeeBombingRun::Update(EnemyComponent* enemyComponent)
{
    if (enemyComponent->UpdateTrajectory(*m_BombingTrajectory)) return std::make_unique<IdleState>();
    return nullptr;
}
void ButterflyBombingRun::Enter(EnemyComponent* enemyComponent)
{
    enemyComponent;
}
std::unique_ptr<EnemyState> ButterflyBombingRun::Update(EnemyComponent* enemyComponent)
{
    enemyComponent;
    return nullptr;
}
void BossBombingRun::Enter(EnemyComponent* enemyComponent)
{
    enemyComponent;
}
std::unique_ptr<EnemyState> BossBombingRun::Update(EnemyComponent* enemyComponent)
{
    enemyComponent;
    return nullptr;
}
