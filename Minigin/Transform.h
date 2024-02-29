#pragma once
#include "Vector3.h"
#include "Matrix.h"

namespace GameEngine
{
	class Vector3;
	class Transform final
	{
	public:
		const dae::Vector3 GetPosition() const { return m_Position; }
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
		dae::Vector3 m_Position{};
		dae::Matrix m_TranslateMatrix{};
		dae::Matrix m_RotateMatrix{};
		dae::Matrix m_ScaleMatrix{};
	};
}
