#include "TrajectoryStates.h"
#include "Game components/Enemy components/EnemyComponent.h"

void CircleTrajectory::Enter(PathData& pathData, const glm::vec2& currentPos)
{
    pathData.radius = glm::distance(currentPos, pathData.centerOfRotation);
    auto nextPos = TrajectoryMath::CalculateNextPositionInCircle(currentPos, pathData.centerOfRotation, pathData.radius);
    m_Direction = TrajectoryMath::CalculateDirection(currentPos, nextPos);
}
std::pair<glm::vec2, bool> CircleTrajectory::Update(PathData& pathData, float speed, const glm::vec2& currentPos)
{
    const auto nextPosInCircle = TrajectoryMath::CalculateNextPositionInCircle(currentPos, pathData.centerOfRotation, pathData.radius);
    m_Direction = TrajectoryMath::CalculateDirection(currentPos, nextPosInCircle);

    glm::vec2 nextPos = TrajectoryMath::CalculateNextPosition(currentPos, m_Direction, speed);
    const float currentAngle = std::atan2(-currentPos.y + pathData.centerOfRotation.y, currentPos.x - pathData.centerOfRotation.x);
    const float nextAngle = std::atan2(-nextPos.y + pathData.centerOfRotation.y, nextPos.x - pathData.centerOfRotation.x);
    pathData.accumRotationAngle += abs(currentAngle - nextAngle);

    if (pathData.accumRotationAngle >= pathData.totalRotationAngle)
    {
        return { nextPos,false };
    }
    return { nextPos,true };
}
void LinearTrajectory::Enter(PathData& pathData, const glm::vec2& currentPos)
{
    m_Direction = TrajectoryMath::CalculateDirection(currentPos, pathData.destination);
}

std::pair<glm::vec2, bool> LinearTrajectory::Update(PathData& pathData, float speed, const glm::vec2& currentPos)
{
    //glm::vec2 direction = TrajectoryMath::CalculateDirection(currentPos, m_Destination);
    glm::vec2 nextPos = TrajectoryMath::CalculateNextPosition(currentPos, m_Direction, speed);
    if (TrajectoryMath::ArePositionsEqual(pathData.destination, nextPos))
    {
        return { nextPos,false };
    }
    return { nextPos,true };
}
