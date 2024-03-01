#include "RotationComponent.h"
#include "Time.h"

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
		m_Angle += Time::GetElapsed() * m_Velocity * (m_IsRotatingClockwise ? 1 : -1);
		GetGameObjParent()->GetLocalTransform().SetRotation(m_Angle);
		GetGameObjParent()->SetPositionIsDirty();
	}
}
