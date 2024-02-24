#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <string>

class Texture2D;
class TextureComponent : public Component
{
public:
	TextureComponent() = default;
	TextureComponent(const std::string& filename);
	virtual void Update(dae::GameObject& gameObj) override;
	virtual void Render(const dae::GameObject& gameObj) const override;
	void SetTexture(const std::string& filename);
protected:
	bool m_NeedsUpdate{true};
	std::shared_ptr<dae::Texture2D> m_Texture{};
};
