#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

void TextureComponent::Update(dae::GameObject& gameObj)
{
	(void)gameObj; //TODO:remove this
	if (m_NeedsUpdate)
	{
		//Update the thing
	}
}

void TextureComponent::Render(const dae::GameObject& gameObj) const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = gameObj.GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
