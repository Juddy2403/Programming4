#include "Matrix.h"

#include <cassert>

#include "MathHelpers.h"
#include <cmath>

namespace MathHelper {
	Matrix::Matrix():
		Matrix(Vector3{1,0,0},
			Vector3{0,1,0},
			Vector3{0,0,1})
	{
	}
	Matrix::Matrix(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
	{
		data[0] = xAxis;
		data[1] = yAxis;
		data[2] = zAxis;
	}

	Matrix::Matrix(const Matrix& m)
	{
		data[0] = m.data[0];
		data[1] = m.data[1];
		data[2] = m.data[2];
	}

	Vector3 Matrix::TransformVector(const Vector3& v) const
	{
		return TransformVector(v[0], v[1], v[2]);
	}

	Vector3 Matrix::TransformVector(float x, float y, float z) const
	{
		return Vector3{
			data[0].x * x + data[1].x * y + data[2].x * z,
			data[0].y * x + data[1].y * y + data[2].y * z,
			data[0].z * x + data[1].z * y + data[2].z * z
		};
	}

	Vector3 Matrix::TransformPoint(const Vector3& p) const
	{
		return TransformPoint(p[0], p[1], p[2]);
	}

	Vector3 Matrix::TransformPoint(float x, float y, float z) const
	{
		return Vector3{
			data[0].x * x + data[1].x * y + data[2].x * z,
			data[0].y * x + data[1].y * y + data[2].y * z,
			data[0].z * x + data[1].z * y + data[2].z * z,
		};
	}

	Vector3 Matrix::GetAxisX() const
	{
		return data[0];
	}

	Vector3 Matrix::GetAxisY() const
	{
		return data[1];
	}

	Vector3 Matrix::GetTranslation() const
	{
		return data[2];
	}

	Matrix Matrix::CreateTranslation(float x, float y)
	{
		return Matrix{
		Vector3{1,0,0} ,
		Vector3{0,1,0} ,
		Vector3{x,y,1} };
	}

	Matrix Matrix::CreateTranslation(const Vector3& t)
	{
		return { Vector3::UnitX, Vector3::UnitY, t };
	}

	Matrix Matrix::CreateRotation(float angle)
	{
		return Matrix{
			Vector3{cos(angle),-sin(angle),0},
			Vector3{sin(angle),cos(angle),0} ,
			Vector3{0,0,1} };
	}

	Matrix Matrix::CreateScale(float scaleX, float scaleY)
	{
		return Matrix{
		Vector3{scaleX,0,0} ,
		Vector3{0,scaleY,0} ,
		Vector3{0,0,1} };
	}


	Matrix Matrix::Transpose(const Matrix& m) const
	{
		Matrix result{};
		for (int r{ 0 }; r < 3; ++r)
		{
			for (int c{ 0 }; c < 3; ++c)
			{
				result.data[r][c] = m.data[c][r];
			}
		}

		return result;
	}

#pragma region Operator Overloads

	Matrix Matrix::operator*(const Matrix& m) const
	{
		Matrix result{};
		Matrix m_transposed = Transpose(m);

		for (int r{ 0 }; r < 3; ++r)
		{
			for (int c{ 0 }; c < 3; ++c)
			{
				result.data[r][c] = Vector3::Dot(data[r], m_transposed.data[c]);
			}
		}

		return result;
	}

	const Matrix& Matrix::operator*=(const Matrix& m)
	{
		Matrix copy{ *this };
		Matrix m_transposed = Transpose(m);

		for (int r{ 0 }; r < 3; ++r)
		{
			for (int c{ 0 }; c < 3; ++c)
			{
				data[r][c] = Vector3::Dot(copy.data[r], m_transposed.data[c]);
			}
		}

		return *this;
	}
#pragma endregion
}