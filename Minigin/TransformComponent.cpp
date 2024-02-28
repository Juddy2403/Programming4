#include "TransformComponent.h"

using namespace GameEngine;

glm::vec3 TransformComponent::GetPosition() const
{
	return m_Transform.GetPosition();
}

GameEngine::TransformComponent::TransformComponent(GameObject* gameObj) :Component(gameObj)
{
}

void TransformComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}