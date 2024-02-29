#include "Transform.h"

using namespace GameEngine;
void GameEngine::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

Transform GameEngine::Transform::operator+(const Transform& other)
{
	Transform result{};
	result.m_Position.x = other.m_Position.x + m_Position.x;
	result.m_Position.y = other.m_Position.y + m_Position.y;
	result.m_Position.z = other.m_Position.z + m_Position.z;

	return result;
}
