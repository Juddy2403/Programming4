#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <string>
#include "TransformComponent.h"

namespace GameEngine {
	class Texture2D;
	class TextureComponent : public Component
	{
	public:
		explicit TextureComponent(GameObject* gameObj,const TransformComponent* transformComp);
		explicit TextureComponent(GameObject* gameObj,const TransformComponent* transformComp, const std::string& filename);
		explicit TextureComponent(GameObject* gameObj,const TransformComponent* transformComp, std::shared_ptr<Texture2D>& texture);
		//virtual void Update() override;
		virtual void Render() const override;
		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& texture);
	private:
		//bool m_NeedsUpdate{ true };
		const TransformComponent* m_TransformComp;
		std::shared_ptr<Texture2D> m_Texture{};

	};
}

