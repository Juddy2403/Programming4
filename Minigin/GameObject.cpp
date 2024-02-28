#include "GameObject.h"
#include "Component.h"

GameEngine::GameObject::GameObject(std::string name):
	m_Name{name}
{
}

GameEngine::GameObject::~GameObject() = default;

void GameEngine::GameObject::Update()
{
	for (auto& component : m_Components)
	{
		component.get()->Update();
		
	}
	
}

void GameEngine::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		component->Render();
	}
}

std::string GameEngine::GameObject::GetName() const
{
	return m_Name;

}
