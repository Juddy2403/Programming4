#include "TransformComponent.h"

void TransformComponent::Update(dae::GameObject& gameObj)
{
	(void)gameObj;
}

void TransformComponent::Render(const dae::GameObject& gameObj) const
{
	(void)gameObj;
}

glm::vec3 TransformComponent::GetPosition() const
{
	return m_Transform.GetPosition();
}

void TransformComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}