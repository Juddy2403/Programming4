//#include <string>
#include "GameObject.h"
//#include "ResourceManager.h"
//#include "Renderer.h"
#include "Component.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float elapsedSec)
{
	(void)elapsedSec; //TODO: remove this

	for (auto component : m_Components)
	{
		component.get()->Update(*this);
	}
}

void dae::GameObject::Render() const
{
	/*const auto& pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);*/
	for (auto component : m_Components)
	{
		component.get()->Render(*this);
	}
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

glm::vec3 dae::GameObject::GetPosition() const
{
	return m_Transform.GetPosition();
}
