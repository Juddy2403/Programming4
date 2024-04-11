#include "ActorComponent.h"
#include "GameObject.h"
#include "TimeManager.h"

GameEngine::ActorComponent::ActorComponent(GameObject* gameObject, int lives, int speed):
    Component(gameObject),
    m_Speed(speed),
    m_Lives(lives)
{}

void GameEngine::ActorComponent::Hit()
{
    --m_Lives;
    GetGameObjParent()->Notify(GameEvent::playerDied, static_cast<int>(ObserverIdentifier::health));
}
void GameEngine::ActorComponent::Move(const glm::vec2& direction)
{
    GetGameObjParent()->GetLocalTransform().Translate(TimeManager::GetElapsed() * m_Speed * direction);
}

GameEngine::ScoreComponent::ScoreComponent(GameObject* gameObject): Component(gameObject) {}

void GameEngine::ScoreComponent::IncreaseScore(int value)
{
    m_Score += value;
    GetGameObjParent()->Notify(GameEvent::scoreIncreased, static_cast<int>(ObserverIdentifier::score));
}
