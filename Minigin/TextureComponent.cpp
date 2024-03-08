#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace GameEngine;

GameEngine::TextureComponent::TextureComponent(GameObject* gameObj): 
	Component(gameObj)
{
}

GameEngine::TextureComponent::TextureComponent(GameObject* gameObj, const std::string& filename) :
	Component(gameObj)
{
	SetTexture(filename);
}

GameEngine::TextureComponent::TextureComponent(GameObject* gameObj, std::shared_ptr<Texture2D>& texture) : 
	Component(gameObj)
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

void TextureComponent::Render() 
{
	if (m_Texture != nullptr)
	{
		const auto pos = GetGameObjParent()->GetPosition();

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
