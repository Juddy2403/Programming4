#include "Component.h"

using namespace GameEngine;

const GameObject& Component::GetParent() const
{
	return *m_pParent;
}

Component::Component(GameObject* gameObj):
	m_pParent{gameObj}
{}
