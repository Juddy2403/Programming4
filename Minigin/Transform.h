#pragma once
#include <glm/glm.hpp>

namespace GameEngine
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);

		Transform() = default;
		Transform(const Transform& other) = default;
		Transform& operator=(const Transform& other) = default;
		Transform operator+(const Transform& other);
	private:
		glm::vec3 m_Position{};
	};
}
