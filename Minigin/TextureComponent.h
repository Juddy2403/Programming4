#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <string>

namespace GameEngine {
	class Texture2D;
	class TextureComponent final : public Component
	{
	public:
		explicit TextureComponent(GameObject* gameObj);
		explicit TextureComponent(GameObject* gameObj, const std::string& filename);
		explicit TextureComponent(GameObject* gameObj, std::shared_ptr<Texture2D>& texture);
		//virtual void Update() override;
		virtual void Render() override;
		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& texture);
	private:
		//bool m_NeedsUpdate{ true };
		std::shared_ptr<Texture2D> m_Texture{};

	};
}

