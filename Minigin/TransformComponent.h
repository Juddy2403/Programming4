#pragma once
#include "Component.h"
#include "Transform.h"

namespace GameEngine {
	class TransformComponent : public Component
	{
	private:
		GameEngine::Transform m_Transform{};
	public:
		//virtual void Update() override;
		explicit TransformComponent(GameObject* gameObj);
		explicit TransformComponent(GameObject* gameObj, float x, float y);
		void SetPosition(float x, float y);
		glm::vec3 GetPosition() const;
	};

}

