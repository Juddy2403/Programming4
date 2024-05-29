#include "EnemyState.h"

#include <iostream>
#include <glm/gtc/constants.hpp>

#include "TrajectoryMath.h"
#include "Game components/FormationComponent.h"
#include "Game components/RotatingSpriteComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Managers/TimeManager.h"
#include "Subjects/GameObject.h"
#include "Components/SpriteComponent.h"

//TODO: move to a helper class or sum
inline void UpdateSprite(EnemyComponent* enemyComponent, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingSpriteComponent, int rotationStage)
{
    const auto rotationInfo = rotatingSpriteComponent->GetColFlipPair(rotationStage);

    spriteComponent->m_SpriteInfo.m_StartPos.x = rotationInfo.first * (spriteComponent->m_SpriteInfo.m_Width
        + spriteComponent->m_SpriteInfo.m_Spacing) + enemyComponent->GetInitXPos();
    spriteComponent->SetFlipMode(rotationInfo.second);
    spriteComponent->UpdateSrcRect();
}

EnemyState* IdleState::Update(EnemyComponent* enemyComponent, [[maybe_unused]] GameEngine::SpriteComponent* spriteComponent,
    [[maybe_unused]] RotatingSpriteComponent* rotatingSpriteComponent)
{
    glm::vec2 formationPos = enemyComponent->GetFormationPosition();
    formationPos.x += FormationComponent::GetOffset();
    enemyComponent->GetGameObjParent()->SetPosition({ formationPos,1 });
    return nullptr;
}
void GetInFormationState::Enter(EnemyComponent* enemyComponent)
{
    EnemyPathData pathData{};
    pathData.destination = enemyComponent->GetFormationPosition();
    m_PathData.push(pathData);
    pathData.isRotating = true;
    pathData.centerOfRotation = enemyComponent->GetFormationPosition() + glm::ivec2{ 0,100 };
    pathData.totalRotationAngle = 4 * glm::pi<float>();
    m_PathData.push(pathData);
}
int GetInFormationState::GetRotationStage(EnemyComponent* enemyComponent)
{
    //calculate rotation angle based on the direction
    float rotationAngle = -(glm::atan(-m_Direction.y, m_Direction.x) - glm::pi<float>() / 2);
    //convert angle between 0 and 2*pi
    if (rotationAngle < 0) rotationAngle += glm::pi<float>() * 2;
    return static_cast<int>(rotationAngle / (glm::pi<float>() * 2) * enemyComponent->GetNrOfStages());
}

EnemyState* GetInFormationState::Update(EnemyComponent* enemyComponent, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingSpriteComponent)
{
    const glm::vec2 currentPos = enemyComponent->GetGameObjParent()->GetPosition();
    if (!m_IsFollowingPath)
    {
        if (m_PathData.empty()) return new IdleState;
        if (m_PathData.front().isRotating)
        {
            m_PathData.front().radius = glm::distance(currentPos, m_PathData.front().centerOfRotation);
            auto nextPos = TrajectoryMath::CalculateNextPositionInCircle(currentPos, m_PathData.front().centerOfRotation, m_PathData.front().radius);
            m_Direction = TrajectoryMath::CalculateDirection(currentPos, nextPos);
        }
        else m_Direction = TrajectoryMath::CalculateDirection(currentPos, m_PathData.front().destination);
        int rotationStage = GetRotationStage(enemyComponent);
        UpdateSprite(enemyComponent, spriteComponent, rotatingSpriteComponent, rotationStage);
        m_IsFollowingPath = true;
    }
    else
    {
        if (m_PathData.front().isRotating)
        {
            if (m_PathData.front().accumRotationAngle >= m_PathData.front().totalRotationAngle)
            {
                m_PathData.pop();
                m_IsFollowingPath = false;
            }
            else
            {
                auto nextPos = TrajectoryMath::CalculateNextPositionInCircle(currentPos, m_PathData.front().centerOfRotation,
                    m_PathData.front().radius);
                m_Direction = TrajectoryMath::CalculateDirection(currentPos, nextPos);
                int rotationStage = GetRotationStage(enemyComponent);

                UpdateSprite(enemyComponent, spriteComponent, rotatingSpriteComponent, rotationStage);

                glm::vec2 newPos = TrajectoryMath::CalculateNextPosition(currentPos, m_Direction, enemyComponent->GetSpeed().x);
                const float currentAngle = std::atan2(-currentPos.y + m_PathData.front().centerOfRotation.y ,
                    currentPos.x - m_PathData.front().centerOfRotation.x);
                const float nextAngle = std::atan2(-newPos.y + m_PathData.front().centerOfRotation.y ,
                    newPos.x - m_PathData.front().centerOfRotation.x);
                m_PathData.front().accumRotationAngle += abs(currentAngle - nextAngle);

                enemyComponent->GetGameObjParent()->SetPosition({ newPos,0 });
            }
        }
        else
        {
            if (TrajectoryMath::ArePositionsEqual(m_PathData.front().destination, currentPos))
            {
                enemyComponent->GetGameObjParent()->SetPosition({ m_PathData.front().destination,0 });
                m_PathData.pop();
                m_IsFollowingPath = false;
            }
            else
            {
                glm::vec2 newPos = TrajectoryMath::CalculateNextPosition(currentPos, m_Direction, enemyComponent->GetSpeed().x);
                
                enemyComponent->GetGameObjParent()->SetPosition({ newPos,0 });
            }
        }
    }
    return nullptr;
}
