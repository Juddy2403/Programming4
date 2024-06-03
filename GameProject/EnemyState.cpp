#include "EnemyState.h"
#include "Game components/FormationComponent.h"
#include "Game components/RotatingSpriteComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Subjects/GameObject.h"
#include "Trajectory Logic/Parsers.h"

const float GetInFormationState::m_TimeInBetween = 0.2f;

void IdleState::Enter(EnemyComponent* enemyComponent)
{
    enemyComponent->GetGameObjParent()->NotifyAll(static_cast<int>(GameEvent::gotInFormation));
    int rotationStage = enemyComponent->GetRotationStage({0,1});
    enemyComponent->UpdateSprite(rotationStage);
}
std::unique_ptr<EnemyState> IdleState::Update(EnemyComponent* enemyComponent)
{
    glm::vec2 formationPos = enemyComponent->GetFormationPosition();
    formationPos.x += FormationComponent::GetOffset();
    enemyComponent->GetGameObjParent()->SetPosition({ formationPos,0 });
    return nullptr;
}
void IdleState::Exit(EnemyComponent* enemyComponent)
{
    enemyComponent->GetGameObjParent()->NotifyAll(static_cast<int>(GameEvent::leftFormation));
}

void GetInFormationState::Enter(EnemyComponent* enemyComponent)
{
    //std::queue<PathData> pathDataQueue = Parser::ParseTrajectory("../Data/Formations/trajectory.json");
    //TODO: the wait time should be set here but it isnt since at this point the set out turn is 0
    m_WaitTime = m_TimeInBetween * enemyComponent->m_SetOutTurn;
    
}

std::unique_ptr<EnemyState> GetInFormationState::Update(EnemyComponent* enemyComponent)
{
    m_WaitTime = m_TimeInBetween * enemyComponent->m_SetOutTurn;
    m_AccumWaitTime += GameEngine::TimeManager::GetElapsed();
    if(m_AccumWaitTime < m_WaitTime) return nullptr;
    const glm::vec2 currentPos = enemyComponent->GetGameObjParent()->GetPosition();
    auto [newPos, hasDirectionChanged] = enemyComponent->GetFormationTrajectory().Update(enemyComponent->GetSpeed(),
        currentPos);
    if (hasDirectionChanged)
    {
        if (enemyComponent->GetFormationTrajectory().IsComplete()) return std::make_unique<IdleState>();
           
        int rotationStage = enemyComponent->GetRotationStage(enemyComponent->GetFormationTrajectory().GetDirection());
        enemyComponent->UpdateSprite(rotationStage);
    }
    enemyComponent->GetGameObjParent()->SetPosition({ newPos,0 });
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
    pathData.destination = playerPos + glm::vec2{0, -50};
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
    m_BombingTrajectory.SetPathData(pathDataQueue, enemyComponent->GetGameObjParent()->GetPosition());
}
std::unique_ptr<EnemyState> BeeBombingRun::Update(EnemyComponent* enemyComponent)
{
    const glm::vec2 currentPos = enemyComponent->GetGameObjParent()->GetPosition();
    auto [newPos, hasDirectionChanged] = m_BombingTrajectory.Update(enemyComponent->GetSpeed(),
        currentPos);
    if (hasDirectionChanged)
    {
        if (m_BombingTrajectory.IsComplete()) return std::make_unique<IdleState>();
        int rotationStage = enemyComponent->GetRotationStage(m_BombingTrajectory.GetDirection());
        enemyComponent->UpdateSprite(rotationStage);
    }
    enemyComponent->GetGameObjParent()->SetPosition({ newPos,0 });
    return nullptr;
}
void ButterflyBombingRun::Enter(EnemyComponent* enemyComponent)
{
    enemyComponent;
}
std::unique_ptr<EnemyState> ButterflyBombingRun::Update(EnemyComponent* enemyComponent)
{
    enemyComponent; return nullptr;
}
void BossBombingRun::Enter(EnemyComponent* enemyComponent)
{
    enemyComponent;
}
std::unique_ptr<EnemyState> BossBombingRun::Update(EnemyComponent* enemyComponent)
{
    enemyComponent; return nullptr;
}
