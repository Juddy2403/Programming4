#include "Transform.h"

using namespace GameEngine;
void GameEngine::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
	m_TranslateMatrix = dae::Matrix::CreateTranslation(m_Position);
}

void GameEngine::Transform::Translate(float x, float y)
{
	m_TranslateMatrix = dae::Matrix::CreateTranslation(x, y);
}

void GameEngine::Transform::SetRotation(float angle)
{
	m_RotateMatrix = dae::Matrix::CreateRotation(angle);
}

void GameEngine::Transform::SetScale(float xScale, float yScale)
{
	m_ScaleMatrix = dae::Matrix::CreateScale(xScale, yScale);
}

void GameEngine::Transform::Update()
{
	dae::Matrix worldMatrix = m_TranslateMatrix * m_RotateMatrix * m_ScaleMatrix;
	m_Position = worldMatrix.GetTranslation();
}

Transform GameEngine::Transform::operator+(const Transform& other)
{
	Transform result{};
	result.m_Position.x = other.m_Position.x + m_Position.x;
	result.m_Position.y = other.m_Position.y + m_Position.y;
	result.m_Position.z = other.m_Position.z + m_Position.z;
	result.m_TranslateMatrix = dae::Matrix::CreateTranslation(result.m_Position);

	return result;
}

Transform GameEngine::Transform::operator-(const Transform& other)
{
	Transform result{};
	result.m_Position.x = m_Position.x - other.m_Position.x;
	result.m_Position.y = m_Position.y - other.m_Position.y;
	result.m_Position.z = m_Position.z - other.m_Position.z;
	result.m_TranslateMatrix = dae::Matrix::CreateTranslation(result.m_Position);

	return result;
}
