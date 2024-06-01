#include "EnemyState.h"
#include "Game components/FormationComponent.h"
#include "Game components/RotatingSpriteComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Subjects/GameObject.h"
#include "Trajectory Logic/Parsers.h"

const float GetInFormationState::m_TimeInBetween = 0.2f;

void IdleState::Enter(EnemyComponent* enemyComponent)
{
    int rotationStage = enemyComponent->GetRotationStage();
    enemyComponent->UpdateSprite(rotationStage);
}
EnemyState* IdleState::Update(EnemyComponent* enemyComponent)
{
    glm::vec2 formationPos = enemyComponent->GetFormationPosition();
    formationPos.x += FormationComponent::GetOffset();
    enemyComponent->GetGameObjParent()->SetPosition({ formationPos,0 });
    return nullptr;
}

void GetInFormationState::Enter(EnemyComponent* enemyComponent)
{
    //std::queue<PathData> pathDataQueue = Parser::ParseTrajectory("../Data/Formations/trajectory.json");
    //TODO: the wait time should be set here but it isnt since at this point the set out turn is 0
    m_WaitTime = m_TimeInBetween * enemyComponent->m_SetOutTurn;
    
}

EnemyState* GetInFormationState::Update(EnemyComponent* enemyComponent)
{
    m_WaitTime = m_TimeInBetween * enemyComponent->m_SetOutTurn;
    m_AccumWaitTime += GameEngine::TimeManager::GetElapsed();
    if(m_AccumWaitTime < m_WaitTime) return nullptr;
    const glm::vec2 currentPos = enemyComponent->GetGameObjParent()->GetPosition();
    auto [newPos, hasDirectionChanged] = enemyComponent->GetFormationTrajectory().Update(enemyComponent->GetSpeed(), currentPos);
    if (hasDirectionChanged)
    {
        if (enemyComponent->GetFormationTrajectory().IsComplete())
           {
            enemyComponent->GetGameObjParent()->Notify(static_cast<int>(GameEvent::gotInFormation),
                static_cast<int>(ObserverIdentifier::formation));
            return new IdleState;
           }
        int rotationStage = enemyComponent->GetRotationStage();
        enemyComponent->UpdateSprite(rotationStage);
    }
    enemyComponent->GetGameObjParent()->SetPosition({ newPos,0 });
    return nullptr;
}
