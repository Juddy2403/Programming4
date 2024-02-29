#include "TextComponent.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include "Renderer.h"

using namespace GameEngine;

GameEngine::TextComponent::TextComponent(GameObject* gameObj, std::shared_ptr<Font> font, const std::string& text) : Component(gameObj)
{
	if(font) SetFont(font);
	SetText(text);
}
void TextComponent::SetText(const std::string& text)
{
	if(m_Text != text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}
}

void TextComponent::SetFont(std::shared_ptr<Font> font)
{
	assert(font);
	if (font) m_Font = font;
}

void TextComponent::Update()
{
	if (m_NeedsUpdate && GetParent()->CheckIfComponentExists<TextureComponent>())
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render  text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(GameEngine::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		GetParent()->GetComponent<TextureComponent>()->SetTexture(std::make_shared<GameEngine::Texture2D>(texture));
		m_NeedsUpdate = false;
	}
}
