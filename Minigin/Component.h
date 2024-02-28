#pragma once
#include "GameObject.h"

namespace GameEngine 
{
	class GameObject;
	class Component
	{
	private:
		const GameObject* m_pParent;
		bool m_IsDestroyed{ false };
	public:
		virtual void Update() {};
		virtual void Render() const {};

		const GameObject& GetParent() const;
		bool IsDestroyed() const;
		void SetDestroyedFlag();
		//virtual void Transform();

		explicit Component(GameObject* gameObj);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	};
}


