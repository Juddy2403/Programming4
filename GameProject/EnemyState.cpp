#include "EnemyState.h"

#include <glm/gtc/constants.hpp>

#include "Game components/FormationComponent.h"
#include "Game components/RotatingSpriteComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Subjects/GameObject.h"
#include "Components/SpriteComponent.h"
#include "Trajectory Logic/Parsers.h"

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
    //std::queue<PathData> pathDataQueue = Parser::ParseTrajectory("../Data/Formations/trajectory.json");
    enemyComponent;
}
int GetInFormationState::GetRotationStage(EnemyComponent* enemyComponent)
{
    //calculate rotation angle based on the direction
    const auto direction = enemyComponent->GetFormationTrajectory().GetDirection();
    float rotationAngle = -(glm::atan(-direction.y, direction.x) - glm::pi<float>() / 2);
    //convert angle between 0 and 2*pi
    if (rotationAngle < 0) rotationAngle += glm::pi<float>() * 2;
    return static_cast<int>(rotationAngle / (glm::pi<float>() * 2) * enemyComponent->GetNrOfStages());
}

EnemyState* GetInFormationState::Update(EnemyComponent* enemyComponent, GameEngine::SpriteComponent* spriteComponent,
    RotatingSpriteComponent* rotatingSpriteComponent)
{
    const glm::vec2 currentPos = enemyComponent->GetGameObjParent()->GetPosition();
    auto [newPos, hasDirectionChanged] = enemyComponent->GetFormationTrajectory().Update(enemyComponent->GetSpeed().x, currentPos);
    if(hasDirectionChanged)
    {
        if(enemyComponent->GetFormationTrajectory().IsComplete()) return new IdleState;
        int rotationStage = GetRotationStage(enemyComponent);
        UpdateSprite(enemyComponent, spriteComponent, rotatingSpriteComponent, rotationStage);
    }
    enemyComponent->GetGameObjParent()->SetPosition({ newPos,0 });
    return nullptr;
}
