#include "ActorComponent.h"

#include "GameObject.h"

GameEngine::ActorComponent::ActorComponent(GameObject* gameObject, int lives):
    Component(gameObject),
    m_Lives(lives)
{}

void GameEngine::ActorComponent::Hit()
{
    --m_Lives;
    GetGameObjParent()->Notify(GameEvent::playerDied,static_cast<int>(ObserverIdentifier::health));
}
void GameEngine::ActorComponent::IncreaseScore(int value)
{
    m_Score += value;
    GetGameObjParent()->Notify(GameEvent::scoreIncreased,static_cast<int>(ObserverIdentifier::score));
}
