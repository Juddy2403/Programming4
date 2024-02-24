#pragma once
#include "GameObject.h"

using namespace dae;
class dae::GameObject;
class Component
{
public:
	virtual void Update(GameObject& gameObj) = 0;
	virtual void Render(const GameObject& gameObj) const = 0;
	virtual void Transform();
	
	Component() = default;
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;
};

