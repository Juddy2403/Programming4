#pragma once
#include "TextureComponent.h"
#include "Font.h"

namespace GameEngine {
	class TextComponent : public Component
	{
	public:
		explicit TextComponent(GameObject* gameObj);
		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		virtual void Update() override;
	private:
		std::string m_text{};
		std::shared_ptr<Font> m_font{};
		bool m_NeedsUpdate{ true };
	};

}

