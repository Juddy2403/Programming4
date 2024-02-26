#pragma once
#include "GameObject.h"

class dae::GameObject;
class Component
{
protected:
	friend class GameObject;
	Component() = default;
public:
	virtual void Update(dae::GameObject& gameObj) = 0;
	virtual void Render(const dae::GameObject& gameObj) const = 0;
	virtual void Transform();
	
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;
};

