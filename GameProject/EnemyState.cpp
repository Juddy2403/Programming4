#include "EnemyState.h"

#include <iostream>
#include <glm/gtc/constants.hpp>

#include "Game components/FormationComponent.h"
#include "Game components/RotatingSpriteComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Managers/TimeManager.h"
#include "Subjects/GameObject.h"
#include "Components/SpriteComponent.h"

bool ArePositionsEqual(const glm::vec2& pos1, const glm::vec2& pos2)
{
    return abs(pos1.x - pos2.x) <= 2 && abs(pos1.y - pos2.y) <= 2;
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
    pathData.destination = enemyComponent->GetFormationPosition() + glm::ivec2{ 0,100 };
    m_PathData.push(pathData);
    pathData.isRotating = true;
    pathData.centerOfRotation = enemyComponent->GetFormationPosition();
    pathData.destination = enemyComponent->GetFormationPosition() + glm::ivec2{ 0,-50 };
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
    glm::vec2 currentPos = enemyComponent->GetGameObjParent()->GetPosition();
    if (!m_IsFollowingPath)
    {
        if (m_PathData.empty()) return new IdleState;

        if(m_PathData.front().isRotating)
        {
            // Calculate the current angle of the currentPos with respect to the center
            float currentAngle = std::atan2(m_PathData.front().centerOfRotation.y- currentPos.y,
                currentPos.x - m_PathData.front().centerOfRotation.x);
            if (currentAngle < 0) currentAngle += glm::pi<float>() * 2;

            // Increment the angle to move clockwise
            const float angleStep = glm::pi<float>() / 180;
            const float radius = glm::distance(currentPos,m_PathData.front().centerOfRotation);
            float nextAngle = currentAngle - angleStep; // Subtracting to move clockwise

            // Calculate the next position on the circle
            glm::vec2 nextPos = {
                m_PathData.front().centerOfRotation.x + radius * glm::cos(nextAngle),
                m_PathData.front().centerOfRotation.y + radius * glm::sin(nextAngle)
            };

            // Compute the direction vector from current position to next position
            m_Direction = glm::normalize(nextPos - currentPos);
            
        }
        else m_Direction = glm::normalize(m_PathData.front().destination - currentPos);
        
        int rotationStage = GetRotationStage(enemyComponent);

        const auto rotationInfo = rotatingSpriteComponent->GetColFlipPair(rotationStage);

        spriteComponent->m_SpriteInfo.m_StartPos.x = rotationInfo.first * (spriteComponent->m_SpriteInfo.m_Width
            + spriteComponent->m_SpriteInfo.m_Spacing) + enemyComponent->GetInitXPos();
        spriteComponent->SetFlipMode(rotationInfo.second);
        spriteComponent->UpdateSrcRect();

        m_IsFollowingPath = true;
    }
    else
    {
        if (ArePositionsEqual(m_PathData.front().destination, currentPos))
        {
            enemyComponent->GetGameObjParent()->SetPosition({ m_PathData.front().destination,0 });
            m_PathData.pop();
            m_IsFollowingPath = false;
        }
        else
        {
            if(m_PathData.front().isRotating)
            {
                // Calculate the current angle of the currentPos with respect to the center
                float currentAngle = std::atan2(m_PathData.front().centerOfRotation.y- currentPos.y,
                    currentPos.x - m_PathData.front().centerOfRotation.x);
                if (currentAngle < 0) currentAngle += glm::pi<float>() * 2;

                // Increment the angle to move clockwise
                const float angleStep = glm::pi<float>() / 180;
                const float radius = glm::distance(currentPos,m_PathData.front().centerOfRotation);
                float nextAngle = currentAngle - angleStep; // Subtracting to move clockwise

                // Calculate the next position on the circle
                glm::vec2 nextPos = {
                    m_PathData.front().centerOfRotation.x + radius * glm::cos(nextAngle),
                    m_PathData.front().centerOfRotation.y - radius * glm::sin(nextAngle)
                };

                // Compute the direction vector from current position to next position
                m_Direction = glm::normalize(nextPos - currentPos);

                int rotationStage = GetRotationStage(enemyComponent);

                const auto rotationInfo = rotatingSpriteComponent->GetColFlipPair(rotationStage);

                spriteComponent->m_SpriteInfo.m_StartPos.x = rotationInfo.first * (spriteComponent->m_SpriteInfo.m_Width
                    + spriteComponent->m_SpriteInfo.m_Spacing) + enemyComponent->GetInitXPos();
                spriteComponent->SetFlipMode(rotationInfo.second);
                spriteComponent->UpdateSrcRect();

            
            }
            glm::vec2 newPos = currentPos + m_Direction * enemyComponent->GetSpeed() * GameEngine::TimeManager::GetElapsed();
            enemyComponent->GetGameObjParent()->SetPosition({ newPos,0 });
        }
    }
    return nullptr;
}
