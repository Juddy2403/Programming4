#pragma once
#include "TextureComponent.h"
#include "Font.h"

class TextComponent : public TextureComponent
{
public:
	TextComponent() = default;
	void SetText(const std::string& text);
	void SetFont(std::shared_ptr<dae::Font> font);
	virtual void Update(dae::GameObject& gameObj) override;
private:
	std::string m_text{};
	std::shared_ptr<dae::Font> m_font{};
};

