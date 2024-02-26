#pragma once
#include "Component.h"

class FPSComponent : public Component
{
public:
	virtual void Update(dae::GameObject& gameObj) override;
	virtual void Render(const dae::GameObject& gameObj) const override;
private:
	float m_FpsUpdateCounter{};
	int m_FramesSinceUpdate{};
	static const float m_FpsUpdateRate;
};

