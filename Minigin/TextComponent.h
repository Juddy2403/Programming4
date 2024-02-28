#pragma once
#include "TextureComponent.h"
#include "Font.h"

namespace GameEngine {
	class TextComponent : public Component
	{
	public:
		explicit TextComponent(GameObject* gameObj);
		explicit TextComponent(GameObject* gameObj, const std::string& text);
		explicit TextComponent(GameObject* gameObj, std::shared_ptr<Font> font);
		explicit TextComponent(GameObject* gameObj, const std::string& text, std::shared_ptr<Font> font);

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		virtual void Update() override;
	private:
		std::string m_Text{};
		std::shared_ptr<Font> m_Font{};
		bool m_NeedsUpdate{ true };
	};

}

