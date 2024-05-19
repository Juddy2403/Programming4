#include "HealthComponent.h"

HealthComponent::HealthComponent(GameEngine::GameObject* gameObject, int health):
    Component(gameObject),
    m_Health(health)
{}