#pragma once
#include "Vector3.h"
#include "Matrix.h"

namespace GameEngine
{
	class Vector3;
	class Transform final
	{
	public:
		const MathHelper::Vector3 GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void Translate(float x, float y);
		void SetRotation(float angle);
		void SetScale(float xScale, float yScale);

		void Update();

		Transform() = default;
		Transform(const Transform& other) = default;
		Transform& operator=(const Transform& other) = default;
		Transform operator+(const Transform& other);
		Transform operator-(const Transform& other);
	private:
		MathHelper::Vector3 m_Position{};
		MathHelper::Matrix m_TranslateMatrix{};
		MathHelper::Matrix m_RotateMatrix{};
		MathHelper::Matrix m_ScaleMatrix{};
	};
}
