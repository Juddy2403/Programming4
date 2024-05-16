#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace GameEngine;

void GameEngine::Transform::SetPosition( int x,  int y,  int z)
{
	m_Position.x =static_cast<float>(x);
	m_Position.y =static_cast<float>(y);
	m_Position.z =static_cast<float>(z);
	m_TranslateMatrix = glm::translate(glm::mat4(1.f), m_Position);
}

void GameEngine::Transform::Translate(int x, int y)
{
	m_TranslateMatrix = glm::translate(m_TranslateMatrix, glm::vec3(x, y, 1.f));
}

void GameEngine::Transform::Translate(const glm::ivec2& vec)
{
	Translate(vec.x, vec.y);
}


void GameEngine::Transform::SetRotation(float angle)
{
	m_RotateMatrix = glm::rotate(glm::mat4(1.f), angle, glm::vec3(0,0,1));
}

void GameEngine::Transform::SetScale(float xScale, float yScale)
{
	m_ScaleMatrix = glm::scale(glm::mat4(1.f), glm::vec3(xScale, yScale, 1));
}

void GameEngine::Transform::Update()
{
	glm::mat4 worldMatrix = m_RotateMatrix*  m_TranslateMatrix; //TODO: add scale matrix if necessary 
	m_Position = worldMatrix[3];
}

Transform GameEngine::Transform::operator+(const Transform& other)
{
	Transform result{};
	result.m_Position.x = other.m_Position.x + m_Position.x;
	result.m_Position.y = other.m_Position.y + m_Position.y;
	result.m_Position.z = other.m_Position.z + m_Position.z;
	m_TranslateMatrix = glm::translate(glm::mat4(1.f), result.m_Position);

	return result;
}

Transform GameEngine::Transform::operator-(const Transform& other)
{
	Transform result{};
	result.m_Position.x = m_Position.x - other.m_Position.x;
	result.m_Position.y = m_Position.y - other.m_Position.y;
	result.m_Position.z = m_Position.z - other.m_Position.z;
	m_TranslateMatrix = glm::translate(glm::mat4(1.f), result.m_Position);

	return result;
}
