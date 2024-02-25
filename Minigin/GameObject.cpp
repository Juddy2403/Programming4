#include "GameObject.h"
#include "Component.h"

dae::GameObject::GameObject(std::string name):
	m_Name{name}
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto component : m_Components)
	{
		component.get()->Update(*this);
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		component->Render(*this);
	}
}

std::string dae::GameObject::GetName() const
{
	return m_Name;
}
