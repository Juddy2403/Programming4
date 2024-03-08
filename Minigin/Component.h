#pragma once
#include "GameObject.h"

namespace GameEngine 
{
	class GameObject;
	class Component
	{
	private:
		GameObject* m_pParent;
		bool m_IsDestroyed{ false };
	public:
		virtual void Update() {};
		virtual void Render() {};

		bool IsDestroyed() const;
		void SetDestroyedFlag();
		//virtual void Transform();

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	protected:
		GameObject* GetGameObjParent() const;
		explicit Component(GameObject* gameObj);


	};
}


