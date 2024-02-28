#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <string>

namespace GameEngine {
	class Texture2D;
	class TextureComponent : public Component
	{
	public:
		explicit TextureComponent(GameObject* gameObj);
		virtual void Update() override;
		virtual void Render() const override;
		void SetTexture(const std::string& filename);
	protected:
		bool m_NeedsUpdate{ true };
		std::shared_ptr<Texture2D> m_Texture{};

	};
}

