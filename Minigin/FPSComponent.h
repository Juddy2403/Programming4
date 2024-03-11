#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace GameEngine {
	class FPSComponent final: public Component
	{
	public:
		virtual void Update() override;
		explicit FPSComponent(GameObject* gameObj, TextComponent* textComponent = nullptr);
	private:
		float m_FpsUpdateCounter{};
		int m_FramesSinceUpdate{};
		float m_FPS{};
		static const float m_FpsUpdateRate;
		TextComponent* m_TextComponent{ nullptr };
	};

}

