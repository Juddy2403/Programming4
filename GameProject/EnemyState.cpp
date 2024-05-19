#include "EnemyState.h"

#include "Game components/FormationComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Subjects/GameObject.h"

EnemyState* IdleState::Update(EnemyComponent* enemyComponent)
{
    glm::ivec2 formationPos = enemyComponent->GetFormationPosition();
    formationPos.x += FormationComponent::GetOffset();
    enemyComponent->GetGameObjParent()->SetPosition({formationPos,1});
    return nullptr;
}
