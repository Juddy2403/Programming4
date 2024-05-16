#include "EnemyState.h"
#include "EnemyComponents.h"
#include "FormationComponent.h"
#include "Subjects/GameObject.h"

EnemyState* IdleState::Update(EnemyComponent* enemyComponent)
{
    glm::ivec2 formationPos = enemyComponent->GetFormationPosition();
    formationPos.x += FormationComponent::GetOffset();
    enemyComponent->GetGameObjParent()->SetPosition({formationPos,1});
    return nullptr;
}
