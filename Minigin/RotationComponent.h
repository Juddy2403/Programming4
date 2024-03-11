#pragma once
#include "Component.h"

namespace GameEngine {
	class RotationComponent final : public Component
	{
	private:
		bool m_IsRotatingClockwise{};
		float m_Angle{};
		float m_Velocity{};
	public:
		RotationComponent(GameObject* gameObj,float velocity = 10.f, bool isRotatingClockwise = true);
		virtual void Update() override;

	};
}


