#include "EnemyState.h"
#include "EnemyComponents.h"
#include "FormationComponent.h"
#include "GameObject.h"

EnemyState* IdleState::Update(EnemyComponent* enemyComponent)
{
    glm::vec2 formationPos = enemyComponent->GetFormationPosition();
    formationPos.x += FormationComponent::GetOffset();
    enemyComponent->GetGameObjParent()->SetPosition({formationPos,1});
    return nullptr;
}
