#include "EnemyState.h"

#include <glm/gtc/constants.hpp>

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
    std::queue<PathData> pathDataQueue;
    PathData pathData{};
    pathData.destination = enemyComponent->GetFormationPosition();
    pathDataQueue.push(pathData);
    pathData.isRotating = true;
    pathData.centerOfRotation = enemyComponent->GetFormationPosition() + glm::ivec2{ 0,100 };
    pathData.totalRotationAngle = 4 * glm::pi<float>();
    pathDataQueue.push(pathData);
    m_Trajectory.SetPathData(std::move(pathDataQueue), enemyComponent->GetGameObjParent()->GetPosition());
}
int GetInFormationState::GetRotationStage(EnemyComponent* enemyComponent)
{
    //calculate rotation angle based on the direction
    const auto direction = m_Trajectory.GetDirection();
    float rotationAngle = -(glm::atan(-direction.y, direction.x) - glm::pi<float>() / 2);
    //convert angle between 0 and 2*pi
    if (rotationAngle < 0) rotationAngle += glm::pi<float>() * 2;
    return static_cast<int>(rotationAngle / (glm::pi<float>() * 2) * enemyComponent->GetNrOfStages());
}

EnemyState* GetInFormationState::Update(EnemyComponent* enemyComponent, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingSpriteComponent)
{
    const glm::vec2 currentPos = enemyComponent->GetGameObjParent()->GetPosition();
    auto [newPos, hasDirectionChanged] = m_Trajectory.Update(enemyComponent->GetSpeed().x, currentPos);
    if(hasDirectionChanged)
    {
        if(m_Trajectory.IsComplete()) return new IdleState;
        int rotationStage = GetRotationStage(enemyComponent);
        UpdateSprite(enemyComponent, spriteComponent, rotatingSpriteComponent, rotationStage);
    }
    enemyComponent->GetGameObjParent()->SetPosition({ newPos,0 });
    return nullptr;
}
