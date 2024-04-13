#include "PlayerComponent.h"
#include "GameObject.h"
#include "TimeManager.h"

ActorDataComponent::ActorDataComponent(GameEngine::GameObject* gameObject, int health):
    Component(gameObject),
    m_Health(health)
{}
void ActorDataComponent::IncreaseScore(int value)
{
    m_Score += value;
    GetGameObjParent()->Notify(GameEngine::GameEvent::scoreIncreased,
        static_cast<int>(GameEngine::ObserverIdentifier::score));
}
void ActorDataComponent::Hit()
{
    --m_Health;
    GetGameObjParent()->Notify(GameEngine::GameEvent::playerDied, static_cast<int>(GameEngine::ObserverIdentifier::health));
}

