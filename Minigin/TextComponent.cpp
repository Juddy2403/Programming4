#include "TextComponent.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include "Renderer.h"

void TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetFont(std::shared_ptr<dae::Font> font)
{
	m_font = std::move(font);
}

void TextComponent::Update(dae::GameObject& gameObj)
{
	(void)gameObj; //TODO: remove this
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<dae::Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}
