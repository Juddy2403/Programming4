#pragma once
#include "TextureComponent.h"
#include "Font.h"

namespace GameEngine {
	class TextComponent : public TextureComponent
	{
	public:
		explicit TextComponent(GameObject* gameObj);
		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		virtual void Update() override;
	protected:
		std::string m_text{};
		std::shared_ptr<Font> m_font{};
	};

}

