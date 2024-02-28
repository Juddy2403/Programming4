#include "GameObject.h"
#include "Component.h"

GameEngine::GameObject::GameObject(std::string name):
	m_Name{name}
{
}

GameEngine::GameObject::~GameObject() = default;

void GameEngine::GameObject::Update()
{
	bool areElemsToErase = false;
	for (auto& component : m_Components)
	{
		if (!component->IsDestroyed()) component->Update();
		else areElemsToErase = true;
	}

	if(areElemsToErase) RemoveDestroyedObjects();
}

void GameEngine::GameObject::RemoveDestroyedObjects()
{
	const auto range = std::ranges::remove_if(m_Components,
		[](const auto& obj) {
			return obj->IsDestroyed();
		});

	// Erase the destroyed objects from the vector
	m_Components.erase(range.begin(), range.end());
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

bool GameEngine::GameObject::IsDestroyed() const
{
	return m_IsDestroyed;
}

void GameEngine::GameObject::SetDestroyedFlag()
{
	m_IsDestroyed = true;
}
