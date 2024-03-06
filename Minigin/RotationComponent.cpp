#include "RotationComponent.h"
#include "Time.h"
#include <numbers>

using namespace GameEngine;

GameEngine::RotationComponent::RotationComponent(GameObject* gameObj, float velocity, 
	bool isRotatingClockwise):
	Component(gameObj),
	m_Velocity{velocity},
	m_IsRotatingClockwise{ isRotatingClockwise }
{
}

void GameEngine::RotationComponent::Update()
{
	if (GetGameObjParent()->GetParent() != nullptr)
	{
		const float fullRotation{ 2 * static_cast<float>(std::numbers::pi) };

		if(m_IsRotatingClockwise)
		{
			m_Angle += Time::GetElapsed() * m_Velocity;
			if (m_Angle >= fullRotation) m_Angle -= fullRotation;
		}
		else
		{
			m_Angle -= Time::GetElapsed() * m_Velocity;
			if (m_Angle <= fullRotation) m_Angle += fullRotation;
		}
		GetGameObjParent()->GetLocalTransform().SetRotation(m_Angle);
		GetGameObjParent()->SetPositionIsDirty();
	}
}
