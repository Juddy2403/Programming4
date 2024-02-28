#include "FPSComponent.h"
#include "Time.h"

using namespace GameEngine;

const float FPSComponent::m_FpsUpdateRate = 1.f;

GameEngine::FPSComponent::FPSComponent(GameObject* gameObj) : Component(gameObj)
{
}

GameEngine::FPSComponent::FPSComponent(GameObject* gameObj, TextComponent* textComponent) :Component(gameObj),
m_TextComponent{ textComponent }
{
}

void FPSComponent::Update()
{
	auto& time = Time::GetInstance();
	m_FpsUpdateCounter += time.GetElapsed();
	++m_FramesSinceUpdate;
	if (m_FpsUpdateCounter >= m_FpsUpdateRate)
	{
		m_FPS = m_FramesSinceUpdate / m_FpsUpdateCounter;
		if (m_TextComponent != nullptr) m_TextComponent->SetText(std::format("{:.1f} FPS", m_FPS));
		m_FramesSinceUpdate = 0;
		m_FpsUpdateCounter -= m_FpsUpdateRate;
	}
}


