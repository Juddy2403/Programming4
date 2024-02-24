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
	/*const auto& pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);*/
	for (const auto& component : m_Components)
	{
		component->Render(*this);
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

std::string dae::GameObject::GetName() const
{
	return m_Name;
}
