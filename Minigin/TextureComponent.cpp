#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

using namespace GameEngine;

GameEngine::TextureComponent::TextureComponent(GameObject* gameObj): Component(gameObj)
{
}

void TextureComponent::Update()
{
	if (m_NeedsUpdate)
	{
		//Update the thing
	}
}

void TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = GetParent().GetComponent<TransformComponent>()->GetPosition();

		GameEngine::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = GameEngine::ResourceManager::GetInstance().LoadTexture(filename);
}
