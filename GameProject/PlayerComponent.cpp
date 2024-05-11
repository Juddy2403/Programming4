#include "PlayerComponent.h"
#include "GameObject.h"

HealthComponent::HealthComponent(GameEngine::GameObject* gameObject, int health):
    Component(gameObject),
    m_Health(health)
{}

PlayerComponent::PlayerComponent(GameEngine::GameObject* gameObject, int playerID):
Component(gameObject), m_PlayerID(playerID){}


