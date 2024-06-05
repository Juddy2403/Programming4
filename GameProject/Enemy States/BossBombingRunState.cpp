#include "BossBombingRunState.h"

#include "IdleState.h"
#include "Minigin.h"
#include "Game components/Enemy components/EnemyComponent.h"

void BossBombingRun::Enter(EnemyComponent* enemyComponent)
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
std::unique_ptr<EnemyState> BossBombingRun::Update(EnemyComponent* enemyComponent)
{
    if (enemyComponent->UpdateTrajectory(*m_BombingTrajectory)) return std::make_unique<IdleState>();
    return nullptr;
}
void BossShootingBeam::Enter(EnemyComponent* enemyComponent)
{
    std::queue<PathData> pathDataQueue;
    PathData pathData;

    auto enemyPos = enemyComponent->GetGameObjParent()->GetPosition();
    
    enemyComponent->GetGameObjParent()->Notify(static_cast<int>(GameEvent::bulletShot),
        static_cast<int>(ObserverIdentifier::bullet));
    // Initial upward movement
    pathData.destination = glm::vec2(enemyPos) + glm::vec2(0, -50);
    pathDataQueue.push(pathData);

    // Loop movement
    pathData = {};
    pathData.isRotating = true;
    pathData.isRotatingClockwise = static_cast<bool>(rand() % 2);
    pathData.centerOfRotation = glm::vec2(enemyPos);
    pathData.totalRotationAngle = 3.49066f;
    pathDataQueue.push(pathData);

    // Dive towards the player
    pathData = {};
    const glm::vec2 playerPos = enemyComponent->GetPlayerComponent()->GetGameObjParent()->GetPosition();
    pathData.destination = playerPos + glm::vec2{ 0, (enemyPos.y - playerPos.y)/2 + 100};
    pathDataQueue.push(pathData);

    // Set the trajectory
    m_BeamTrajectory->SetPathData(pathDataQueue, enemyComponent->GetGameObjParent()->GetPosition());
}
std::unique_ptr<EnemyState> BossShootingBeam::Update(EnemyComponent* enemyComponent)
{
    if(m_IsShootingBeam) return nullptr;
    if (enemyComponent->UpdateTrajectory(*m_BeamTrajectory))
    {
        enemyComponent->GetGameObjParent()->Notify(static_cast<int>(GameEvent::bossShotBeam),
        static_cast<int>(ObserverIdentifier::bullet));
        enemyComponent->GetRotatingSprite()->RotateSpriteInDirection({0,1});
        m_IsShootingBeam = true;
    }
    return nullptr;
}
