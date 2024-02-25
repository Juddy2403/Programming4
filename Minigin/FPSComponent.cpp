#include "FPSComponent.h"
#include "Time.h"
#include "TextComponent.h"

const float FPSComponent::m_FpsUpdateRate = 1.f;

void FPSComponent::Update(dae::GameObject& gameObj)
{
	auto& time = Time::GetInstance();
	m_FpsUpdateCounter += time.GetElapsed();
	++m_FramesSinceUpdate;
	if (m_FpsUpdateCounter >= m_FpsUpdateRate)
	{
		const float fpsCounter{ m_FramesSinceUpdate / m_FpsUpdateCounter };
		std::stringstream stream{};
		stream << std::fixed << std::setprecision(1) << fpsCounter;
		gameObj.GetComponent<TextComponent>()->SetText(stream.str());
		m_FramesSinceUpdate = 0;
		m_FpsUpdateCounter -= m_FpsUpdateRate;
	}
}

void FPSComponent::Render(const GameObject& gameObj) const
{
	(void)gameObj;
}
