#pragma once
#include "Vector3.h"

namespace dae {
	struct Matrix
	{
		Matrix() = default;
		Matrix(
			const Vector3& xAxis,
			const Vector3& yAxis,
			const Vector3& zAxis);

		Matrix(const Matrix& m);

		Vector3 TransformVector(const Vector3& v) const;
		Vector3 TransformVector(float x, float y, float z) const;
		Vector3 TransformPoint(const Vector3& p) const;
		Vector3 TransformPoint(float x, float y, float z) const;
		//const Matrix& Transpose();

		Vector3 GetAxisX() const;
		Vector3 GetAxisY() const;
		Vector3 GetAxisZ() const;

		static Matrix CreateTranslation(float x, float y);
		static Matrix CreateTranslation(const Vector3& t);
		static Matrix CreateRotation(float angle);
		static Matrix CreateScale(float scaleX, float scaleY);

		Matrix Transpose(const Matrix& m) const;

		Matrix operator*(const Matrix& m) const;
		const Matrix& operator*=(const Matrix& m);

	private:

		//Row-Major Matrix
		Vector3 data[3]
		{
			{1,0,0,}, //xAxis
			{0,1,0,}, //yAxis
			{0,0,1,}, //zAxis
		};

	};
}