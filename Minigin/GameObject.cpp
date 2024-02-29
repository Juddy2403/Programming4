#include "GameObject.h"
#include "Component.h"

using namespace GameEngine;

GameEngine::GameObject::GameObject(std::string name):
	m_Name{name}
{
}

GameEngine::GameObject::~GameObject() = default;

void GameEngine::GameObject::AddChild(GameObject* child)
{
	m_pChildren.emplace_back(child);
}

void GameEngine::GameObject::RemoveChild(GameObject* child)
{
	m_pChildren.erase(std::ranges::remove(m_pChildren, child).begin());
}

bool GameEngine::GameObject::IsChild(GameObject* child)
{
	return std::ranges::find(m_pChildren, child) != m_pChildren.end();
}

void GameEngine::GameObject::Update()
{
	bool areElemsToErase = false;
	for (auto& component : m_Components)
	{
		if (!component->IsDestroyed()) component->Update();
		else areElemsToErase = true;
	}

	UpdateWorldTransform();
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

GameObject* GameEngine::GameObject::GetParent() const
{
	return m_pParent;
}

void GameEngine::GameObject::SetParent(GameObject* parent)
{
	if (IsChild(parent) || parent == this || m_pParent == parent) return;
	if (m_pParent) m_pParent->RemoveChild(this);
	m_pParent = parent;
	if (m_pParent) m_pParent->AddChild(this);
}

int GameEngine::GameObject::GetChildCount() const
{
	return static_cast<int>(m_pChildren.size());
}

GameObject* GameEngine::GameObject::GetChildAt(int index)
{
	return m_pChildren[index];
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

void GameObject::SetPosition(float x, float y)
{
	m_LocalTransform.SetPosition(x, y, 0.0f);
	m_IsPositionDirty = true;
}

glm::vec3 GameObject::GetPosition() const
{
	return m_WorldTransform.GetPosition();
}

Transform GameEngine::GameObject::GetWorldTransform()
{
	if (m_IsPositionDirty) UpdateWorldTransform();
	return m_WorldTransform;

}

void GameEngine::GameObject::UpdateWorldTransform()
{
	if (m_IsPositionDirty)
	{
		if (m_pParent == nullptr) m_WorldTransform = m_LocalTransform;
		else m_WorldTransform = m_pParent->GetWorldTransform() + m_LocalTransform;
	}
	m_IsPositionDirty = false;
}