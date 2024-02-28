#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace GameEngine;

GameEngine::TextureComponent::TextureComponent(GameObject* gameObj, const TransformComponent* transformComp): 
	Component(gameObj),
	m_TransformComp{transformComp}
{
}

GameEngine::TextureComponent::TextureComponent(GameObject* gameObj, const TransformComponent* transformComp, const std::string& filename) :
	Component(gameObj),
	m_TransformComp{ transformComp }
{
	SetTexture(filename);
}

GameEngine::TextureComponent::TextureComponent(GameObject* gameObj, const TransformComponent* transformComp, std::shared_ptr<Texture2D>& texture) : 
	Component(gameObj),
	m_TransformComp{ transformComp }
{
	SetTexture(texture);
}

//void TextureComponent::Update()
//{
//	if (m_NeedsUpdate)
//	{
//		//Update the thing
//	}
//}

void TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_TransformComp->GetPosition();

		GameEngine::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = GameEngine::ResourceManager::GetInstance().LoadTexture(filename);
}

void GameEngine::TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_Texture = texture;
}
