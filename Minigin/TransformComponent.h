#pragma once
#include "Component.h"
#include "Transform.h"

class TransformComponent : public Component
{
private:
	dae::Transform m_Transform{};
public:
	virtual void Update(dae::GameObject& gameObj) override;
	virtual void Render(const dae::GameObject& gameObj) const override;

	void SetPosition(float x, float y);
	glm::vec3 GetPosition() const;
};

