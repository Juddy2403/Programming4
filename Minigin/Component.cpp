#include "Component.h"

using namespace GameEngine;

GameObject* Component::GetGameObjParent() const
{
	return m_pParent;
}

bool GameEngine::Component::IsDestroyed() const
{
	return m_IsDestroyed;
}

void GameEngine::Component::SetDestroyedFlag()
{
	m_IsDestroyed = true;
}

Component::Component(GameObject* gameObj):
	m_pParent{gameObj}
{}
