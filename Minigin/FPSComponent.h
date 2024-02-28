#pragma once
#include "Component.h"

namespace GameEngine {
	class FPSComponent : public Component
	{
	public:
		virtual void Update() override;
		explicit FPSComponent(GameObject* gameObj);
	private:
		float m_FpsUpdateCounter{};
		int m_FramesSinceUpdate{};
		static const float m_FpsUpdateRate;
	};

}

